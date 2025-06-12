cmake_minimum_required(VERSION 3.28)
project(database C)

set(CMAKE_C_STANDARD 23)

add_executable(database main.c
        src/InputBuffer.c
        src/Utils.c
        src/CommandProcessing.c
        src/Statement.c)
