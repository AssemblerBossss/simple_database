#include "../include/table.h"

Table *new_table() {
    Table *table = (Table *) malloc(sizeof(Table));
    table->num_of_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
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