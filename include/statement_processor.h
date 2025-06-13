#ifndef DATABASE_STATEMENT_PROCESSOR_H
#define DATABASE_STATEMENT_PROCESSOR_H

#include "input_buffer.h"
#include "statement.h"
#include "prepare_result.h"
#include "table.h"
#include "Utils.h"


PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_update(Statement *statement, Table *table);
ExecuteResult execute_delete(Statement *statement, Table *table);
ExecuteResult execute_statement(Statement *statement, Table *table);

#endif // DATABASE_STATEMENT_PROCESSOR_H