#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_VERTICES 1000

int n;
int graph[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES];
int used[MAX_VERTICES];
int found = 0;

void read_graph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не могу открыть файл %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    char line[10000];
    fgets(line, sizeof(line), file);

    for (int i = 0; i < n; i++) {
        if (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, " \n");
            while (token != NULL) {
                int neighbor = atoi(token) - 1;
                if (neighbor >= 0 && neighbor < n) {
                    graph[i][neighbor] = 1;
                }
                token = strtok(NULL, " \n");
            }
        }
    }

    fclose(file);
}

int hamiltonian_path_rec(int pos) {
    if (pos == n) {
        return 1;
    }

    for (int v = 0; v < n; v++) {
        if (!used[v]) {
            if (graph[path[pos - 1]][v]) {
                path[pos] = v;
                used[v] = 1;

                if (hamiltonian_path_rec(pos + 1)) {
                    return 1;
                }

                used[v] = 0;
            }
        }
    }

    return 0;
}

int find_hamiltonian_path() {
    if (n == 0) return 1;

    for (int start = 0; start < n; start++) {
        for (int i = 0; i < n; i++) {
            used[i] = 0;
            path[i] = -1;
        }

        path[0] = start;
        used[start] = 1;

        if (hamiltonian_path_rec(1)) {
            return 1;
        }
    }

    return 0;
}

void write_result(const char* filename, int exists) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Не могу открыть файл %s\n", filename);
        exit(1);
    }

    if (exists) {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d", path[i] + 1);
            if (i < n - 1) {
                fprintf(file, " ");
            }
        }
    }
    else {
        fprintf(file, "0");
    }

    fclose(file);
}

int main_program() {
    setlocale(LC_CTYPE, "Russian");
    read_graph("input.txt");
    int exists = find_hamiltonian_path();
    write_result("output.txt", exists);

    return 0;
}