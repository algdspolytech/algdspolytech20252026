#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<assert.h>
#include "Functions.h"


#define rows 6
#define cols 6









void Test_CreateStack_Capacity_ReturnStack() {
	printf("Test 1: Stack creation\n");

	int cap = 10;

	Stack* stack = createStack(cap);


	assert((stack->capacity == cap) && (sizeof(stack->way) * stack->capacity == (cap * sizeof(Point))));
	printf("Success!\n\n");
}


void Test_push_Point_NewStack() {
	printf("Test 2: New element in stack\n");

	int cap = 1;
	Stack* stack = createStack(cap);
	Point point = { 1, 1 };
	push(stack, point);

	Point res = stack->way[stack->top];
	assert(res.col == point.col && res.row == point.row);
	printf("Success!\n\n");
}


void Test_isEmpty_EmptyStack_ReturnTrue() {
	printf("Test 3: Stack is empty\n");

	int cap = 1;
	Stack* stack = createStack(cap);
	int empty = isEmpty(stack);

	assert(empty);
	printf("Success!\n\n");
}

void Test_isEmpty_EmptyStack_ReturnFalse() {
	printf("Test 4: Stack is not empty\n");

	int cap = 1;
	Stack* stack = createStack(cap);
	Point point = { 1, 1 };
	push(stack, point);
	int empty = isEmpty(stack);

	assert(!empty);
	printf("Success!\n\n");
}

void Test_isFull_FullStack_ReturnTrue() {
	printf("Test 5: Stack is full\n");

	int cap = 2;
	Stack* stack = createStack(cap);
	Point point1 = { 1, 1 };
	Point point2 = { 2, 2 };

	push(stack, point1);
	push(stack, point2);

	int full = isFull(stack);
	assert(full);
	printf("Success!\n\n");
}

void Test_isFull_NotFullStack_ReturnFalse() {
	printf("Test 6: Stack is not full\n");

	int cap = 3;
	Stack* stack = createStack(cap);
	Point point = { 1, 1 };

	push(stack, point);

	int full = isFull(stack);
	assert(!full);
	printf("Success!\n\n");
}

void Test_pop_NonEmptyStack_ReturnPoint() {
	printf("Test 7: Pop element from non-empty stack\n");

	int cap = 3;
	Stack* stack = createStack(cap);
	Point point1 = { 1, 1 };
	Point point2 = { 2, 2 };
	Point point3 = { 3, 3 };

	push(stack, point1);
	push(stack, point2);
	push(stack, point3);

	Point popped = pop(stack);

	assert(popped.row == point3.row && popped.col == point3.col);
	assert(stack->top == 1);
	printf("Success!\n\n");
}

void Test_pop_EmptyStack_ReturnInvalidPoint() {
	printf("Test 8: Pop element from empty stack\n");

	int cap = 3;
	Stack* stack = createStack(cap);

	Point popped = pop(stack);


	assert(popped.row == -1 && popped.col == -1);
	printf("Success!\n\n");
}

void Test_push_FullStack_ErrorMessage() {
	printf("Test 9: Push to full stack (error message)\n");

	int cap = 2;
	Stack* stack = createStack(cap);
	Point point1 = { 1, 1 };
	Point point2 = { 2, 2 };
	Point point3 = { 3, 3 };

	push(stack, point1);
	push(stack, point2);


	int initial_top = stack->top;
	Point initial_last = stack->way[stack->top];


	printf("Error message: ");
	push(stack, point3);


	assert(stack->top == initial_top);
	assert(stack->way[stack->top].row == initial_last.row);
	assert(stack->way[stack->top].col == initial_last.col);
	printf("Success!\n\n");
}


void Test_isValid_ValidCell_ReturnTrue() {
	printf("Test 10: Valid cell check\n");

	int maze[rows][cols] = {
		{0, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0, 0}
	};

	int visited[rows][cols] = { 0 };


	int result1 = isValid(maze, 0, 0, visited);
	assert(result1 == 1);


	int result2 = isValid(maze, 0, 1, visited);
	assert(result2 == 0);


	visited[2][2] = 1;
	int result3 = isValid(maze, 2, 2, visited);
	assert(result3 == 0);


	int result4 = isValid(maze, -1, 0, visited);
	assert(result4 == 0);


	int result5 = isValid(maze, rows, cols, visited);
	assert(result5 == 0);

	printf("Success!\n\n");
}


void Test_DFS_PathExists_ReturnTrue() {
	printf("Test 11: DFS finds path when it exists\n");

	int maze[rows][cols] = {
		{0, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0, 0}
	};

	Point start = { 0, 0 };
	Point end = { 5, 5 };

	int result = DFS(maze, start, end);
	assert(result == 1);

	printf("Success!\n\n");
}


void Test_DFS_NoPath_ReturnFalse() {
	printf("Test 12: DFS returns false when no path exists\n");

	int maze[rows][cols] = {
		{0, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 1, 1}
	};

	Point start = { 0, 0 };
	Point end = { 5, 5 };

	int result = DFS(maze, start, end);
	assert(result == 0);

	printf("Success!\n\n");
}


void Test_DFS_SameStartAndEnd_ReturnTrue() {
	printf("Test 13: DFS with start and end at same point\n");

	int maze[rows][cols] = {
		{0, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0, 0}
	};

	Point start = { 0, 0 };
	Point end = { 0, 0 };

	int result = DFS(maze, start, end);
	assert(result == 1);

	printf("Success!\n\n");
}

void Test_DFS_StartIsWall_ReturnFalse() {
	printf("Test 14: DFS with start point as wall\n");

	int maze[rows][cols] = {
		{1, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0, 0}
	};

	Point start = { 0, 0 };
	Point end = { 5, 5 };

	int result = DFS(maze, start, end);
	assert(result == 0);

	printf("Success!\n\n");
}


void Test_DFS_EndIsWall_ReturnFalse() {
	printf("Test 15: DFS with end point as wall\n");

	int maze[rows][cols] = {
		{0, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1}
	};

	Point start = { 0, 0 };
	Point end = { 5, 5 };

	int result = DFS(maze, start, end);
	assert(result == 0);

	printf("Success!\n\n");
}


int main() {
	setlocale(LC_CTYPE, "Russian");

	Test_CreateStack_Capacity_ReturnStack();
	Test_push_Point_NewStack();
	Test_isEmpty_EmptyStack_ReturnTrue();
	Test_isEmpty_EmptyStack_ReturnFalse();
	Test_isFull_FullStack_ReturnTrue();
	Test_isFull_NotFullStack_ReturnFalse();
	Test_pop_NonEmptyStack_ReturnPoint();
	Test_pop_EmptyStack_ReturnInvalidPoint();
	Test_push_FullStack_ErrorMessage();
	Test_isValid_ValidCell_ReturnTrue();
	Test_DFS_PathExists_ReturnTrue();
	Test_DFS_NoPath_ReturnFalse();
	Test_DFS_SameStartAndEnd_ReturnTrue();
	Test_DFS_StartIsWall_ReturnFalse();
	Test_DFS_EndIsWall_ReturnFalse();


	return 0;
}
