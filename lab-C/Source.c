#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

node* Create_Node(int a) {
    node* elem = (node*)malloc(sizeof(node));
    if (!elem) return NULL;
    elem->value = a;
    elem->next = NULL;
    return elem;
}

void Create_Graf(Graf* G, int n) {
    G->numbers = n;
    G->mas_of_visited = (int*)malloc(n * sizeof(int));
    G->mas = (node**)malloc(n * sizeof(node*));
    for (int i = 0; i < n; i++) {
        G->mas_of_visited[i] = 0;
        G->mas[i] = NULL;
    }
}

void Add_Edge(Graf* G, int src, int dest) {
    node* nod2 = Create_Node(dest);
    nod2->next = G->mas[src];
    G->mas[src] = nod2;

    node* nod1 = Create_Node(src);
    nod1->next = G->mas[dest];
    G->mas[dest] = nod1;

    printf("\n%d %d\n", src, dest);
}

bool IsWay(Graf* G, int cur, int target) {
    if (cur == target)
        return true;

    G->mas_of_visited[cur] = 1;
    node* nod = G->mas[cur];
  
    while (nod != NULL) {
        int nod_value = nod->value;
        if (nod->value == target) 
        {
            return true;
        }
        if (!G->mas_of_visited[nod_value]) {
            if (IsWay(G, nod_value, target))
                return true;
        }
        nod = nod->next;
    }
    return false;
}

void PrintGraf(Graf G) {
    for (int i = 0; i < G.numbers; i++) {
        if (G.mas[i] != NULL) {
            printf("%d: ", i);
            node* temp = G.mas[i];
            while (temp != NULL) {
                printf("%d ", temp->value);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

int ReadFile(const char* filename, Graf* G) {
    FILE* F = fopen(filename, "r");
    if (F == NULL) {
        perror("Error opening file");
        return -1;
    }

    int max_vertex = -1;
    char line[200];

    while (fgets(line, sizeof(line), F)) {
        char* token = strtok(line, " \n");
        if (token) {
            int vertex = atoi(token);
            if (vertex > max_vertex)
                max_vertex = vertex;
        }
    }

    rewind(F);
    Create_Graf(G, max_vertex + 1);

    while (fgets(line, sizeof(line), F)) {
        char* token = strtok(line, " \n");
        if (token) {
            int vertex = atoi(token);
            printf("%d: ", vertex);
            while ((token = strtok(NULL, " \n")) != NULL) {
                int neighbour = atoi(token);
                printf("%d ", neighbour);
                Add_Edge(G, vertex, neighbour);
            }
            printf("\n");
        }
    }

    fclose(F);
    return max_vertex;
}

void FreeGraf(Graf* G) {
    for (int i = 0; i < G->numbers; i++) {
        node* current = G->mas[i];
        while (current != NULL) {
            node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(G->mas);
    free(G->mas_of_visited);
}
