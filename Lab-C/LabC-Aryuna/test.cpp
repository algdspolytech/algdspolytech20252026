#include "C:\Users\Àðþíà\source\repos\TestforLabC\LabC\functionsfull.c"

#include <gtest/gtest.h>

TEST(QueueTest, InitAndIsEmpty) {
    Queue q;
    initQueue(&q);
    EXPECT_TRUE(isEmpty(&q));
}

TEST(QueueTest, EnqueueDequeue) {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    EXPECT_FALSE(isEmpty(&q));

    enqueue(&q, 20);
    enqueue(&q, 30);

    EXPECT_EQ(dequeue(&q), 10);
    EXPECT_EQ(dequeue(&q), 20);
    EXPECT_EQ(dequeue(&q), 30);
    EXPECT_TRUE(isEmpty(&q));
}

TEST(QueueTest, MultipleOperations) {
    Queue q;
    initQueue(&q);

    for (int i = 0; i < 10; i++) {
        enqueue(&q, i * 10);
    }

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(dequeue(&q), i * 10);
    }

    EXPECT_TRUE(isEmpty(&q));
}

TEST(StringTest, StrEqual) {
    EXPECT_TRUE(str_equal("hello", "hello"));
    EXPECT_TRUE(str_equal("", ""));
    EXPECT_FALSE(str_equal("hello", "world"));
    EXPECT_FALSE(str_equal("hello", "hell"));
    EXPECT_FALSE(str_equal("hell", "hello"));
}

TEST(StringTest, StrCopy) {
    char dest[WORD_LEN];

    str_copy(dest, "test");
    EXPECT_TRUE(str_equal(dest, "test"));

    str_copy(dest, "");
    EXPECT_TRUE(str_equal(dest, ""));

    str_copy(dest, "longer_string_test");
    EXPECT_TRUE(str_equal(dest, "longer_string_test"));
}

TEST(ReadWordTest, BasicRead) {
    FILE* f = tmpfile();
    fprintf(f, "word1 word2 word3");
    rewind(f);

    char buf[WORD_LEN];

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word1"));

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word2"));

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word3"));

    EXPECT_FALSE(readWord(f, buf));

    fclose(f);
}

TEST(ReadWordTest, WithWhitespace) {
    FILE* f = tmpfile();
    fprintf(f, "  word1   \tword2\nword3  ");
    rewind(f);

    char buf[WORD_LEN];

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word1"));

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word2"));

    EXPECT_TRUE(readWord(f, buf));
    EXPECT_TRUE(str_equal(buf, "word3"));

    EXPECT_FALSE(readWord(f, buf));

    fclose(f);
}

TEST(ReadWordTest, EmptyFile) {
    FILE* f = tmpfile();

    char buf[WORD_LEN];
    EXPECT_FALSE(readWord(f, buf));

    fclose(f);
}

TEST(GraphTest, AddEdge) {
    Node* adj[MAX] = { 0 };

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);

    EXPECT_NE(adj[0], nullptr);
    EXPECT_EQ(adj[0]->to, 2);
    EXPECT_NE(adj[0]->next, nullptr);
    EXPECT_EQ(adj[0]->next->to, 1);

    EXPECT_NE(adj[1], nullptr);
    EXPECT_EQ(adj[1]->to, 2);

    for (int i = 0; i < MAX; i++) {
        Node* p = adj[i];
        while (p) {
            Node* temp = p;
            p = p->next;
            free(temp);
        }
    }
}

TEST(BoundaryTest, QueueBoundaries) {
    Queue q;
    initQueue(&q);

    for (int i = 0; i < MAX; i++) {
        enqueue(&q, i);
    }
    enqueue(&q, MAX);

    for (int i = 0; i < MAX; i++) {
        EXPECT_EQ(dequeue(&q), i);
    }

    EXPECT_TRUE(isEmpty(&q));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}