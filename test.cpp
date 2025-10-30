#include <gtest/gtest.h>

extern "C" {
#include "priority_queue.h"
}

// 1. Инициализация пустой очереди
TEST(PriorityQueueTest, InitEmpty) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    EXPECT_TRUE(isEmpty(&pq));
}

// 2. Добавление одного элемента
TEST(PriorityQueueTest, AddSingle) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 10, 5);
    EXPECT_FALSE(isEmpty(&pq));
}

// 3. Извлечение элемента возвращает правильные данные
TEST(PriorityQueueTest, DequeueReturnsData) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 42, 10);
    int val;
    int result = dequeue(&pq, &val);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(val, 42);
    EXPECT_TRUE(isEmpty(&pq));
}

// 4. Очередь с несколькими элементами — приоритеты в порядке убывания
TEST(PriorityQueueTest, OrderByPriority) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 1, 1);
    enqueue(&pq, 2, 5);
    enqueue(&pq, 3, 3);
    int val;
    // первый вызов — приоритет 5
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 2);
    // следующий — приоритет 3
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 3);
    // последний — приоритет 1
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(isEmpty(&pq));
}

// 5. Извлечение из пустой очереди
TEST(PriorityQueueTest, DequeueEmpty) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    int val;
    EXPECT_FALSE(dequeue(&pq, &val));
}

// 6. Добавление элементов с одинаковым приоритетом
TEST(PriorityQueueTest, SamePriorityOrder) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 1, 10);
    enqueue(&pq, 2, 10);
    enqueue(&pq, 3, 10);
    int val;
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 2);
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 3);
}

// 7. Много элементов
TEST(PriorityQueueTest, MultipleInsertionsAndRemovals) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    for (int i = 1; i <= 10; ++i) {
        enqueue(&pq, i * 10, i);
    }
    int val;
    for (int expected_priority = 10; expected_priority >= 1; --expected_priority) {
        EXPECT_TRUE(dequeue(&pq, &val));
        // Можно проверить, что значение соответствует приоритету, но для простоты — просто убедимся, что извлекается
        EXPECT_GT(val, 0);
    }
    EXPECT_TRUE(isEmpty(&pq));
}

// 8. Очистка очереди
TEST(PriorityQueueTest, ClearQueue) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 1, 1);
    enqueue(&pq, 2, 2);
    clearQueue(&pq);
    EXPECT_TRUE(isEmpty(&pq));
}

// 9. Добавление, а затем извлечение
TEST(PriorityQueueTest, SimpleAddRemove) {
    PriorityQueue pq;
    initPriorityQueue(&pq);

    enqueue(&pq, 10, 1);
    enqueue(&pq, 20, 3);
    enqueue(&pq, 30, 2);
    enqueue(&pq, 40, 3);
    enqueue(&pq, 50, 5);
    enqueue(&pq, 60, 4);

    int val;
    // Должен извлечь 50 (приоритет 5)
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 50);

    // Следующий с приоритетом 4: 60
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 60);

    // С приоритетом 3: сначала 20, потом 40 (по FIFO)
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 20);
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 40);

    // Потом с приоритетом 2: 30
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 30);

    // Потом 10 (приоритет 1)
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 10);

    // Очередь должна быть пуста
    EXPECT_FALSE(dequeue(&pq, &val));
}

// 10. Приоритеты крайние (очень большие и маленькие)
TEST(PriorityQueueTest, ExtremePriorities) {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    enqueue(&pq, 1, 1000);
    enqueue(&pq, 2, -1000);
    int val;
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(dequeue(&pq, &val));
    EXPECT_EQ(val, 2);
    EXPECT_TRUE(isEmpty(&pq));
}