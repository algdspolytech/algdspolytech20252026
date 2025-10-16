// tree.h
#ifndef DIRECTORY_TREE_H
#define DIRECTORY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 9
#define MAX_PATH_SIZE 256

typedef struct TreeNode {
    char name[MAX_NAME_LENGTH];
    struct TreeNode* next;
    struct TreeNode* child;
} TreeNode;

typedef struct PathList {
    char path[MAX_PATH_SIZE];
    struct PathList* next;
} PathList;

TreeNode* create_node(const char* name);
PathList* add_to_path_list(PathList* head, const char* path);
TreeNode* find_child(TreeNode* parent, const char* name);
void add_child(TreeNode* parent, TreeNode* child);
void add_path_to_tree(TreeNode* root, const char* path);
PathList* read_paths_from_file(const char* filename);
void sort_children(TreeNode* parent);
void sort_tree(TreeNode* node);
void print_tree_to_file(TreeNode* node, int level, FILE* output);
void free_tree(TreeNode* node);
void free_path_list(PathList* head);

#endif//ALGDSPOLYTECH20252026__TREE_H