#ifndef DATABASE_TYPES_H
#define DATABASE_TYPES_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

#endif // DATABASE_TYPES_H