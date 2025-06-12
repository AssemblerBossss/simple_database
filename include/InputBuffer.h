#ifndef DATABASE_INPUTBUFFER_H
#define DATABASE_INPUTBUFFER_H

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Структура для хранения входного буфера
 *
 * Содержит буфер для хранения вводимых данных и информацию о его размере.
 */
typedef struct {
    char* buffer;          ///< Указатель на динамически выделенный буфер
    size_t buffer_length;  ///< Текущая длина выделенного буфера
    ssize_t input_length;  ///< Фактическая длина введенных данных
} InputBuffer;

/**
 * @brief Создает новый входной буфер
 *
 * @return Указатель на выделенный буфер
 * @note Вызывающая сторона должна освободить память через close_input_buffer()
 */
InputBuffer* new_input_buffer();

/**
 * @brief Читает ввод пользователя в буфер
 *
 * @param input_buffer Указатель на инициализированный буфер
 * @warning Использует getline(), которая выделяет память автоматически
 */
void read_input(InputBuffer* input_buffer);

/**
 * @brief Освобождает ресурсы входного буфера
 *
 * @param input_buffer Указатель на буфер для освобождения
 * @post После вызова указатель становится невалидным
 */
void close_input_buffer(InputBuffer* input_buffer);

#endif //DATABASE_INPUTBUFFER_H
