#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 4096
#define TEST_ITERATIONS 1000
#define MAX_ALLOC_SIZE 512

// Тест корректности
void test_correctness() {
    printf("=== Correctness Test ===\n");
    
    char buffer[BUFFER_SIZE];
    
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

// Простой тест производительности
void test_performance() {
    printf("\n=== Performance Test ===\n");
    
    // Выделяем буфер для аллокатора
    void* buffer = malloc(BUFFER_SIZE * 10); // 40KB
    if (!buffer) {
        printf("Failed to allocate buffer\n");
        return;
    }
    
    // Инициализируем аллокатор
    if (meminit(buffer, BUFFER_SIZE * 10) != 0) {
        printf("Failed to initialize allocator\n");
        free(buffer);
        return;
    }
    
    void* pointers[TEST_ITERATIONS];
    int pointer_count = 0;
    
    clock_t start = clock();
    
    srand(time(NULL));
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        if (pointer_count < TEST_ITERATIONS && (rand() % 100 < 70 || pointer_count == 0)) {
            // Аллокация (70% вероятности)
            size_t size = (rand() % MAX_ALLOC_SIZE) + 1;
            pointers[pointer_count] = memalloc(size);
            if (pointers[pointer_count]) {
                pointer_count++;
            }
        } else if (pointer_count > 0) {
            // Освобождение (30% вероятности)
            int idx = rand() % pointer_count;
            memfree(pointers[idx]);
            pointers[idx] = pointers[pointer_count - 1];
            pointer_count--;
        }
    }
    
    // Освобождение оставшейся памяти
    for (int i = 0; i < pointer_count; i++) {
        memfree(pointers[i]);
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Custom allocator time: %.4f seconds\n", time_spent);
    memstat();
    
    free(buffer);
}

int main() {
    printf("Memory Allocator (Best Fit, Doubly Linked List)\n");
    printf("===============================================\n");
    
    // Тест корректности
    test_correctness();
    
    // Тест производительности
    test_performance();
    
    return 0;
}
