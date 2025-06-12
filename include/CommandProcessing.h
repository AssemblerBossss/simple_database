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

MetaCommandResult do_meta_command(InputBuffer *input_buffer);






#endif //DATABASE_COMMAND_PROCESSING_H
