// tree.c
#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

TreeNode* create_node(const char* name) {
    if (name == NULL) return NULL;

    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) return NULL;

    strncpy(new_node->name, name, MAX_SYMBOLS - 1);
    new_node->name[MAX_SYMBOLS - 1] = '\0';
    new_node->next = NULL;
    new_node->child = NULL;

    return new_node;
}

PathList* add_to_path_list(PathList* head, const char* path) {
    if (path == NULL) return head;

    PathList* new_node = (PathList*)malloc(sizeof(PathList));
    if (new_node == NULL) return head;

    strncpy(new_node->path, path, MAX_PATH_LENGTH - 1);
    new_node->path[MAX_PATH_LENGTH - 1] = '\0';
    new_node->next = head;

    return new_node;
}

TreeNode* find_child(TreeNode* parent, const char* name) {
    if (parent == NULL || name == NULL) return NULL;

    TreeNode* current = parent->child;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_child(TreeNode* parent, TreeNode* new_child) {
    if (parent == NULL || new_child == NULL) return;

    if (parent->child == NULL) {
        parent->child = new_child;
    }
    else {
        TreeNode* current = parent->child;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_child;
    }
}

void add_path_to_tree(TreeNode* root, const char* path) {
    if (root == NULL || path == NULL || path[0] == '\0') return;

    char tmp_path[MAX_PATH_LENGTH];
    strncpy(tmp_path, path, MAX_PATH_LENGTH - 1);
    tmp_path[MAX_PATH_LENGTH - 1] = '\0';

    char* token = strtok(tmp_path, "\\");
    TreeNode* current = root;

    while (token != NULL) {
        TreeNode* existing_child = find_child(current, token);
        if (existing_child != NULL) {
            current = existing_child;
        }
        else {
            TreeNode* new_child = create_node(token);
            if (new_child != NULL) {
                add_child(current, new_child);
                current = new_child;
            }
            else {
                break; // Ошибка выделения памяти
            }
        }
        token = strtok(NULL, "\\");
    }
}

PathList* read_paths_from_file(const char* filename) {
    if (filename == NULL) return NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла: %s\n", filename);
        return NULL;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1 || n <= 0) {
        fclose(file);
        return NULL;
    }

    // Пропуск оставшейся части строки
    int c;
    while ((c = fgetc(file)) != '\n' && c != EOF);

    PathList* head = NULL;
    char buffer[MAX_PATH_LENGTH];

    for (int i = 0; i < n; i++) {
        if (fgets(buffer, MAX_PATH_LENGTH, file) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            head = add_to_path_list(head, buffer);
        }
    }

    fclose(file);
    return head;
}

void sort_children(TreeNode* parent) {
    if (parent == NULL || parent->child == NULL) return;

    int count = 0;
    TreeNode* current = parent->child;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    TreeNode** children_array = (TreeNode**)malloc(count * sizeof(TreeNode*));
    if (children_array == NULL) return;

    current = parent->child;
    for (int i = 0; i < count; i++) {
        children_array[i] = current;
        current = current->next;
    }

    // Пузырьковая сортировка
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(children_array[j]->name, children_array[j + 1]->name) > 0) {
                TreeNode* temp = children_array[j];
                children_array[j] = children_array[j + 1];
                children_array[j + 1] = temp;
            }
        }
    }

    parent->child = children_array[0];
    for (int i = 0; i < count - 1; i++) {
        children_array[i]->next = children_array[i + 1];
    }
    children_array[count - 1]->next = NULL;

    free(children_array);
}

void sort_tree(TreeNode* node) {
    if (node == NULL) return;

    sort_children(node);

    TreeNode* current = node->child;
    while (current != NULL) {
        sort_tree(current);
        current = current->next;
    }
}

void print_tree_to_file(TreeNode* node, int level, FILE* output) {
    if (node == NULL || output == NULL) return;

    for (int i = 0; i < level * 2; i++) {
        fputc(' ', output);
    }
    fprintf(output, "%s\n", node->name);

    print_tree_to_file(node->child, level + 1, output);
    print_tree_to_file(node->next, level, output);
}

void free_tree(TreeNode* node) {
    if (node == NULL) return;

    free_tree(node->child);
    free_tree(node->next);
    free(node);
}

void free_path_list(PathList* head) {
    PathList* current = head;
    while (current != NULL) {
        PathList* next = current->next;
        free(current);
        current = next;
    }
}