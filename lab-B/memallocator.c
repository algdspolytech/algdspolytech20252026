#include "memallocator.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Константы
#define ALIGNMENT 8  // Выравнивание для 64-битных систем
#define MIN_BLOCK_SIZE 32  // Минимальный размер блока (включая заголовок)
#define DEBUG 0  // Включить отладочный вывод

// Макросы для выравнивания
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define IS_ALIGNED(addr) (((uintptr_t)(addr) & (ALIGNMENT - 1)) == 0)

// Структура заголовка блока памяти
typedef struct BlockHeader {
    size_t size;              // Размер блока (включая заголовок, без учета соседей)
    int is_free;              // Флаг свободного блока (1 - свободен, 0 - занят)
    struct BlockHeader* prev; // Предыдущий блок в списке свободных
    struct BlockHeader* next; // Следующий блок в списке свободных
    void* data;               // Указатель на данные блока
} BlockHeader;

// Глобальные переменные
static void* memory_pool = NULL;     // Указатель на начало пула памяти
static size_t pool_size = 0;         // Общий размер пула памяти
static BlockHeader* free_list = NULL; // Голова списка свободных блоков

// Вспомогательные функции
static void* get_block_end(BlockHeader* header) {
    return (char*)header + header->size;
}

static BlockHeader* get_next_block(BlockHeader* header) {
    BlockHeader* next = (BlockHeader*)get_block_end(header);
    
    // Проверяем, не выходим ли за пределы пула
    if ((char*)next >= (char*)memory_pool + pool_size) {
        return NULL;
    }
    return next;
}

static void remove_from_free_list(BlockHeader* block) {
    if (!block) return;
    
    if (block->prev) {
        block->prev->next = block->next;
    } else {
        free_list = block->next;
    }
    
    if (block->next) {
        block->next->prev = block->prev;
    }
    
    block->prev = NULL;
    block->next = NULL;
}

static void add_to_free_list(BlockHeader* block) {
    if (!block) return;
    
    block->is_free = 1;
    block->prev = NULL;
    block->next = free_list;
    
    if (free_list) {
        free_list->prev = block;
    }
    
    free_list = block;
}

static void merge_with_next(BlockHeader* block) {
    BlockHeader* next = get_next_block(block);
    
    if (next && next->is_free) {
        // Удаляем следующий блок из списка свободных
        remove_from_free_list(next);
        
        // Объединяем блоки
        block->size += next->size;
        
        // Обновляем указатель на данные
        block->data = (char*)block + sizeof(BlockHeader);
    }
}

// Основные функции аллокатора

int meminit(void* buffer, size_t size) {
    if (!buffer || size < MIN_BLOCK_SIZE) {
        return -1;  // Ошибка: некорректные параметры
    }
    
    // Выравниваем начало буфера
    memory_pool = (void*)ALIGN((uintptr_t)buffer);
    pool_size = size - ((char*)memory_pool - (char*)buffer);
    
    // Выравниваем размер пула
    pool_size = ALIGN(pool_size);
    
    if (pool_size < MIN_BLOCK_SIZE) {
        return -1;  // Ошибка: слишком маленький буфер
    }
    
    // Инициализируем первый блок как свободный
    BlockHeader* first_block = (BlockHeader*)memory_pool;
    first_block->size = pool_size;
    first_block->is_free = 1;
    first_block->prev = NULL;
    first_block->next = NULL;
    first_block->data = (char*)first_block + sizeof(BlockHeader);
    
    free_list = first_block;
    
    #if DEBUG
    printf("Memory pool initialized:\n");
    printf("  Buffer: %p\n", buffer);
    printf("  Memory pool: %p\n", memory_pool);
    printf("  Pool size: %zu bytes\n", pool_size);
    printf("  First block: %p, size: %zu\n", first_block, first_block->size);
    #endif
    
    return 0;  // Успешная инициализация
}

