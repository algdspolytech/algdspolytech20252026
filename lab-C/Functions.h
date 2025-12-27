#pragma once

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



Stack* createStack(int capacity);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, Point point);
Point pop(Stack* stack);
void freeStack(Stack* stack);
void printStack(Stack* stack);

void printMaze(int maze[rows][cols], Point start, Point end, int visited[rows][cols]);
int isValid(int maze[rows][cols], int Row, int Col, int visited[rows][cols]);
void reconstructPath(int maze[rows][cols], Point parent[rows][cols], Point start, Point end);
int DFS(int maze[rows][cols], Point start, Point end);