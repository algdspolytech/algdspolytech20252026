CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
SRC = src/shortest_path.c
TEST = tests/test_shortest.c
BIN = bin/shortest
TESTBIN = bin/test_shortest

.PHONY: all test clean
all: $(BIN) $(TESTBIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) -Isrc -o $(BIN) $(SRC)

$(TESTBIN): $(SRC) $(TEST)
	@mkdir -p bin
	$(CC) $(CFLAGS) -Isrc -o $(TESTBIN) $(SRC) $(TEST)

test: $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -rf bin
