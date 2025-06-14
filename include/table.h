#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include "types.h"
#include "row_serialization.h"

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE       4096
#define ROWS_PER_PAGE   (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS  (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct {
    int file_descriptor;          // Дескриптор открытого файла
    uint32_t file_length;         // Текущий размер файла
    void *pages[TABLE_MAX_PAGES]  // Массив указателей на загруженные в память страницы данных
} Pager;


typedef struct {
    uint32_t num_of_rows;
    Pager *pager;
} Table;


/**
 * @brief Открывает или создает файл базы данных и инициализирует структуру Pager
 *
 * Функция создает новый объект Pager, который управляет доступом к файлу базы данных.
 * При первом открытии файла инициализирует его структуру и подготавливает кеш страниц в памяти.
 *
 * @param[in] filename Имя файла базы данных (может не существовать)
 * @return Указатель на инициализированную структуру Pager
 *
 * @warning Файл открывается с правами только для владельца (0600)
 * @see pager_close(), Table
 */
Pager *pager_open(const char *filename);

/**
 * @brief Получает страницу из кеша или загружает с диска
 * @param pager Указатель на структуру Pager
 * @param page_number Номер страницы (0-based)
 * @return Указатель на страницу или NULL при ошибке
 */
void *get_page(Pager *pager, uint32_t page_number);

Table *db_open(const char *filename);

void free_table(Table *table);

void* row_slot(Table *table, uint32_t row_number);

#endif //DATABASE_TABLE_H
