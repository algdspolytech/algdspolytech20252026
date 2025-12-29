#include "Pentomino.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_pentomino_file> <output_file>\n", argv[0]);
        return 1;
    }


    Pentomino* p = load_pentomino(argv[1]);
    if (p == NULL) {
        printf("Error: failed to load pentomino from file\n");
        write_pentomino(NULL, argv[2]);
        return 1;
    }

 
    if (!is_valid_pentomino(p)) {
        printf("Error: invalid pentomino\n");
        write_pentomino(NULL, argv[2]);
        free_pentomino(p);
        return 1;
    }


    Field* field = init_field(10, 10);
    if (field == NULL) {
        printf("Error: failed to create field\n");
        free_pentomino(p);
        return 1;
    }

  
    int placed = 0;

    for (int rotation = 0; rotation < 4 && !placed; rotation++) {
        for (int y = 0; y < field->height && !placed; y++) {
            for (int x = 0; x < field->width && !placed; x++) {
                if (can_place(field, p, x, y)) {
                    printf("Pentomino placed at (%d, %d) after %d rotation(s)\n",
                        x, y, rotation);
                    placed = 1;
                }
            }
        }
        if (!placed) {
            rotate_pentomino(p);
        }
    }

    if (placed) {
        write_pentomino(p, argv[2]);
    }
    else {
        printf("Failed to place pentomino on the field\n");
        write_pentomino(NULL, argv[2]);
    }

    free_field(field);
    free_pentomino(p);

    return 0;
}
