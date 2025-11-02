
#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

extern "C" {
#include "queue_list.h"
#include "queue_arr.h"
}



TEST(QueueListTest, CreateEmptyQueue) {
    QueueList* queue = create_queue_list();
    EXPECT_TRUE(is_empty(queue));
    EXPECT_EQ(size(queue), 0);
    destroy_queue(queue);
}

TEST(QueueListTest, EnqueueOne) {
    QueueList* queue = create_queue_list();
    enqueue(queue, 10);
    EXPECT_FALSE(is_empty(queue));
    EXPECT_EQ(size(queue), 1);

    int status;
    EXPECT_EQ(peak(queue, &status), 10);
    EXPECT_EQ(status, 1);
    destroy_queue(queue);
}

TEST(QueueListTest, FIFO) {
    QueueList* queue = create_queue_list();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    int status;
    EXPECT_EQ(dequeue(queue, &status), 1);
    EXPECT_EQ(dequeue(queue, &status), 2);
    EXPECT_EQ(dequeue(queue, &status), 3);
    EXPECT_TRUE(is_empty(queue));
    destroy_queue(queue);
}

TEST(QueueListTest, DequeueToEmpty) {
    QueueList* queue = create_queue_list();
    enqueue(queue, 5);
    int status;
    EXPECT_EQ(dequeue(queue, &status), 5);
    EXPECT_TRUE(is_empty(queue));
    EXPECT_EQ(size(queue), 0);
    destroy_queue(queue);
}

TEST(QueueListTest, PeekEmpty) {
    QueueList* queue = create_queue_list();
    int status;
    int value = peak(queue, &status);
    EXPECT_EQ(status, 0);
    EXPECT_EQ(value, 0);
    destroy_queue(queue);
}

TEST(QueueListTest, DifferentOperations) {
    QueueList* queue = create_queue_list();
    int status;

    enqueue(queue, 1);
    EXPECT_EQ(dequeue(queue, &status), 1);

    enqueue(queue, 2);
    enqueue(queue, 3);

    EXPECT_EQ(peak(queue, &status), 2);
    EXPECT_EQ(size(queue), 2);

    EXPECT_EQ(dequeue(queue, &status), 2);
    EXPECT_EQ(dequeue(queue, &status), 3);
    EXPECT_TRUE(is_empty(queue));
    destroy_queue(queue);
}

TEST(QueueArrayTest, CreateEmptyQueue) {
    QueueArray* queue = create_queue_array(5);
    ASSERT_NE(queue, nullptr);
    EXPECT_TRUE(is_empty_array(queue));
    EXPECT_FALSE(is_full_array(queue));
    EXPECT_EQ(size_array(queue), 0);
    destroy_queue_array(queue);
}

TEST(QueueArrayTest, EnqueuOne) {
    QueueArray* queue = create_queue_array(3);
    int status = -1;
    enqueue_array(queue, 10, &status);
    EXPECT_EQ(status, 1);
    EXPECT_FALSE(is_empty_array(queue));
    EXPECT_EQ(size_array(queue), 1);
    EXPECT_EQ(peak_array(queue, &status), 10);
    EXPECT_EQ(status, 1);
    destroy_queue_array(queue);
}

TEST(QueueArrayTest, FIFOOrder_no3) {
    QueueArray* queue = create_queue_array(5);
    int status;
    enqueue_array(queue, 1, &status); EXPECT_EQ(status, 1);
    enqueue_array(queue, 2, &status);
    enqueue_array(queue, 3, &status);
    EXPECT_EQ(dequeue_array(queue, &status), 1); EXPECT_EQ(status, 1);
    EXPECT_EQ(dequeue_array(queue, &status), 2); 
    EXPECT_EQ(dequeue_array(queue, &status), 3);
    EXPECT_TRUE(is_empty_array(queue));
    EXPECT_EQ(size_array(queue), 0);
    destroy_queue_array(queue);
}

TEST(QueueArrayTest, WrapAround_no4) {
    QueueArray* queue = create_queue_array(3);
    int status;
    enqueue_array(queue, 10, &status); EXPECT_EQ(status, 1);
    enqueue_array(queue, 20, &status); 
    enqueue_array(queue, 30, &status);
    EXPECT_TRUE(is_full_array(queue));
    EXPECT_EQ(dequeue_array(queue, &status), 10); EXPECT_EQ(status, 1);
    enqueue_array(queue, 40, &status); EXPECT_EQ(status, 1);
    EXPECT_TRUE(is_full_array(queue));
    EXPECT_EQ(size_array(queue), 3);
    EXPECT_EQ(dequeue_array(queue, &status), 20); 
    EXPECT_EQ(dequeue_array(queue, &status), 30); 
    EXPECT_EQ(dequeue_array(queue, &status), 40); EXPECT_EQ(status, 1);
    EXPECT_TRUE(is_empty_array(queue));
    destroy_queue_array(queue);
}

TEST(QueueArrayTest, FullQueueEnqueueBlocked_no5) {
    QueueArray* queue = create_queue_array(2);
    int status;
    enqueue_array(queue, 7, &status); EXPECT_EQ(status, 1);
    enqueue_array(queue, 8, &status); 
    EXPECT_TRUE(is_full_array(queue));
    enqueue_array(queue, 9, &status); EXPECT_EQ(status, 0);
    EXPECT_TRUE(is_full_array(queue));
    EXPECT_EQ(size_array(queue), 2);
    EXPECT_EQ(dequeue_array(queue, &status), 7);
    EXPECT_EQ(dequeue_array(queue, &status), 8); EXPECT_EQ(status, 1);
    EXPECT_TRUE(is_empty_array(queue));
    destroy_queue_array(queue);
}

TEST(QueueArrayTest, EmptySafety_no6) {
    QueueArray* queue = create_queue_array(4);
    int status = 123;
    int peekValue = peak_array(queue, &status);
    EXPECT_EQ(status, 0);
    EXPECT_EQ(peekValue, 0);
    status = 999;
    int dequeuedValue = dequeue_array(queue, &status);
    EXPECT_EQ(status, 0);
    EXPECT_EQ(dequeuedValue, 0);
    destroy_queue_array(queue);
}
