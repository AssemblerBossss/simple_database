#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include "types.h"
#include "row_serialization.h"

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE       4096
#define ROWS_PER_PAGE   (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS  (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void *pages[TABLE_MAX_PAGES]
} Pager;


typedef struct {
    uint32_t num_of_rows;
    Pager *pager;
} Table;

Table *db_open(const char *filename);

void free_table(Table *table);

void* row_slot(Table *table, uint32_t row_number);

#endif //DATABASE_TABLE_H
