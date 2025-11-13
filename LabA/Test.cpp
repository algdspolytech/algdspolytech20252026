#include <gtest/gtest.h>

extern "C" {
#include "queue.h"
}

// 1. Очередь пуста после создания
TEST(PriorityQueueTest, EmptyAfterCreation) {
    Q* pq = NULL;
    EXPECT_TRUE(isEmpty(pq));
}

// 2. Вставка одного элемента
TEST(PriorityQueueTest, InsertOne) {
    Q* pq = NULL;
    insert(&pq, 10, 1);
    EXPECT_FALSE(isEmpty(pq));
    EXPECT_EQ(peek(pq), 10);
}

// 3. Вставка нескольких элементов с разным приоритетом
TEST(PriorityQueueTest, InsertMultiple) {
    Q* pq = NULL;
    insert(&pq, 10, 2);
    insert(&pq, 5, 1);
    insert(&pq, 20, 3);
    EXPECT_EQ(peek(pq), 5);  // минимальный приоритет = 1
}

// 4. Удаление элемента
TEST(PriorityQueueTest, DequeueOne) {
    Q* pq = NULL;
    insert(&pq, 10, 1);
    dequeue(&pq);
    EXPECT_TRUE(isEmpty(pq));
}

// 5. Очередь остается корректной после нескольких удалений
TEST(PriorityQueueTest, DequeueMultiple) {
    Q* pq = NULL;
    insert(&pq, 10, 2);
    insert(&pq, 5, 1);
    insert(&pq, 20, 3);
    dequeue(&pq);
    EXPECT_EQ(peek(pq), 10);
    dequeue(&pq);
    EXPECT_EQ(peek(pq), 20);
    dequeue(&pq);
    EXPECT_TRUE(isEmpty(pq));
}

// 6. Peek на пустой очереди
TEST(PriorityQueueTest, PeekEmpty) {
    Q* pq = NULL;
    EXPECT_EQ(peek(pq), -1);
}

// 7. Вставка элементов с одинаковым приоритетом
TEST(PriorityQueueTest, InsertSamePriority) {
    Q* pq = NULL;
    insert(&pq, 1, 1);
    insert(&pq, 2, 1);
    insert(&pq, 3, 1);
    EXPECT_EQ(peek(pq), 1);
    dequeue(&pq);
    EXPECT_EQ(peek(pq), 2);
}

// 8. Проверка isEmpty после вставки и удаления
TEST(PriorityQueueTest, EmptyAfterInsertDequeue) {
    Q* pq = NULL;
    insert(&pq, 10, 1);
    EXPECT_FALSE(isEmpty(pq));
    dequeue(&pq);
    EXPECT_TRUE(isEmpty(pq));
}

// 9. Вставка в пустую очередь
TEST(PriorityQueueTest, InsertIntoEmpty) {
    Q* pq = NULL;
    insert(&pq, 42, 5);
    EXPECT_EQ(peek(pq), 42);
}

// 10. Множественные вставки и проверки приоритета
TEST(PriorityQueueTest, PriorityOrder) {
    Q* pq = NULL;
    insert(&pq, 1, 3);
    insert(&pq, 2, 2);
    insert(&pq, 3, 1);
    EXPECT_EQ(peek(pq), 3);
    dequeue(&pq);
    EXPECT_EQ(peek(pq), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
