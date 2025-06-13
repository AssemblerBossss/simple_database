#ifndef DATABASE_ROW_SERIALIZATION_H
#define DATABASE_ROW_SERIALIZATION_H

#include "types.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

void serialize_row(Row *source, void *destination);
void deserialize_row(void *source, Row *destination);

#endif // DATABASE_ROW_SERIALIZATION_H