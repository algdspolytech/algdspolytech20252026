CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = program
SOURCES = adjacency_list.c test_adjacency_list.c main.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: clean test