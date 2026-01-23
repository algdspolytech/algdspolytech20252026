#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE (10 * 1024 * 1024)  // 10 MB
#define TEST_ITERATIONS 10000
#define MAX_ALLOC_SIZE 2048

// Тестирование стандартного malloc/free
void test_standard_malloc(int iterations) {
    printf("Testing standard malloc/free...\n");
    
    void* pointers[TEST_ITERATIONS];
    int sizes[TEST_ITERATIONS];
    int pointer_count = 0;
    
    clock_t start = clock();
    
    for (int i = 0; i < iterations; i++) {
        if (pointer_count < TEST_ITERATIONS && (rand() % 100 < 60 || pointer_count == 0)) {
            // Аллокация (60% вероятности)
            sizes[pointer_count] = (rand() % MAX_ALLOC_SIZE) + 1;
            pointers[pointer_count] = malloc(sizes[pointer_count]);
            if (pointers[pointer_count]) {
                memset(pointers[pointer_count], i % 256, sizes[pointer_count]);
                pointer_count++;
            }
        } else if (pointer_count > 0) {
            // Освобождение (40% вероятности)
            int idx = rand() % pointer_count;
            free(pointers[idx]);
            pointers[idx] = pointers[pointer_count - 1];
            sizes[idx] = sizes[pointer_count - 1];
            pointer_count--;
        }
    }
    
    // Освобождение оставшейся памяти
    for (int i = 0; i < pointer_count; i++) {
        free(pointers[i]);
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Standard malloc/free time: %.4f seconds\n", time_spent);
}

// Тестирование пользовательского аллокатора
void test_custom_allocator(int iterations) {
    printf("Testing custom memory allocator...\n");
    
    // Выделяем буфер для аллокатора
    void* buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        printf("Failed to allocate buffer for custom allocator\n");
        return;
    }
    
    // Инициализируем аллокатор
    if (meminit(buffer, BUFFER_SIZE) != 0) {
        printf("Failed to initialize memory allocator\n");
        free(buffer);
        return;
    }
    
    void* pointers[TEST_ITERATIONS];
    int sizes[TEST_ITERATIONS];
    int pointer_count = 0;
    
    clock_t start = clock();
    
    for (int i = 0; i < iterations; i++) {
        if (pointer_count < TEST_ITERATIONS && (rand() % 100 < 60 || pointer_count == 0)) {
            // Аллокация (60% вероятности)
            sizes[pointer_count] = (rand() % MAX_ALLOC_SIZE) + 1;
            pointers[pointer_count] = memalloc(sizes[pointer_count]);
            if (pointers[pointer_count]) {
                memset(pointers[pointer_count], i % 256, sizes[pointer_count]);
                pointer_count++;
            }
        } else if (pointer_count > 0) {
            // Освобождение (40% вероятности)
            int idx = rand() % pointer_count;
            memfree(pointers[idx]);
            pointers[idx] = pointers[pointer_count - 1];
            sizes[idx] = sizes[pointer_count - 1];
            pointer_count--;
        }
    }
    
    // Освобождение оставшейся памяти
    for (int i = 0; i < pointer_count; i++) {
        memfree(pointers[i]);
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Выводим статистику
    memstat();
    
    printf("Custom allocator time: %.4f seconds\n", time_spent);
    
    free(buffer);
}

// Тест корректности работы аллокатора
void test_correctness() {
    printf("\n=== Correctness Test ===\n");
    
    // Выделяем буфер для аллокатора
    char buffer[4096];
    
    if (meminit(buffer, sizeof(buffer)) != 0) {
        printf("Init failed\n");
        return;
    }
    
    printf("Allocating blocks...\n");
    
    // Выделяем несколько блоков
    char* ptr1 = memalloc(100);
    char* ptr2 = memalloc(200);
    char* ptr3 = memalloc(50);
    
    if (ptr1 && ptr2 && ptr3) {
        printf("All allocations successful\n");
        
        // Записываем данные
        strcpy(ptr1, "Hello");
        strcpy(ptr2, "World");
        strcpy(ptr3, "Test");
        
        printf("ptr1: %s\n", ptr1);
        printf("ptr2: %s\n", ptr2);
        printf("ptr3: %s\n", ptr3);
        
        // Освобождаем средний блок
        printf("\nFreeing middle block...\n");
        memfree(ptr2);
        memstat();
        
        // Выделяем блок другого размера
        printf("\nAllocating new block...\n");
        char* ptr4 = memalloc(150);
        if (ptr4) {
            strcpy(ptr4, "NewBlock");
            printf("ptr4: %s\n", ptr4);
        }
        
        memstat();
        
        // Освобождаем все
        memfree(ptr1);
        memfree(ptr3);
        if (ptr4) memfree(ptr4);
        
        printf("\nAll blocks freed\n");
        memstat();
    } else {
        printf("Allocation failed\n");
    }
}

int main() {
    srand(time(NULL));
    
    printf("Memory Allocator Testing (Best Fit, Doubly Linked List)\n");
    printf("=======================================================\n\n");
    
    // Тест корректности
    test_correctness();
    
    printf("\n\n=== Performance Comparison ===\n");
    
    // Тест производительности
    test_standard_malloc(TEST_ITERATIONS);
    test_custom_allocator(TEST_ITERATIONS);
    
    return 0;
}