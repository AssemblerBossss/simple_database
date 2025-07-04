#ifndef DATABASE_STATEMENT_H
#define DATABASE_STATEMENT_H

#include "types.h"

// Тип перечисления для определения типа SQL-запроса
typedef enum {
    STATEMENT_INSERT,  // Запрос на вставку данных (INSERT)
    STATEMENT_SELECT,  // Запрос на выборку данных (SELECT)
    STATEMENT_DELETE,  // Запрос на удаление данных (DELETE)
    STATEMENT_UPDATE   // Запрос на обновление данных (UPDATE)
} StatementType;

// Структура, представляющая SQL-запрос
typedef struct {
    StatementType type;       // Тип запроса (из перечисления StatementType)
    Row row_to_insert;        // Данные для вставки (актуально для INSERT)
} Statement;

// Тип перечисления для результата выполнения запроса
typedef enum {
    EXECUTE_SUCCESS,      // Запрос выполнен успешно
    EXECUTE_TABLE_FULL    // Ошибка: таблица заполнена (нет места для вставки)
} ExecuteResult;

#endif // DATABASE_STATEMENT_H