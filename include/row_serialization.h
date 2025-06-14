#ifndef DATABASE_ROW_SERIALIZATION_H
#define DATABASE_ROW_SERIALIZATION_H

#include "types.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

extern const uint32_t ID_SIZE;         ///< Размер поля id в байтах
extern const uint32_t USERNAME_SIZE;   ///< Размер поля username в байтах
extern const uint32_t EMAIL_SIZE;      ///< Размер поля email в байтах

extern const uint32_t ID_OFFSET;       ///< Смещение поля id от начала строки
extern const uint32_t USERNAME_OFFSET; ///< Смещение username от начала строки
extern const uint32_t EMAIL_OFFSET;    ///< Смещение email от начала строки

extern const uint32_t ROW_SIZE;        ///< Полный размер сериализованной строки (всех полей)

/**
@brief Сериализует структуру Row в массив байт

Копирует поля структуры Row в непрерывный блок памяти по заданным смещениям.

@param source Указатель на структуру Row
@param destination Указатель на буфер для записи
*/
void serialize_row(Row *source, void *destination);

/**

@brief Десериализует массив байт обратно в структуру Row

Восстанавливает поля структуры Row из буфера по заданным смещениям.

@param source Указатель на буфер с данными
@param destination Указатель на структуру Row для заполнения
*/
void deserialize_row(void *source, Row *destination);

#endif // DATABASE_ROW_SERIALIZATION_H