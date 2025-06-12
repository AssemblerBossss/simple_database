#ifndef DATABASE_COMMAND_PROCESSING_H
#define DATABASE_COMMAND_PROCESSING_H

#include <string.h>

#include "InputBuffer.h"

/*
 * Перечисление для возврата статуса выполнения метакоманд.
 */
typedef enum {
    META_COMMAND_SUCCESS,             // Метакоманда успешно распознана и выполнена
    META_COMMAND_UNRECOGNIZED_COMMAND // Введенная команда не является известной метакомандой
} MetaCommandResult;

/*
 * Перечисление для возврата статуса подготовки SQL-запроса.
 * Используется на этапе разбора и подготовки запроса перед выполнением.
 */
typedef enum {
    PREPARE_SUCCESS,                // SQL-запрос успешно распознан и подготовлен к выполнению
    PREPARE_UNRECOGNIZED_STATEMENT  // Введенный запрос не соответствует ни одному известному типу SQL-запроса
} PrepareResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer);






#endif //DATABASE_COMMAND_PROCESSING_H
