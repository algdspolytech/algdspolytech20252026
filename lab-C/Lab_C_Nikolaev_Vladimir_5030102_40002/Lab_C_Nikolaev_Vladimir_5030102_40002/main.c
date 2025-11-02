#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#pragma warning(disable: 4996)
#define n 10

int Num_In_Mas(int* mas, int num) {
	int x = 0;
	while (mas[x]!=-1) {
		if (mas[x] == num) {
			return 0;
		}
		x++;
	}
	return 1;
}

int* Add_To_List(int* mas, int num) {
	int x = 0;
	while (mas[x] != -1) {
		x++;
	}
	mas = realloc(mas,sizeof(int) * (x + 1));
	mas[x] = num;
	mas[x + 1] = -1;
	return mas;
}

int *DFS(int** a,int*marked_node,int num) {
	marked_node=Add_To_List(marked_node, num);
	for (int x = 0; x < n; x++) {
		if (a[num][x] == 1 && Num_In_Mas(marked_node, x)) {
			marked_node = DFS(a, marked_node, x);
		}
	}
	return marked_node;
}

int** Create_Graph_Matrix(FILE* file) {
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (file_size == 0) {
		return NULL;
	}
	int** a = malloc(sizeof(int*) * n);
	for (int x = 0; x < n; x++) {
		a[x] = malloc(sizeof(int) * n);
	}
	char num;
	int x = 0;
	int y = 0;

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (fscanf(file, "%c ", &num) != EOF && num != ' ' && num != '\n') {
				a[x][y] = num - 48;
			}
		}
	}
	return a;
}

char* Way_Between_Graph_Node(int** a, int node1, int node2) {
	int* marked_node = malloc(sizeof(int));
	marked_node[0] = -1;
	marked_node = DFS(a, marked_node, node1);
	int z = 0;
	int flag = 0;
	while (marked_node[z] != -1) {
		if (marked_node[z] == node2) {
			flag = 1;
		}
		z++;
	}
	if (flag == 0) {
		return "There is no way:(";
	}
	else {
		return "There is a way:)";
	}
}