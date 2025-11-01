#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 9
#define MAX_PATH_LENGTH 256

typedef struct TreeNode {
    char name[MAX_SYMBOLS];
    struct TreeNode* next;
    struct TreeNode* child;
} TreeNode;

typedef struct PathList {
    char path[MAX_PATH_LENGTH];
    struct PathList* next;
} PathList;

// Основные функции
TreeNode* create_node(const char* name);
PathList* add_to_path_list(PathList* head, const char* path);
TreeNode* find_child(TreeNode* parent, const char* name);
void add_child(TreeNode* parent, TreeNode* new_child);
void add_path_to_tree(TreeNode* root, const char* path);
PathList* read_paths_from_file(const char* filename);
void sort_children(TreeNode* parent);
void sort_tree(TreeNode* node);
void print_tree_to_file(TreeNode* node, int level, FILE* output);
void free_tree(TreeNode* node);
void free_path_list(PathList* head);

#endif