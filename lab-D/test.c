#include "Pentomino.h"
#include <assert.h>
#include <stdio.h>

void create_test_file(const char* name, const char* content) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", content);
    fclose(f);
}


void TestLoadPentomino_ValidFile_no1() {
    create_test_file("p1.txt", "0 0\n1 0\n2 0\n3 0\n4 0\n");
    Pentomino* p = load_pentomino("p1.txt");
    assert(p != NULL);
    assert(p->count == 5);
    free_pentomino(p);
    remove("p1.txt");
}

void TestLoadPentomino_FileNotFound_no2() {
    Pentomino* p = load_pentomino("missing.txt");
    assert(p == NULL);
}

void TestLoadPentomino_TooManyCells_no3() {
    create_test_file("p2.txt", "0 0\n1 0\n2 0\n3 0\n4 0\n5 0\n");
    Pentomino* p = load_pentomino("p2.txt");
    assert(p == NULL);
    remove("p2.txt");
}


void TestValidPentomino_Correct_no4() {
    Pentomino* p = init_pentomino();
    for (int i = 0; i < 5; i++) {
        p->cells[i].x = i;
        p->cells[i].y = 0;
    }
    p->count = 5;
    assert(is_valid_pentomino(p) == 1);
    free_pentomino(p);
}

void TestValidPentomino_DuplicateCells_no5() {
    Pentomino* p = init_pentomino();
    for (int i = 0; i < 5; i++) {
        p->cells[i].x = 0;
        p->cells[i].y = 0;
    }
    p->count = 5;
    assert(is_valid_pentomino(p) == 0);
    free_pentomino(p);
}

void TestValidPentomino_NotEnoughCells_no6() {
    Pentomino* p = init_pentomino();
    p->count = 3;
    assert(is_valid_pentomino(p) == 0);
    free_pentomino(p);
}


void TestRotatePentomino_Normal_no7() {
    Pentomino* p = init_pentomino();
    p->cells[0] = (Cell){ 1, 2 };
    p->count = 1;
    rotate_pentomino(p);
    assert(p->cells[0].x == -2);
    assert(p->cells[0].y == 1);
    free_pentomino(p);
}


void TestCanPlace_EmptyField_no8() {
    Field* f = init_field(5, 5);
    Pentomino* p = init_pentomino();
    for (int i = 0; i < 5; i++) {
        p->cells[i] = (Cell){ i, 0 };
    }
    p->count = 5;
    assert(can_place(f, p, 0, 0) == 1);
    free_field(f);
    free_pentomino(p);
}

void TestCanPlace_OutOfBounds_no9() {
    Field* f = init_field(3, 3);
    Pentomino* p = init_pentomino();
    for (int i = 0; i < 5; i++) {
        p->cells[i] = (Cell){ i, 0 };
    }
    p->count = 5;
    assert(can_place(f, p, 0, 0) == 0);
    free_field(f);
    free_pentomino(p);
}

void TestCanPlace_CellOccupied_no10() {
    Field* f = init_field(5, 5);
    f->field[0][1] = 1;

    Pentomino* p = init_pentomino();
    for (int i = 0; i < 5; i++)
        p->cells[i] = (Cell){ i, 0 };
    p->count = 5;

    assert(can_place(f, p, 0, 0) == 0);
    free_field(f);
    free_pentomino(p);
}


void TestWritePentomino_Valid_no11() {
    Pentomino* p = init_pentomino();
    p->cells[0] = (Cell){ 1, 1 };
    p->count = 1;
    write_pentomino(p, "out.txt");

    FILE* f = fopen("out.txt", "r");
    int x, y;
    assert(fscanf(f, "%d %d", &x, &y) == 2);
    assert(x == 1 && y == 1);
    fclose(f);

    remove("out.txt");
    free_pentomino(p);
}

void TestWritePentomino_Null_no12() {
    write_pentomino(NULL, "out2.txt");
    FILE* f = fopen("out2.txt", "r");
    int v;
    assert(fscanf(f, "%d", &v) == 1);
    assert(v == 0);
    fclose(f);
    remove("out2.txt");
}


void TestInitFreePentomino_no13() {
    Pentomino* p = init_pentomino();
    assert(p != NULL);
    free_pentomino(p);
}

void TestInitFreeField_no14() {
    Field* f = init_field(4, 4);
    assert(f->width == 4);
    free_field(f);
}

int main() {
    printf("Running Pentomino tests...\n");

    TestLoadPentomino_ValidFile_no1();
    TestLoadPentomino_FileNotFound_no2();
    TestLoadPentomino_TooManyCells_no3();
    TestValidPentomino_Correct_no4();
    TestValidPentomino_DuplicateCells_no5();
    TestValidPentomino_NotEnoughCells_no6();
    TestRotatePentomino_Normal_no7();
    TestCanPlace_EmptyField_no8();
    TestCanPlace_OutOfBounds_no9();
    TestCanPlace_CellOccupied_no10();
    TestWritePentomino_Valid_no11();
    TestWritePentomino_Null_no12();
    TestInitFreePentomino_no13();
    TestInitFreeField_no14();

    printf("All tests passed successfully!\n");
    return 0;
}
