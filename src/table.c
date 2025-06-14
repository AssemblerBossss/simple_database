#include "../include/table.h"

Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;

    Table *table = (Table*)malloc(sizeof(Table));
    table->pager = pager;
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