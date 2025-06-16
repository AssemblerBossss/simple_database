#ifndef DATABASE_CURSOR_H
#define DATABASE_CURSOR_H

#include "types.h"
#include "table.h"

/**
 * @brief Структура курсора для итерации по таблице
 *
 * Курсор хранит текущую позицию при обходе таблицы и флаг достижения конца.
 */
typedef struct {
    Table *table;      ///< Указатель на связанную таблицу
    uint32_t num_row;  ///< Текущий номер строки (0-based)
    bool end_of_table; ///< Флаг конца таблицы (true если курсор за последней строкой)
} Cursor;

/**
 * @brief Создает курсор в начале таблицы
 * @param[in] table Указатель на таблицу для итерации
 * @return Указатель на новый курсор
 */
Cursor *table_start(Table *table);

/**
 * @brief Создает курсор в конце таблицы
 * @param[in] table Указатель на таблицу для итерации
 * @return Указатель на новый курсор
 */
Cursor *table_end(Table *table);


#endif //DATABASE_CURSOR_H
