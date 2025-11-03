#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (!fin || !fout) {
        fprintf(stderr, "Не удалось открыть input.txt или output.txt\n");
        return 1;
    }

    Node** adj = allocateAdjacencyList();
    int* inDegree = allocateInDegreeMemory();
    char** result = allocateResultMemory();
    WordDictionary dict;
    initDictionary(&dict);

    if (!adj || !inDegree || !result) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        fclose(fin);
        fclose(fout);
        freeResultMemory(result);
        free(inDegree);
        free(adj);
        return 1;
    }

    parseFirstLine(fin, &dict);
    buildGraph(fin, &dict, adj, inDegree);

    Queue q;
    initQueue(&q);
    initQueueWithZeroDegree(&q, &dict, inDegree);

    int cnt = topologicalSort(&q, adj, inDegree, result, &dict);

    outputResult(fout, result, cnt, cnt == dict.count);

    cleanupGraph(adj);
    freeResultMemory(result);
    free(inDegree);
    free(adj);

    fclose(fin);
    fclose(fout);
    return 0;
}