void* memalloc(size_t size) {
    if (!size || !free_list) {
        return NULL;
    }
    
    // Выравниваем размер запроса
    size_t requested_size = ALIGN(size + sizeof(BlockHeader));
    if (requested_size < MIN_BLOCK_SIZE) {
        requested_size = MIN_BLOCK_SIZE;
    }
    
    BlockHeader* best_block = NULL;
    BlockHeader* current = free_list;
    
    // Поиск лучшего подходящего блока
    while (current) {
        if (current->size >= requested_size) {
            if (!best_block || current->size < best_block->size) {
                best_block = current;
            }
        }
        current = current->next;
    }
    
    if (!best_block) {
        #if DEBUG
        printf("No suitable block found for size %zu\n", size);
        #endif
        return NULL;  // Не нашли подходящий блок
    }
    
    // Удаляем найденный блок из списка свободных
    remove_from_free_list(best_block);
    
    // Проверяем, можно ли разделить блок
    size_t remaining_size = best_block->size - requested_size;
    if (remaining_size >= MIN_BLOCK_SIZE) {
        // Создаем новый свободный блок из остатка
        BlockHeader* new_block = (BlockHeader*)((char*)best_block + requested_size);
        new_block->size = remaining_size;
        new_block->is_free = 1;
        new_block->data = (char*)new_block + sizeof(BlockHeader);
        
        // Уменьшаем размер текущего блока
        best_block->size = requested_size;
        
        // Добавляем новый блок в список свободных
        add_to_free_list(new_block);
    }
    
    // Помечаем блок как занятый
    best_block->is_free = 0;
    best_block->data = (char*)best_block + sizeof(BlockHeader);
    
    #if DEBUG
    printf("Allocated %zu bytes at %p (block: %p, total size: %zu)\n", 
           size, best_block->data, best_block, best_block->size);
    #endif
    
    // Обнуляем выделенную память (опционально)
    memset(best_block->data, 0, best_block->size - sizeof(BlockHeader));
    
    return best_block->data;
}

void memfree(void* ptr) {
    if (!ptr || ptr < memory_pool || ptr >= (char*)memory_pool + pool_size) {
        #if DEBUG
        printf("Invalid pointer to free: %p\n", ptr);
        #endif
        return;
    }
    
    // Получаем заголовок блока
    BlockHeader* block = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    
    // Проверяем корректность указателя
    if (block->data != ptr || block->is_free) {
        #if DEBUG
        printf("Double free or corrupted pointer: %p\n", ptr);
        #endif
        return;
    }
    
    #if DEBUG
    printf("Freeing block at %p (size: %zu)\n", block, block->size);
    #endif
    
    // Помечаем блок как свободный
    block->is_free = 1;
    
    // Добавляем блок в список свободных
    add_to_free_list(block);
    
    // Пытаемся объединить с предыдущим блоком
    BlockHeader* prev_block = NULL;
    if ((char*)block > (char*)memory_pool) {
        // Ищем предыдущий блок (линейный поиск)
        BlockHeader* current = (BlockHeader*)memory_pool;
        while (current && get_next_block(current) != block) {
            current = get_next_block(current);
        }
        prev_block = current;
    }
    
    if (prev_block && prev_block->is_free) {
        // Удаляем текущий блок из списка
        remove_from_free_list(block);
        // Объединяем с предыдущим
        prev_block->size += block->size;
        block = prev_block;
    }
    
    // Пытаемся объединить со следующим блоком
    merge_with_next(block);
}

void memdefrag() {
    // В этой реализации дефрагментация выполняется при освобождении (merge_with_next)
    // Дополнительная дефрагментация может быть реализована при необходимости
    #if DEBUG
    printf("Defragmentation not fully implemented in this version\n");
    #endif
}

void memstat() {
    printf("\n=== Memory Statistics ===\n");
    printf("Total pool size: %zu bytes\n", pool_size);
    
    size_t total_free = 0;
    size_t total_used = 0;
    int free_blocks = 0;
    int used_blocks = 0;
    
    // Считаем статистику по свободным блокам
    BlockHeader* current = free_list;
    while (current) {
        total_free += current->size;
        free_blocks++;
        current = current->next;
    }
    
    // Считаем статистику по всем блокам
    current = (BlockHeader*)memory_pool;
    while (current && (char*)current < (char*)memory_pool + pool_size) {
        if (!current->is_free) {
            total_used += current->size;
            used_blocks++;
        }
        current = get_next_block(current);
    }
    
    printf("Used memory: %zu bytes (%d blocks)\n", total_used, used_blocks);
    printf("Free memory: %zu bytes (%d blocks)\n", total_free, free_blocks);
    printf("Fragmentation: %.2f%%\n", 
           (free_blocks > 1 ? (1.0 - (float)total_free / pool_size) * 100 : 0.0));
    printf("=========================\n");
}