#include "gtest/gtest.h"
#include "pch.h"

extern "C" {
#include "queue.h"
}

// 1. Добавление элемента в пустую очередь (массив)
TEST(ArrayQueueTest, AddToEmptyQueue_no1) {
  Queue q;
  initializeQueue(&q);
  enqueue(&q, 10);
  EXPECT_EQ(peek(&q), 10);
}

// 2. Удаление элемента, проверка FIFO (массив)
TEST(ArrayQueueTest, AddSeveral_no2) {
  Queue q;
  initializeQueue(&q);
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  EXPECT_EQ(peek(&q), 1);
  EXPECT_EQ(dequeue(&q), 1);
  EXPECT_EQ(peek(&q), 2);
}

// 3. Проверка, что удаление возвращает удаленное значение (массив)
TEST(ArrayQueueTest, Dequeue_no3) {
  Queue q;
  initializeQueue(&q);
  enqueue(&q, 5);
  int val = dequeue(&q);
  EXPECT_EQ(val, 5);
}

// 4. Проверка, что функция peek показывает первый элемент, не удаляя его
// (массив)
TEST(ArrayQueueTest, Peek_no4) {
  Queue q;
  initializeQueue(&q);
  enqueue(&q, 42);
  EXPECT_EQ(peek(&q), 42);
  EXPECT_EQ(peek(&q), 42);  // peek не удаляет элемент
}

// 5. Проверка, что при удалении из пустой очереди возвращает -1 (массив)
TEST(ArrayQueueTest, DequeueFromEmpty_no5) {
  Queue q;
  initializeQueue(&q);
  EXPECT_EQ(dequeue(&q), -1);
}

// 6. Добавление элемента в пустую очередь (связной список)
TEST(ListQueueTest, AddToEmptyQueue_no6) {
  QueueList q{nullptr, nullptr};
  enqueueList(&q, 10);
  EXPECT_EQ(peekList(&q), 10);
}

// 7. Проверяет порядок элементов и корректное движение указателя front (связной
// список)
TEST(ListQueueTest, AddSeveral_no7) {
  QueueList q{nullptr, nullptr};
  enqueueList(&q, 1);
  enqueueList(&q, 2);
  enqueueList(&q, 3);
  EXPECT_EQ(peekList(&q), 1);
  EXPECT_EQ(dequeueList(&q), 1);
  EXPECT_EQ(peekList(&q), 2);
}

// 8. Проверяет, что функция dequeue удаляет нужное значение и освобождает
// память (связной список)
TEST(ListQueueTest, Dequeue_no8) {
  QueueList q{nullptr, nullptr};
  enqueueList(&q, 5);
  int val = dequeueList(&q);
  EXPECT_EQ(val, 5);
}

// 9. Проверяет, что peek не удаляет элемент, а только показывает (связной
// список)
TEST(ListQueueTest, Peek_no9) {
  QueueList q{nullptr, nullptr};
  enqueueList(&q, 100);
  EXPECT_EQ(peekList(&q), 100);
  EXPECT_EQ(peekList(&q), 100);  // не должен удалять
}

// 10. Проверяет, что программа не "ломается" при удалении из пустой очереди
// (связной список)
TEST(ListQueueTest, DequeueFromEmpty_no10) {
  QueueList q{nullptr, nullptr};
  EXPECT_EQ(dequeueList(&q), -1);
}

// 11. Проверяет очистку структуры после серии удалений (связной список)
TEST(ListQueueTest, MultipleDequeueUntilEmpty_no11) {
  QueueList q{nullptr, nullptr};
  enqueueList(&q, 1);
  enqueueList(&q, 2);
  enqueueList(&q, 3);

  EXPECT_EQ(dequeueList(&q), 1);
  EXPECT_EQ(dequeueList(&q), 2);
  EXPECT_EQ(dequeueList(&q), 3);

  EXPECT_TRUE(isEmptyList(&q));  // очередь должна быть пустой
  EXPECT_EQ(q.front, nullptr);
  EXPECT_EQ(q.rear, nullptr);
}

// 12. Проверяет, что очередь не "ломается" при переполнении (массив)
TEST(ArrayQueueTest, FillAndOverflow_no11) {
  Queue q;
  initializeQueue(&q);
  for (int i = 0; i < SIZE; i++) {
    enqueue(&q, i);
  }

  EXPECT_TRUE(isFull(&q));
  int prevRear = q.rear;
  enqueue(&q, 999);
  EXPECT_EQ(q.rear, prevRear);  // rear не должен увеличиться
}
