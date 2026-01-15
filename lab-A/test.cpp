#include <gtest/gtest.h>
#include "main.h"

// -------------- ARRAY QUEUE TESTS --------------

class ArrayQueueTest : public ::testing::Test
{
protected:
    ArrayQueue queue;

    void SetUp() override
    {
        create_array(&queue, 10);
    }

    void TearDown() override
    {
        free_array(&queue);
    }
};

TEST_F(ArrayQueueTest, Init_ArrayQueue_no1)
{
    ASSERT_NE(queue.arr, nullptr);
    ASSERT_EQ(queue.capacity, 10);
    ASSERT_EQ(queue.first, 0);
    ASSERT_EQ(queue.last, -1);
    ASSERT_EQ(queue.size, 0);
}

TEST_F(ArrayQueueTest, AddOneValue_ArrayQueue_no2)
{
    add_array(&queue, 10);

    ASSERT_EQ(queue.size, 1);
    ASSERT_EQ(queue.first, 0);
    ASSERT_EQ(queue.last, 0);
    ASSERT_EQ(queue.arr[0], 10);
}

TEST_F(ArrayQueueTest, AddManyValues_ArrayQueue_no3)
{
    for (int i = 1; i < 12; i++)
    {
        add_array(&queue, 10 * i);
    }

    ASSERT_EQ(queue.first, 0);
    ASSERT_EQ(queue.last, 9);
    ASSERT_EQ(queue.size, 10);
    ASSERT_EQ(queue.arr[queue.last], 100);
}

TEST_F(ArrayQueueTest, DelOneValue_ArrayQueue_no4)
{
    add_array(&queue, 10);
    del_array(&queue);

    ASSERT_EQ(queue.size, 0);
    ASSERT_EQ(queue.first, 1);
    ASSERT_EQ(queue.last, 0);
}

TEST_F(ArrayQueueTest, CircularBehavior_ArrayQueue_no5)
{
    for (int i = 1; i < 10; i++)
    {
        add_array(&queue, i * 10);
    }
    del_array(&queue);

    add_array(&queue, 30);
    add_array(&queue, 40);

    ASSERT_EQ(queue.size, 10);
    ASSERT_EQ(queue.first, 1);
    ASSERT_EQ(queue.last, 0);
}

TEST_F(ArrayQueueTest, DelEmpty_ArrayQueue_no6)
{
    ASSERT_EQ(del_array(&queue), -1);
    ASSERT_EQ(queue.size, 0);
    ASSERT_EQ(queue.first, 0);
    ASSERT_EQ(queue.last, -1);
    ASSERT_NE(queue.arr, nullptr);
}

TEST_F(ArrayQueueTest, Free_ArrayQueue_no7)
{
    add_array(&queue, 10);
    add_array(&queue, 20);

    free_array(&queue);

    ASSERT_EQ(queue.arr, nullptr);
    ASSERT_EQ(queue.capacity, 0);
    ASSERT_EQ(queue.first, 0);
    ASSERT_EQ(queue.last, -1);
    ASSERT_EQ(queue.size, 0);
}

// -------------- LINKED LIST QUEUE TESTS --------------

class LinkedListQueueTest : public ::testing::Test
{
protected:
    LinkedListQueue queue;

    void SetUp() override
    {
        create_linked_list(&queue);
    }

    void TearDown() override
    {
        free_linked_list(&queue);
    }
};

TEST_F(LinkedListQueueTest, InitLinked_ListQueue_no8)
{
    ASSERT_EQ(queue.first, nullptr);
    ASSERT_EQ(queue.last, nullptr);
}

TEST_F(LinkedListQueueTest, AddValues_LinkedListQueue_no9)
{
    add_linked_list(&queue, 10);
    add_linked_list(&queue, 20);

    ASSERT_NE(queue.first, nullptr);
    ASSERT_NE(queue.last, nullptr);
    ASSERT_EQ(queue.first->data, 10);
    ASSERT_EQ(queue.first->next->data, 20);
}

TEST_F(LinkedListQueueTest, DelValue_LinkedListQueue_no10)
{
    for (int i = 1; i < 12; i++)
    {
        add_linked_list(&queue, 10 * i);
    }

    ASSERT_EQ(del_linked_list(&queue), 10);
    ASSERT_NE(queue.first, nullptr);
    ASSERT_NE(queue.last, nullptr);
    ASSERT_EQ(queue.first->data, 20);
}

TEST_F(LinkedListQueueTest, DelEmpty_LinkedListQueue_no11)
{
    ASSERT_EQ(del_linked_list(&queue), -1);
    ASSERT_EQ(queue.first, nullptr);
    ASSERT_EQ(queue.last, nullptr);
}

TEST_F(LinkedListQueueTest, Free_LinkedListQueue_no12)
{
    add_linked_list(&queue, 10);
    add_linked_list(&queue, 20);

    free_linked_list(&queue);

    ASSERT_EQ(queue.first, nullptr);
    ASSERT_EQ(queue.last, nullptr);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}