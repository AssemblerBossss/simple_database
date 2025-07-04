#ifndef DATABASE_ROW_SERIALIZATION_H
#define DATABASE_ROW_SERIALIZATION_H

#include "types.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

// Размеры полей
#define ID_SIZE       size_of_attribute(Row, id)        ///< Размер поля id в байтах
#define USERNAME_SIZE size_of_attribute(Row, username)  ///< Размер поля username в байтах
#define EMAIL_SIZE    size_of_attribute(Row, email)     ///< Размер поля email в байтах

// Смещения полей
#define ID_OFFSET       0                                  ///< Смещение поля id от начала строки
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)              ///< Смещение username от начала строки
#define EMAIL_OFFSET    (USERNAME_OFFSET + USERNAME_SIZE)  ///< Смещение email от начала строки

// Полный размер строки
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)    ///< Полный размер сериализованной строки (всех полей)
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