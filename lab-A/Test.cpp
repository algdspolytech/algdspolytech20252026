#include <gtest/gtest.h>
#include <limits.h>
extern "C" {
#include "queue.h"
}

// Тесты для очереди на связном списке

TEST(ListQueueTest, CreateAndDestroy_no1) {
    ListQueue* queue = list_queue_create();
    ASSERT_NE(queue, nullptr);
    EXPECT_TRUE(list_queue_is_empty(queue));
    EXPECT_EQ(list_queue_size(queue), 0);
    list_queue_destroy(queue);
}

TEST(ListQueueTest, EnqueueSingleElement_no2) {
    ListQueue* queue = list_queue_create();
    list_queue_enqueue(queue, 42);

    EXPECT_FALSE(list_queue_is_empty(queue));
    EXPECT_EQ(list_queue_size(queue), 1);
    EXPECT_EQ(list_queue_peek(queue), 42);

    list_queue_destroy(queue);
}

TEST(ListQueueTest, EnqueueDequeueMultipleElements_no3) {
    ListQueue* queue = list_queue_create();

    // Добавляем 5 элементов
    for (int i = 1; i <= 5; i++) {
        list_queue_enqueue(queue, i * 10);
    }

    EXPECT_EQ(list_queue_size(queue), 5);
    EXPECT_EQ(list_queue_peek(queue), 10);

    // Извлекаем 2 элемента
    EXPECT_EQ(list_queue_dequeue(queue), 10);
    EXPECT_EQ(list_queue_dequeue(queue), 20);
    EXPECT_EQ(list_queue_size(queue), 3);

    list_queue_destroy(queue);
}

TEST(ListQueueTest, DequeueFromEmptyQueue_no4) {
    ListQueue* queue = list_queue_create();

    EXPECT_EQ(list_queue_dequeue(queue), -1);
    EXPECT_TRUE(list_queue_is_empty(queue));

    list_queue_destroy(queue);
}

TEST(ListQueueTest, PeekFromEmptyQueue_no5) {
    ListQueue* queue = list_queue_create();

    EXPECT_EQ(list_queue_peek(queue), -1);

    list_queue_destroy(queue);
}

TEST(ListQueueTest, MixedOperationsComplexScenario_no6) {
    ListQueue* queue = list_queue_create();

    // Сложный сценарий: добавление, удаление, снова добавление
    list_queue_enqueue(queue, 1);
    list_queue_enqueue(queue, 2);
    EXPECT_EQ(list_queue_dequeue(queue), 1);

    list_queue_enqueue(queue, 3);
    list_queue_enqueue(queue, 4);
    EXPECT_EQ(list_queue_dequeue(queue), 2);
    EXPECT_EQ(list_queue_dequeue(queue), 3);

    EXPECT_EQ(list_queue_peek(queue), 4);
    EXPECT_EQ(list_queue_size(queue), 1);

    // Добавляем еще после почти полной очистки
    list_queue_enqueue(queue, 5);
    list_queue_enqueue(queue, 6);
    EXPECT_EQ(list_queue_size(queue), 3);

    list_queue_destroy(queue);
}

TEST(ListQueueTest, LargeNumberOfElements_no7) {
    ListQueue* queue = list_queue_create();
    const int NUM_ELEMENTS = 1000;

    // Добавляем много элементов
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        list_queue_enqueue(queue, i);
    }

    EXPECT_EQ(list_queue_size(queue), NUM_ELEMENTS);

    // Проверяем порядок извлечения
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        EXPECT_EQ(list_queue_dequeue(queue), i);
    }

    EXPECT_TRUE(list_queue_is_empty(queue));
    list_queue_destroy(queue);
}

// Тесты для очереди на массиве

