#ifndef LIST_H
#define LIST_H

struct Node {
    char *data;
    struct Node *prev;
    struct Node *next;
};

// basic
struct Node* create_node(const char *str);
void add_to_list(struct Node **head, struct Node **tail, const char *str);
void sort_list(struct Node **head);
void print_list(struct Node *head);
void free_list(struct Node *head);

// addit for tests
struct Node* get_tail(struct Node *head);
int list_size(struct Node *head);
int is_sorted(struct Node *head);
char* get_node_data(struct Node *head, int index);

#endif