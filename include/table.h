#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include "types.h"
#include "row_serialization.h"

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE       4096
#define ROWS_PER_PAGE   (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS  (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct {
    uint32_t num_of_rows;
    void *pages[TABLE_MAX_PAGES];
} Table;

Table *new_table();

void free_table(Table *table);

void* row_slot(Table *table, uint32_t row_number);

#endif //DATABASE_TABLE_H
