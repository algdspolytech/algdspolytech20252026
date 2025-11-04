CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
SRC = src/bigint.c
TEST = tests/test_bigint.c
BIN = bin/test_bigint

.PHONY: all test clean
all: $(BIN)

$(BIN): $(SRC) $(TEST)
	@mkdir -p bin
	$(CC) $(CFLAGS) -Isrc -o $(BIN) $(SRC) $(TEST)

test: $(BIN)
	./$(BIN)

clean:
	rm -rf bin
