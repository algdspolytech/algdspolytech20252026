#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_EDGES 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordSet;

typedef struct {
    char from[MAX_WORD_LEN];
    char to[MAX_WORD_LEN];
} Edge;

typedef struct Node {
    char word[MAX_WORD_LEN];
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

typedef struct GraphNode {
    char word[MAX_WORD_LEN];
    int in_degree;
    struct AdjNode* adj_list;
} GraphNode;

typedef struct AdjNode {
    int vertex_index;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    GraphNode vertices[MAX_WORDS];
    int vertex_count;
} Graph;

// Прототипы функций
Queue* create_queue();
int is_empty(Queue* q);
void enqueue(Queue* q, const char* word);
char* dequeue(Queue* q);
void free_queue(Queue* q);
int find_vertex_index(Graph* graph, const char* word);
int add_vertex(Graph* graph, const char* word);
void add_edge(Graph* graph, const char* from, const char* to);
void free_graph(Graph* graph);
int topological_sort(Graph* graph, char result[][MAX_WORD_LEN]);
int read_input(const char* filename, WordSet* word_set, Edge edges[], int* edge_count);
void write_output(const char* filename, char result[][MAX_WORD_LEN], int count, int has_cycle);

#endif
