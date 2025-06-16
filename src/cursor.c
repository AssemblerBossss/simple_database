#include "../include/cursor.h"

Cursor *table_start(Table *table) {
    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->num_row = 0;
    cursor->end_of_table = (table->num_of_rows == 0);

    return cursor;
}