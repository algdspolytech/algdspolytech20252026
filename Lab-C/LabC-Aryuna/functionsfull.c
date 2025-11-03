#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

void initQueue(Queue* q) { q->front = q->rear = 0; }
int isEmpty(Queue* q) { return q->front == q->rear; }
void enqueue(Queue* q, int v) { if (q->rear < MAX) q->data[q->rear++] = v; }
int dequeue(Queue* q) { return q->data[q->front++]; }

int str_equal(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}
void str_copy(char* dest, const char* src) {
    int i = 0;
    while (src[i]) { dest[i] = src[i]; i++; }
    dest[i] = '\0';
}

void addEdge(Node* adj[], int u, int v) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p) {
        p->to = v;
        p->next = adj[u];
        adj[u] = p;
    }
}

void initDictionary(WordDictionary* dict) {
    dict->count = 0;
}

int findIndex(const WordDictionary* dict, const char* w) {
    for (int i = 0; i < dict->count; i++)
        if (str_equal(dict->words[i], w)) return i;
    return -1;
}

int addWordIfNew(WordDictionary* dict, const char* w) {
    int idx = findIndex(dict, w);
    if (idx != -1) return idx;
    if (dict->count >= MAX) return -1;
    str_copy(dict->words[dict->count], w);
    return dict->count++;
}

int readWord(FILE* f, char* buf) {
    int c;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            ungetc(c, f);
            break;
        }
    }
    if (c == EOF) return 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') break;
        if (i < WORD_LEN - 1) buf[i++] = (char)c;
    }
    buf[i] = '\0';
    return 1;
}

void parseFirstLine(FILE* fin, WordDictionary* dict) {
    char line[LINE_LEN];
    if (!fgets(line, sizeof(line), fin)) {
        return;
    }

    int pos = 0;
    while (line[pos] != '\0') {
        while (line[pos] == ' ' || line[pos] == '\t' || line[pos] == '\r' || line[pos] == '\n') pos++;
        if (line[pos] == '\0') break;

        char w[WORD_LEN];
        int i = 0;
        while (line[pos] != '\0' && line[pos] != ' ' && line[pos] != '\t' &&
            line[pos] != '\r' && line[pos] != '\n') {
            if (i < WORD_LEN - 1) w[i++] = line[pos];
            pos++;
        }
        w[i] = '\0';
        if (i > 0) addWordIfNew(dict, w);
    }
}

void buildGraph(FILE* fin, WordDictionary* dict, Node* adj[], int inDegree[]) {
    char w1[WORD_LEN], w2[WORD_LEN];
    while (1) {
        if (!readWord(fin, w1)) break;
        if (!readWord(fin, w2)) break;

        int u = findIndex(dict, w1);
        int v = findIndex(dict, w2);
        if (u == -1 || v == -1) continue;

        addEdge(adj, u, v);
        inDegree[v]++;
    }
}

int topologicalSort(Queue* q, Node* adj[], int inDegree[], char** result, const WordDictionary* dict) {
    int cnt = 0;

    while (!isEmpty(q)) {
        int u = dequeue(q);
        str_copy(result[cnt++], dict->words[u]);

        Node* p = adj[u];
        while (p) {
            inDegree[p->to]--;
            if (inDegree[p->to] == 0) enqueue(q, p->to);
            p = p->next;
        }
    }

    return cnt;
}

void initQueueWithZeroDegree(Queue* q, const WordDictionary* dict, const int inDegree[]) {
    for (int i = 0; i < dict->count; i++)
        if (inDegree[i] == 0) enqueue(q, i);
}

void cleanupGraph(Node* adj[]) {
    for (int i = 0; i < MAX; i++) {
        Node* p = adj[i];
        while (p) {
            Node* t = p;
            p = p->next;
            free(t);
        }
    }
}

char** allocateResultMemory() {
    char** result = (char**)malloc(MAX * sizeof(char*));
    if (result) {
        for (int i = 0; i < MAX; i++) {
            result[i] = (char*)malloc(WORD_LEN * sizeof(char));
        }
    }
    return result;
}

void freeResultMemory(char** result) {
    if (result) {
        for (int i = 0; i < MAX; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int* allocateInDegreeMemory() {
    return (int*)calloc(MAX, sizeof(int));
}

Node** allocateAdjacencyList() {
    return (Node**)calloc(MAX, sizeof(Node*));
}

void outputResult(FILE* fout, char** result, int cnt, int success) {
    if (!success) {
        fprintf(fout, "[Error]\n");
    }
    else {
        for (int i = 0; i < cnt; i++) {
            fprintf(fout, "%s", result[i]);
            if (i + 1 < cnt) fprintf(fout, " ");
        }
        fprintf(fout, "\n");
    }
}