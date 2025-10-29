CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = weather_analyzer
TEST_TARGET = test_weather

SRCS = main.c weather_journal.c data_parser.c
OBJS = $(SRCS:.c=.o)

TEST_SRCS = test_weather.c weather_journal.c data_parser.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: clean test run