TEST(ArrayQueueTest, CreateAndDestroy_no8) {
    ArrayQueue* queue = array_queue_create(5);
    ASSERT_NE(queue, nullptr);
    EXPECT_TRUE(array_queue_is_empty(queue));
    EXPECT_EQ(array_queue_size(queue), 0);
    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, EnqueueSingleElement_no9) {
    ArrayQueue* queue = array_queue_create(3);
    array_queue_enqueue(queue, 100);

    EXPECT_FALSE(array_queue_is_empty(queue));
    EXPECT_EQ(array_queue_size(queue), 1);
    EXPECT_EQ(array_queue_peek(queue), 100);

    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, EnqueueToFullCapacity_no10) {
    ArrayQueue* queue = array_queue_create(3);

    array_queue_enqueue(queue, 10);
    array_queue_enqueue(queue, 20);
    array_queue_enqueue(queue, 30);

    EXPECT_TRUE(array_queue_is_full(queue));
    EXPECT_EQ(array_queue_size(queue), 3);
    EXPECT_EQ(array_queue_peek(queue), 10);

    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, CircularBehaviorWithWrapAround_no11) {
    ArrayQueue* queue = array_queue_create(3);

    // Заполняем очередь
    array_queue_enqueue(queue, 1);
    array_queue_enqueue(queue, 2);
    array_queue_enqueue(queue, 3);

    // Освобождаем место
    EXPECT_EQ(array_queue_dequeue(queue), 1);

    // Добавляем новый элемент - должен использовать освободившееся место
    array_queue_enqueue(queue, 4);

    EXPECT_EQ(array_queue_peek(queue), 2);
    EXPECT_EQ(array_queue_size(queue), 3);
    EXPECT_TRUE(array_queue_is_full(queue));

    // Проверяем порядок извлечения
    EXPECT_EQ(array_queue_dequeue(queue), 2);
    EXPECT_EQ(array_queue_dequeue(queue), 3);
    EXPECT_EQ(array_queue_dequeue(queue), 4);

    EXPECT_TRUE(array_queue_is_empty(queue));
    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, DequeueFromEmptyArrayQueue_no12) {
    ArrayQueue* queue = array_queue_create(5);

    EXPECT_EQ(array_queue_dequeue(queue), -1);
    EXPECT_TRUE(array_queue_is_empty(queue));

    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, PeekFromEmptyArrayQueue_no13) {
    ArrayQueue* queue = array_queue_create(5);

    EXPECT_EQ(array_queue_peek(queue), -1);

    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, ComplexArrayOperations_no14) {
    ArrayQueue* queue = array_queue_create(4);

    array_queue_enqueue(queue, 10);
    array_queue_enqueue(queue, 20);
    EXPECT_EQ(array_queue_dequeue(queue), 10);

    array_queue_enqueue(queue, 30);
    array_queue_enqueue(queue, 40);
    EXPECT_EQ(array_queue_dequeue(queue), 20);

    array_queue_enqueue(queue, 50);

    EXPECT_EQ(array_queue_size(queue), 3);
    EXPECT_EQ(array_queue_peek(queue), 30);

    // Проверяем полное извлечение
    EXPECT_EQ(array_queue_dequeue(queue), 30);
    EXPECT_EQ(array_queue_dequeue(queue), 40);
    EXPECT_EQ(array_queue_dequeue(queue), 50);

    EXPECT_TRUE(array_queue_is_empty(queue));
    array_queue_destroy(queue);
}

TEST(ArrayQueueTest, BoundaryConditions_no15) {
    ArrayQueue* queue = array_queue_create(2);

    // Граничный случай: добавление в почти полную очередь
    array_queue_enqueue(queue, 1);
    array_queue_enqueue(queue, 2);

    // Попытка добавления в полную очередь
    array_queue_enqueue(queue, 3); // Должно проигнорироваться

    EXPECT_EQ(array_queue_size(queue), 2);
    EXPECT_TRUE(array_queue_is_full(queue));

    array_queue_destroy(queue);
}

// Сравнительные тесты

TEST(ComparisonTest, BothQueuesSameBehavior_no16) {
    ListQueue* listQueue = list_queue_create();
    ArrayQueue* arrayQueue = array_queue_create(10);

    // Одинаковые операции для обеих очередей
    for (int i = 1; i <= 5; i++) {
        list_queue_enqueue(listQueue, i);
        array_queue_enqueue(arrayQueue, i);
    }

    EXPECT_EQ(list_queue_size(listQueue), array_queue_size(arrayQueue));

    for (int i = 1; i <= 3; i++) {
        EXPECT_EQ(list_queue_dequeue(listQueue), array_queue_dequeue(arrayQueue));
    }

    EXPECT_EQ(list_queue_size(listQueue), array_queue_size(arrayQueue));

    list_queue_destroy(listQueue);
    array_queue_destroy(arrayQueue);
}

TEST(EdgeCaseTest, ZeroCapacityArrayQueue_no17) {
    ArrayQueue* queue = array_queue_create(0);
    EXPECT_EQ(queue, nullptr);
}

TEST(EdgeCaseTest, NegativeCapacityArrayQueue_no18) {
    ArrayQueue* queue = array_queue_create(-5);
    EXPECT_EQ(queue, nullptr);
}

TEST(EdgeCaseTest, MemoryAllocationFailure_no19) {
    // Тест на обработку крайних случаев с памятью
    ListQueue* listQueue = list_queue_create();
    ASSERT_NE(listQueue, nullptr);

    // Пытаемся добавить элемент (в нормальных условиях должно работать)
    list_queue_enqueue(listQueue, 42);
    EXPECT_EQ(list_queue_size(listQueue), 1);

    list_queue_destroy(listQueue);
}

TEST(PerformanceTest, SequentialOperations_no20) {
    ListQueue* listQueue = list_queue_create();
    ArrayQueue* arrayQueue = array_queue_create(1000);

    // Последовательные операции для проверки стабильности
    for (int i = 0; i < 100; i++) {
        list_queue_enqueue(listQueue, i);
        array_queue_enqueue(arrayQueue, i);

        if (i % 10 == 0) {
            list_queue_dequeue(listQueue);
            array_queue_dequeue(arrayQueue);
        }
    }

    // Обе очереди должны быть в согласованном состоянии
    EXPECT_GT(list_queue_size(listQueue), 0);
    EXPECT_GT(array_queue_size(arrayQueue), 0);

    list_queue_destroy(listQueue);
    array_queue_destroy(arrayQueue);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}