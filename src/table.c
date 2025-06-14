#include "../include/table.h"

Pager *pager_open(const char *filename) {
    int _file_descriptor = open(
            filename,
            O_RDWR          // Read/Write mode
            | O_CREAT,      // Crete file if note exists
            S_IRUSR         // User read permission
            | S_IWUSR      // User read permission

            );

    if (_file_descriptor == -1) {
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(_file_descriptor, 0, SEEK_END);

    Pager *pager = (Pager*)malloc(sizeof(Pager));
    pager->file_descriptor = _file_descriptor;
    pager->file_length = file_length;

    for (uint32_t i =0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;

    Table *table = (Table*)malloc(sizeof(Table));
    table->pager = pager;
    table->num_of_rows = num_rows;
    return table;
}

void free_table(Table *table) {
    for(uint32_t i = 0; table->pages[i]; i++) {
        free(table->pages[i]);
    }
    free(table);
}


void *row_slot(Table *table, uint32_t row_number) {
    uint32_t page_number = row_number / ROWS_PER_PAGE;
    void *page = table->pages[page_number];

    if (page == NULL) {
        // Allocate memory only when we try to access page
        page = table->pages[page_number] = malloc(PAGE_SIZE);
    }

    uint32_t row_offset = row_number % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROWS_PER_PAGE;
    return page + byte_offset;
}