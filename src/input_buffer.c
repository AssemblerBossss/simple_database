#include "../include/input_buffer.h"

InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer = (InputBuffer *) malloc(sizeof(InputBuffer));

    if (input_buffer) {
        input_buffer->buffer = NULL;
        input_buffer->buffer_length = 0;
        input_buffer->input_length = 0;
        return input_buffer;
    }
    else {
        perror("Ошибка выделения памяти для InputBuffer");
        exit(EXIT_FAILURE);

    }
}


void read_input(InputBuffer *input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer),
                                 &(input_buffer->buffer_length),
                                 stdin);
    if (bytes_read <= 0) {
        perror("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;

}

void close_input_buffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}