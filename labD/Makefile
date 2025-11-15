CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = ruckzack
TEST_TARGET = tests

all: $(TARGET)

$(TARGET): main.c ruckzack.c io.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c ruckzack.c io.c

test: $(TEST_TARGET)

$(TEST_TARGET): tests.c ruckzack.c io.c
	$(CC) $(CFLAGS) -o $(TEST_TARGET) tests.c ruckzack.c io.c

clean:
	rm -f $(TARGET) $(TEST_TARGET) output.txt

.PHONY: all test clean
