#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include "types.h"
#include "row_serialization.h"
#include "node.h"


typedef struct {
    int file_descriptor;          ///< Дескриптор открытого файла
    uint32_t file_length;         ///< Текущий размер файла
    void *pages[TABLE_MAX_PAGES]; ///< Массив указателей на загруженные в память страницы (NULL если страница не загружена)
    uint32_t num_pages;
} Pager;


typedef struct {
    Pager *pager;           ///< Указатель на менеджер страничного доступа
    uint32_t root_page_num;
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
 * @param[in] pager Указатель на структуру Pager
 * @param[in] page_number Номер страницы (0-based)
 * @return Указатель на страницу или NULL при ошибке
 */
void *get_page(Pager *pager, uint32_t page_number);

/**
 * @brief Открывает базу данных или создает новую
 *
 * Функция инициализирует структуру Table и связанный с ней Pager для работы с файлом базы данных.
 * Если файл существует, вычисляет количество строк на основе его размера.
 *
 * @param[in] filename Имя файла базы данных
 * @return Указатель на созданную структуру Table
 *
 */
Table *db_open(const char *filename);

/**
 * @brief Закрывает таблицу и освобождает все ресурсы
 *
 * Функция выполняет:
 * - Сброс всех страниц данных на диск (как полных, так и частичных)
 * - Закрытие файлового дескриптора
 * - Освобождение памяти, занятой страницами, Pager и Table
 *
 * @param[in] table Указатель на таблицу для закрытия
 *
 * @note Частичные страницы обрабатываются отдельно от полных
 */
void db_close(Table *table);

/**
 * @brief Записывает страницу данных из памяти на диск
 *
 * Функция выполняет сброс (flush) указанной страницы из кеша в памяти
 * в соответствующий участок файла базы данных.
 *
 * @param[in] pager Указатель на структуру Pager
 * @param[in] page_num Номер страницы для записи (0-based)
 * @param[in] size Количество байт для записи
 */
void pager_flush(Pager *pager, uint32_t page_num);


#endif //DATABASE_TABLE_H
