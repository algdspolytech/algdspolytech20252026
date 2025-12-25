#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<assert.h>

#define rows 6
#define cols 6

typedef struct {
	int row, col;
}Point;

typedef struct {
	Point* way;
	int top;
	int capacity;
}Stack;


Stack* createStack(int capacity) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	stack->capacity = capacity;
	stack->top = -1;
	stack->way = (Point*)malloc(capacity * sizeof(Point));

	return stack;
}

int isEmpty(Stack* stack) {
	return (stack->top == -1);
}

int isFull(Stack* stack) {
	return (stack->top == (stack->capacity) - 1);
}

void push(Stack* stack, Point point) {
	if (isFull(stack)) {
		printf("Ошибка: стек переполнен\n");
		return;
	}
	else {
		stack->top++;
		stack->way[stack->top] = point;
	}
}

Point pop(Stack* stack) {
	if (isEmpty(stack)) {
		printf("Ошибка: стек пуст\n");
		return (Point) { -1, -1 };
	}
	Point p = stack->way[stack->top];  
	stack->top--;                      
	return p;
}



void freeStack(Stack* stack) {
	if (stack != NULL) {
		free(stack->way);
		free(stack);
	}
}


void printStack(Stack* stack) {
	if (isEmpty(stack)) {
		printf("Ошибка: стек пуст\n");
		return;
	}
	else {
		for (int i = stack->top; i >= 0; i--) {
			printf("(%d, %d) ", stack->way[i].row, stack->way[i].col);
		}
		printf("\n");
	}
}

void printMaze(int maze[rows][cols], Point start, Point end, int visited[rows][cols]) {
	printf("\nЛабиринт:\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == start.row && j == start.col) {
				printf("S ");
			}
			else if (i == end.row && j == end.col) {
				printf("E ");
			}
			else if (visited[i][j]) {
				printf(". ");
			}
			else {
				printf("%c ", maze[i][j] == 1 ? '#' : ' ');
			}
		}
		printf("\n");
	}
}

int isValid(int maze[rows][cols], int Row, int Col, int visited[rows][cols]) {
	// Проверяем границы, что не стена и не посещена
	return (Row >= 0 && Row < rows &&
		Col >= 0 && Col < cols &&
		maze[Row][Col] == 0 && !visited[Row][Col]);
}


void reconstructPath(int maze[rows][cols], Point parent[rows][cols], Point start, Point end) {
	Point path[rows * cols];
	int pathLength = 0;
	Point current = end;


	while (current.row != -1 && current.col != -1) {
		path[pathLength++] = current;
		current = parent[current.row][current.col];
	}

	// Печатаем путь от начала к концу
	printf("Маршрут: ");
	for (int i = pathLength - 1; i >= 0; i--) {
		printf("(%d,%d)", path[i].row, path[i].col);
		if (i > 0) printf(" -- ");
	}
	printf("\n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int isPath = 0;
			for (int k = 0; k < pathLength; k++) {
				if (path[k].row == i && path[k].col == j) {
					isPath = 1;
					break;
				}
			}

			if (i == start.row && j == start.col) {
				printf("S ");
			}
			else if (i == end.row && j == end.col) {
				printf("E ");
			}
			else if (isPath) {
				printf("* ");
			}
			else {
				printf("%c ", maze[i][j] == 1 ? '#' : ' ');
			}
		}
		printf("\n");
	}
}





int DFS(int maze[rows][cols], Point start, Point end) {

	if (maze[start.row][start.col] == 1) {
		printf("Ошибка: начальная точка является стеной\n");
		return 0;
	}

	if (maze[end.row][end.col] == 1) {
		printf("Ошибка: конечная точка является стеной\n");
		return 0;
	}


	Stack* stack = createStack(rows * cols);
	int visited[rows][cols] = { 0 };
	Point parent[rows][cols];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			parent[i][j] = (Point){ -1, -1 };
		}
	}

	int dHor[] = { -1, 0, 1, 0 };
	int dVer[] = { 0, 1, 0, -1 };

	push(stack, start);
	visited[start.row][start.col] = 1;

	while (!isEmpty(stack)) {
		Point current = pop(stack);

		if (current.row == end.row && current.col == end.col) {
			reconstructPath(maze, parent, start, end);
			freeStack(stack);
			return 1;
		}

		int neighborsAdded = 0;

		for (int i = 0; i < 4; i++) {
			int newRow = current.row + dHor[i];
			int newCol = current.col + dVer[i];

			if (isValid(maze, newRow, newCol, visited)) {
				Point neighbor = { newRow, newCol };
				push(stack, neighbor);

				visited[newRow][newCol] = 1;
				parent[newRow][newCol] = current;
				neighborsAdded++;
			}
		}

	}
	printf("\nПуть не найден\n");
	freeStack(stack);
	return 0;
}








