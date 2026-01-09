#ifndef MEMALLOCATOR_H
#define MEMALLOCATOR_H

#include <stddef.h>

// Инициализация аллокатора с указанием общего размера памяти
int meminit(void* buffer, size_t size);

// Выделение блока памяти заданного размера
void* memalloc(size_t size);

// Освобождение ранее выделенного блока памяти
void memfree(void* ptr);

// Дефрагментация памяти
void memdefrag();

// Получение статистики использования памяти
void memstat();

#endif // MEMALLOCATOR_H