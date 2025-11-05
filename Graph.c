#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line(FILE* file) {
    if (file == NULL) return NULL;
    int buffer_size = 128;
    int len = 0;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) return NULL;
    int t;
    while ((t = fgetc(file)) != EOF && t != '\n') {
        if (len + 1 >= buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (buffer == NULL) return NULL;
        }
        buffer[len++] = t;
    }
    if (len == 0 && t == EOF) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

void graph_list(FILE* file) {
    if (file == NULL) return;
    rewind(file);
    int numb = 0;
    int node = 1;
    char* line;
    while ((line = read_line(file)) != NULL) {
        printf("%d:", node);
        for (int i = 0; i <= strlen(line) - 1; i++) {
            if (line[i] == '1') {
                printf("%d ", (numb + 1));
                numb++;
            }
            if (line[i] == '0') numb++;
        }
        printf("\n");
        numb = 0;
        free(line);
        node++;
    }
}

int main() {
    FILE* file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("ERROR");
        return 1;
    }
    graph_list(file);
    fclose(file);
    return 0;
}
