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
    Table *table;       ///< Указатель на связанную таблицу
    bool end_of_table;  ///< Флаг конца таблицы (true если курсор за последней строкой)
    uint32_t page_num;  ///< Номер страницы, где находится текущая запись
    uint32_t cell_num;  ///< Номер ячейки (записи) внутри страницы
} Cursor;

/**
 * @brief Создает и инициализирует курсор для начала таблицы
 *
 * @param[in] table Указатель на таблицу, с которой будет работать курсор
 * @return Cursor* Указатель на созданный курсор
 *
 * @note Курсор всегда начинает с корневой страницы таблицы (root_page_num)
 * @note Для пустой таблицы устанавливает флаг end_of_table в true
 */
Cursor *table_start(Table *table);

/**
 * @brief Создает курсор в конце таблицы
 * @param[in] table Указатель на таблицу для итерации
 * @return Указатель на новый курсор
 */
Cursor *table_end(Table *table);

/**
 * @brief Возвращает указатель на указанную строку в таблице
 *
 * @param[in] cursor Указатель на структуру Cursor
 * @return Указатель на начало данных строки в памяти
 */
void* cursor_value(Cursor *cursor);

/**
 * @brief Перемещает курсор к следующей записи в таблице
 *
 * @param[in,out] cursor Указатель на курсор, который нужно переместить
 *
 * @note Если курсор достигнет конца текущей страницы, устанавливает флаг end_of_table
 * @warning Не обрабатывает переход между страницами (только в пределах одной страницы)
 */
void cursor_advance(Cursor *cursor);


#endif //DATABASE_CURSOR_H
