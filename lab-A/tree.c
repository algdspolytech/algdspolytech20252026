// tree.c
#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

TreeNode* create_node(const char* node_name) {
    if (!node_name) return NULL;

    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) return NULL;

    strncpy(new_node->name, node_name, MAX_NAME_LENGTH - 1);
    new_node->name[MAX_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    new_node->child = NULL;

    return new_node;
}

PathList* add_to_path_list(PathList* list_head, const char* new_path) {
    if (!new_path) return list_head;

    PathList* new_list_node = (PathList*)malloc(sizeof(PathList));
    if (!new_list_node) return list_head;

    strncpy(new_list_node->path, new_path, MAX_PATH_SIZE - 1);
    new_list_node->path[MAX_PATH_SIZE - 1] = '\0';
    new_list_node->next = list_head;

    return new_list_node;
}

TreeNode* find_child(TreeNode* parent_node, const char* child_name) {
    if (!parent_node || !child_name) return NULL;

    TreeNode* current_child = parent_node->child;
    while (current_child) {
        if (strcmp(current_child->name, child_name) == 0) {
            return current_child;
        }
        current_child = current_child->next;
    }
    return NULL;
}

void add_child(TreeNode* parent_node, TreeNode* child_node) {
    if (!parent_node || !child_node) return;

    if (!parent_node->child) {
        parent_node->child = child_node;
    } else {
        TreeNode* last_child = parent_node->child;
        while (last_child->next) {
            last_child = last_child->next;
        }
        last_child->next = child_node;
    }
}

void add_path_to_tree(TreeNode* root_node, const char* full_path) {
    if (!root_node || !full_path || full_path[0] == '\0') return;

    char path_copy[MAX_PATH_SIZE];
    strncpy(path_copy, full_path, MAX_PATH_SIZE - 1);
    path_copy[MAX_PATH_SIZE - 1] = '\0';

    char* segment = strtok(path_copy, "\\");
    TreeNode* current_node = root_node;

    while (segment) {
        TreeNode* existing_child = find_child(current_node, segment);
        if (existing_child) {
            current_node = existing_child;
        } else {
            TreeNode* new_child = create_node(segment);
            if (new_child) {
                add_child(current_node, new_child);
                current_node = new_child;
            } else {
                break; // Ошибка выделения памяти
            }
        }
        segment = strtok(NULL, "\\");
    }
}

PathList* read_paths_from_file(const char* filename) {
    if (!filename) return NULL;

    FILE* file_handle = fopen(filename, "r");
    if (!file_handle) {
        printf("Ошибка открытия файла: %s\n", filename);
        return NULL;
    }

    int path_count;
    if (fscanf(file_handle, "%d", &path_count) != 1 || path_count <= 0) {
        fclose(file_handle);
        return NULL;
    }


    int ch;
    while ((ch = fgetc(file_handle)) != '\n' && ch != EOF);

    PathList* list_head = NULL;
    char line_buffer[MAX_PATH_SIZE];

    for (int i = 0; i < path_count; i++) {
        if (fgets(line_buffer, MAX_PATH_SIZE, file_handle)) {
            line_buffer[strcspn(line_buffer, "\n")] = '\0';
            list_head = add_to_path_list(list_head, line_buffer);
        }
    }

    fclose(file_handle);
    return list_head;
}

void sort_children(TreeNode* parent_node) {
    if (!parent_node || !parent_node->child) return;

    int child_count = 0;
    TreeNode* current = parent_node->child;
    while (current) {
        child_count++;
        current = current->next;
    }

    TreeNode** child_array = (TreeNode**)malloc(child_count * sizeof(TreeNode*));
    if (!child_array) return;

    current = parent_node->child;
    for (int i = 0; i < child_count; i++) {
        child_array[i] = current;
        current = current->next;
    }


    for (int i = 0; i < child_count - 1; i++) {
        for (int j = 0; j < child_count - i - 1; j++) {
            if (strcmp(child_array[j]->name, child_array[j + 1]->name) > 0) {
                TreeNode* temp = child_array[j];
                child_array[j] = child_array[j + 1];
                child_array[j + 1] = temp;
            }
        }
    }

    parent_node->child = child_array[0];
    for (int i = 0; i < child_count - 1; i++) {
        child_array[i]->next = child_array[i + 1];
    }
    child_array[child_count - 1]->next = NULL;

    free(child_array);
}


void sort_tree(TreeNode* node) {
    if (!node) return;

    sort_children(node);

    TreeNode* current_child = node->child;
    while (current_child) {
        sort_tree(current_child);
        current_child = current_child->next;
    }
}

void print_tree_to_file(TreeNode* node, int depth_level, FILE* output_file) {
    if (!node || !output_file) return;

    for (int i = 0; i < depth_level * 2; i++) {
        fputc(' ', output_file);
    }
    fprintf(output_file, "%s\n", node->name);

    print_tree_to_file(node->child, depth_level + 1, output_file);
    print_tree_to_file(node->next, depth_level, output_file);
}


void free_tree(TreeNode* node) {
    if (!node) return;

    free_tree(node->child);
    free_tree(node->next);
    free(node);
}


void free_path_list(PathList* list_head) {
    PathList* current = list_head;
    while (current) {
        PathList* next_node = current->next;
        free(current);
        current = next_node;
    }
}