#ifndef DATABASE_STATEMENT_PROCESSOR_H
#define DATABASE_STATEMENT_PROCESSOR_H

#include "input_buffer.h"
#include "statement.h"
#include "prepare_result.h"
#include "table.h"
#include "Utils.h"

/**
 * @brief Подготавливает INSERT-запрос из входного буфера
 * @param[in] input_buffer Указатель на входной буфер с командой
 * @param[in] statement Указатель на структуру Statement для заполнения
 * @return Результат подготовки (PrepareResult)
 *
 * @note Разбирает строку формата: "insert id username email"
 */
PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement);

/**
 * @brief Определяет тип SQL-запроса (INSERT, SELECT...) и подготавливает Statement
 * @param[in] input_buffer Указатель на входной буфер
 * @param[in] statement Указатель на структуру Statement
 * @return Результат подготовки (PrepareResult)
 */
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

/**
 * @brief Выполняет INSERT-запрос
 * @param[in] statement Указатель на подготовленный Statement
 * @param[in] table Указатель на таблицу
 * @return Результат выполнения (ExecuteResult)
 *
 * @note Добавляет строку в конец таблицы
 * @warning Проверяет переполнение таблицы
 */
ExecuteResult execute_insert(Statement *statement, Table *table);

/**
 * @brief Выполняет SELECT-запрос
 * @param[in] statement Указатель на подготовленный Statement
 * @param[in] table Указатель на таблицу
 * @return Результат выполнения (ExecuteResult)
 *
 * @note Выводит все строки таблицы в формате (id, username, email)
 */
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_update(Statement *statement, Table *table);
ExecuteResult execute_delete(Statement *statement, Table *table);

/**
 * @brief Выполняет SQL-запрос на основе типа Statement
 * @param[in] statement Указатель на подготовленный Statement
 * @param[in] table Указатель на таблицу
 * @return Результат выполнения (ExecuteResult)
 *
 * @note Маршрутизирует выполнение на конкретные функции
 * @warning Не реализованы UPDATE и DELETE (заглушки)
 */
ExecuteResult execute_statement(Statement *statement, Table *table);

#endif // DATABASE_STATEMENT_PROCESSOR_H