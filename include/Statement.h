#ifndef DATABASE_STATEMENT_H
#define DATABASE_STATEMENT_H

#include <string.h>

#include "InputBuffer.h"


/*
 * Перечисление для возврата статуса подготовки SQL-запроса.
 * Используется на этапе разбора и подготовки запроса перед выполнением.
 */
typedef enum {
    PREPARE_SUCCESS,                // SQL-запрос успешно распознан и подготовлен к выполнению
    PREPARE_UNRECOGNIZED_STATEMENT  // Введенный запрос не соответствует ни одному известному типу SQL-запроса
} PrepareResult;


typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_DELETE,
    STATEMENT_UPDATE
} StatementType;


typedef struct {
    StatementType type
} Statement;


PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

void execute_statement(Statement *statement);

#endif //DATABASE_STATEMENT_H
