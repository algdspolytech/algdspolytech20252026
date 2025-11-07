#include "polynom.h"
#include <stdio.h>
#include <stdlib.h> 

int main() {
    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt";

    // проверка существования и доступа вх файла
    FILE* fin_check = fopen(input_filename, "r");

    if (fin_check == NULL) {
        fprintf(stderr, "Error: Input file '%s' not found or cannot be opened.\n", input_filename);
        fprintf(stderr, "Please ensure '%s' exists in the execution directory.\n", input_filename);
        return EXIT_FAILURE;
    }

    // файл найден, закрытие проверочного дескриптора
    fclose(fin_check);

    process_file(input_filename, output_filename);

    return 0;
}