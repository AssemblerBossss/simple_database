#include "../include/cursor.h"

Cursor *table_start(Table *table) {
    Cursor *cursor = (Cursor*)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->num_row = 0;
    cursor->end_of_table = (table->num_of_rows == 0);

    return cursor;
}

Cursor *table_end(Table *table) {
    Cursor *cursor = (Cursor*)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->num_row = table->num_of_rows;
    cursor->end_of_table = true;

    return cursor;
}

void *cursor_value(Cursor *cursor) {
    // Calculate which page contains the requested row

    uint32_t row_number = cursor->num_row;
    uint32_t page_number = cursor->num_row / ROWS_PER_PAGE;
    // Get the page (either from cache or load from disk)
    void *page = get_page(cursor->table->pager, page_number);

    // Calculate the row's position within the page
    uint32_t row_offset = row_number % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}


void cursor_advance(Cursor *cursor) {
    cursor->num_row += 1;
    if (cursor->num_row == cursor->table->num_of_rows) {
        cursor->end_of_table = true;
    }
}
