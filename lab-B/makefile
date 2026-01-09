CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
TARGET = test_allocator
OBJS = memallocator.o test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

memallocator.o: memallocator.c memallocator.h
	$(CC) $(CFLAGS) -c memallocator.c

test.o: test.c memallocator.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run