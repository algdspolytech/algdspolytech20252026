#include "Lab-A.h"
#pragma warning(disable:4996)

FolderTree* create_node(const char* name) {
    if (!name) {
        return NULL;
    }

    FolderTree* node = (FolderTree*)malloc(sizeof(FolderTree));
    if (!node) {
        return NULL;
    }

    strncpy(node->name, name, MAX_NAME_LENGTH - 1);
    node->name[MAX_NAME_LENGTH - 1] = '\0';

    node->child_count = 0;
    node->size = 4;
    node->child = (FolderTree**)malloc(node->size * sizeof(FolderTree*));

    if (!node->child) {
        free(node);
        return NULL;
    }

    return node;
}

void free_tree(FolderTree* root) {
    if (!root) return;

    for (int i = 0; i < root->child_count; i++) {
        free_tree(root->child[i]);
    }

    free(root->child);
    free(root);
}

void add_child(FolderTree* parent, FolderTree* child) {
    if (!parent || !child) return;

    // Check if we need to expand size
    if (parent->child_count >= parent->size) {
        int new_size = parent->size * 2;
        FolderTree** new_children = (FolderTree**)realloc(parent->child, new_size * sizeof(FolderTree*));

        if (!new_children) {
            return; // Realloc failed, but we continue anyway
        }

        parent->child = new_children;
        parent->size = new_size;
    }

    parent->child[parent->child_count++] = child;
}

FolderTree* find_child(FolderTree* parent, const char* name) {
    if (!parent || !name) return NULL;

    for (int i = 0; i < parent->child_count; i++) {
        if (strcmp(parent->child[i]->name, name) == 0) {
            return parent->child[i];
        }
    }

    return NULL;
}

void insert_path(FolderTree* root, const char* path) {
    if (root == NULL || path == NULL || path[0] == '\0') return;

    char tmp_path[MAX_PATH_LENGTH];
    strncpy(tmp_path, path, MAX_PATH_LENGTH - 1);
    tmp_path[MAX_PATH_LENGTH - 1] = '\0';

    char* token = strtok(tmp_path, "\\");
    FolderTree* current = root;

    while (token != NULL) {
        FolderTree* existing_child = find_child(current, token);
        if (existing_child != NULL) {
            current = existing_child;
        }
        else {
            FolderTree* new_child = create_node(token);
            if (new_child != NULL) {
                add_child(current, new_child);
                current = new_child;
            }
            else {
                break; // Memory allocation failed
            }
        }
        token = strtok(NULL, "\\");
    }
}

int compare_nodes(const void* a, const void* b) {
    const FolderTree* node_a = *(const FolderTree**)a;
    const FolderTree* node_b = *(const FolderTree**)b;
    return strcmp(node_a->name, node_b->name);
}

void sort_tree(FolderTree* node) {
    if (!node || node->child_count == 0) return;

    // Sort current node's children
    qsort(node->child, node->child_count, sizeof(FolderTree*), compare_nodes);

    // Recursively sort all subtrees
    for (int i = 0; i < node->child_count; i++) {
        sort_tree(node->child[i]);
    }
}

void print_tree(FolderTree* node, int level, FILE* output_file) {
    if (!node || !output_file) return;

    // Print current node with proper indentation
    for (int i = 0; i < level; i++) {
        fprintf(output_file, " ");
    }
    fprintf(output_file, "%s\n", node->name);

    // Recursively print all children
    for (int i = 0; i < node->child_count; i++) {
        print_tree(node->child[i], level + 1, output_file);
    }
}

void process_folder_tree(FolderTree* node, int level, FILE* output) {
    if (node == NULL || output == NULL) return;

    for (int i = 0; i < level * 2; i++) {
        fputc(' ', output);
    }
    fprintf(output, "%s\n", node->name);

    for (int i = 0; i < node->child_count; i++) {
        process_folder_tree(node->child[i], level + 1, output);
    }
}