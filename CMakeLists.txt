cmake_minimum_required(VERSION 3.28)
project(database C)

set(CMAKE_C_STANDARD 23)

add_executable(database main.c
        src/input_buffer.c
        src/Utils.c
        src/command_processing.c
        src/statement_processor.c
        include/table.h
        include/row_serialization.h
        src/table.c
        src/row_serialization.c
        src/statement_processor.c
)
