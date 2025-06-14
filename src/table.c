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


void *get_page(Pager *pager, uint32_t page_number) {
    if (page_number >= TABLE_MAX_PAGES) {
        printf("Tried to fetch page_number out of bounds. %d", TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_number] == NULL) {
        // Cache miss. Allocate memory and load from file
        void *page = malloc(PAGE_SIZE);
        if (!page) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        // We might save a partial page at the end of the file
        if (pager->file_length % PAGE_SIZE) {
            num_pages += 1;
        }

        if (page_number <= num_pages) {
            lseek(pager->file_descriptor, page_number * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if (bytes_read == -1) {
                printf("Error reading file.");
                free(page);
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[page_number] = page;
    }
    return pager->pages[page_number];
}

void *row_slot(Table *table, uint32_t row_number) {
    uint32_t page_number = row_number / ROWS_PER_PAGE;

    void *page = get_page(table->pager, page_number);

    uint32_t row_offset = row_number % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROWS_PER_PAGE;
    return page + byte_offset;
}