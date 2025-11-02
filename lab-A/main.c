#include "Lab-A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main() {
    FILE* input_file = fopen("input.txt", "w");
    if (!input_file) {
        printf("Error creating input file!\n");
        return 1;
    }

    fprintf(input_file, "7\n");
    fprintf(input_file, "WINNT\\SYSTEM32\\CONFIG\n");
    fprintf(input_file, "GAMES\n");
    fprintf(input_file, "WINNT\\DRIVERS\n");
    fprintf(input_file, "HOME\n");
    fprintf(input_file, "WIN\\SOFT\n");
    fprintf(input_file, "GAMES\\DRIVERS\n");
    fprintf(input_file, "WINNT\\SYSTEM32\\CERTSRV\\CERTCO~1\\X86\n");

    fclose(input_file);
    printf("Input file created successfully!\n");

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        printf("Error opening files!\n");
        if (input) fclose(input);
        if (output) fclose(output);
        return 1;
    }

    int n;
    if (fscanf(input, "%d", &n) != 1 || n < 1 || n > MAX_PATHS) {
        printf("Invalid input format!\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fgetc(input);

    FolderTree* root = create_node("");
    if (!root) {
        printf("Memory allocation failed!\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    char path[MAX_PATH_LENGTH];

    for (int i = 0; i < n; i++) {
        if (fgets(path, sizeof(path), input)) {
            size_t len = strlen(path);
            if (len > 0 && path[len - 1] == '\n') {
                path[len - 1] = '\0';
            }

            insert_path(root, path);
        }
    }

    fclose(input);

    sort_tree(root);

    for (int i = 0; i < root->child_count; i++) {
        process_folder_tree(root->child[i], 0, output);
    }

    fclose(output);
    free_tree(root);

    printf("Output file generated successfully!\n");
    printf("Check output.txt for the sorted directory tree.\n");

    return 0;
}