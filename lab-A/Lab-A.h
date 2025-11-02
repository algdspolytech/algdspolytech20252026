#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 9
#define MAX_PATHS 500

typedef struct FolderTree {
    char name[MAX_NAME_LENGTH];
    struct FolderTree** child;
    int child_count;
    int size;
} FolderTree;

/**
 * Creates a new tree node with the given name
 * @param name: The name for the new node
 * @return: Pointer to the created node, or NULL on failure
 */
FolderTree* create_node(const char* name);

/**
 * Frees all memory allocated for the tree
 * @param root: Root of the tree to free
 */
void free_tree(FolderTree* root);

/**
 * Adds a child node to a parent node
 * @param parent: Parent node to add child to
 * @param child: Child node to add
 */
void add_child(FolderTree* parent, FolderTree* child);

/**
 * Finds a child node with the given name in parent's children
 * @param parent: Parent node to search in
 * @param name: Name of child to find
 * @return: Pointer to found child, or NULL if not found
 */
FolderTree* find_child(FolderTree* parent, const char* name);

/**
 * Inserts a path into the tree
 * @param root: Root of the tree
 * @param path: Path string to insert
 */
void insert_path(FolderTree* root, const char* path);

/**
 * Compares two tree nodes for sorting (lexicographical order)
 * @param a: First node pointer
 * @param b: Second node pointer
 * @return: Negative if a < b, positive if a > b, 0 if equal
 */
int compare_nodes(const void* a, const void* b);

/**
 * Sorts all children of a node and recursively sorts subtrees
 * @param node: Node whose children to sort
 */
void sort_tree(FolderTree* node);

/**
 * Prints the tree to a file with proper indentation
 * @param node: Current node to print
 * @param level: Current depth level (0 for root)
 * @param output_file: File to write output to
 */
void print_tree(FolderTree* node, int level, FILE* output_file);

/**
 * Main function to process input and generate output
 * Reads from "input.txt" and writes to "output.txt"
 * @return: 0 on success, 1 on error
 */
void process_folder_tree(FolderTree* node, int level, FILE* output);