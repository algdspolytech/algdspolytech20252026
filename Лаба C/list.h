#include <stdbool.h>
#include "config.h"

typedef struct Node {
    char word[MAX_WORD_LEN];
    int in_degree;
    int index;
    struct Node** neighbors;
    int neighbor_count;
} Node;

typedef struct Graph {
    Node* nodes[MAX_WORDS];
    int node_count;
} Graph;

void safe_string_copy(char* dest, const char* src, int max_len);
void init_graph(Graph* graph);
Node* find_node(Graph* graph, const char* word);
Node* add_node(Graph* graph, const char* word);
void add_edge(Graph* graph, const char* from, const char* to);
bool topological_sort(Graph* graph, char result[][MAX_WORD_LEN]);
void free_graph(Graph* graph);
int parse_words(const char* line, char words[][MAX_WORD_LEN]);
