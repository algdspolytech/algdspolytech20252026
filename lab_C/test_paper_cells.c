#include <stdio.h>
#include "paper_cells.h"

static int total = 0;
static int passed = 0;
static int failed = 0;

#define TEST_START() printf("T %s\n", __func__)

#define TEST_ASSERT(condition) \
    do { \
        total++; \
        if (condition) { \
            passed++; \
            printf("P\n"); \
        } else { \
            failed++; \
            printf("F %s:%d\n", __FILE__, __LINE__); \
        } \
    } while(0)

#define TEST_EQUAL(expected, actual) \
    TEST_ASSERT((expected) == (actual))

#define TEST_NULL(ptr) \
    TEST_ASSERT((ptr) == NULL)

#define TEST_NOT_NULL(ptr) \
    TEST_ASSERT((ptr) != NULL)

void test_create_paper_valid_no1(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(3, 4);
    TEST_NOT_NULL(paper);
    TEST_EQUAL(3, paper->rows);
    TEST_EQUAL(4, paper->cols);
    destroy_paper(paper);
}

void test_create_paper_invalid_no2(void)
{
    TEST_START();
    PaperGrid* paper1 = create_paper(0, 5);
    TEST_NULL(paper1);
    PaperGrid* paper2 = create_paper(5, -1);
    TEST_NULL(paper2);
}

void test_remove_cells_valid_no3(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(3, 3);
    TEST_NOT_NULL(paper);

    int coords[2][2] = { {0,0}, {1,1} };
    remove_cells(paper, 2, coords);

    TEST_EQUAL(0, paper->grid[0][0]);
    TEST_EQUAL(0, paper->grid[1][1]);
    TEST_EQUAL(1, paper->grid[2][2]);

    destroy_paper(paper);
}

void test_remove_cells_invalid_no4(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(2, 2);
    TEST_NOT_NULL(paper);

    int coords[2][2] = { {5,5}, {-1,-1} };
    remove_cells(paper, 2, coords);

    TEST_EQUAL(1, paper->grid[0][0]);
    TEST_EQUAL(1, paper->grid[1][1]);

    destroy_paper(paper);
}

void test_count_fragments_full_no5(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(2, 2);
    TEST_NOT_NULL(paper);

    int count = count_fragments(paper);
    TEST_EQUAL(1, count);

    destroy_paper(paper);
}

void test_count_fragments_single_removal_no6(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(3, 3);
    TEST_NOT_NULL(paper);

    int coords[1][2] = { {1,1} };
    remove_cells(paper, 1, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(1, count);

    destroy_paper(paper);
}

void test_count_fragments_four_parts_no7(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(3, 3);
    TEST_NOT_NULL(paper);

    int coords[5][2] = { {0,1}, {1,0}, {1,1}, {1,2}, {2,1} };
    remove_cells(paper, 5, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(4, count);

    destroy_paper(paper);
}

void test_count_fragments_empty_no8(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(2, 2);
    TEST_NOT_NULL(paper);

    int coords[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} };
    remove_cells(paper, 4, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(0, count);

    destroy_paper(paper);
}

void test_count_fragments_checkerboard_no9(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(4, 4);
    TEST_NOT_NULL(paper);

    int coords[8][2] = { {0,0}, {0,2}, {1,1}, {1,3}, {2,0}, {2,2}, {3,1}, {3,3} };
    remove_cells(paper, 8, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(8, count);

    destroy_paper(paper);
}

void test_count_fragments_row_no10(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(1, 5);
    TEST_NOT_NULL(paper);

    int coords[2][2] = { {0,1}, {0,3} };
    remove_cells(paper, 2, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(3, count);

    destroy_paper(paper);
}

void test_count_fragments_column_no11(void)
{
    TEST_START();
    PaperGrid* paper = create_paper(5, 1);
    TEST_NOT_NULL(paper);

    int coords[2][2] = { {1,0}, {3,0} };
    remove_cells(paper, 2, coords);

    int count = count_fragments(paper);
    TEST_EQUAL(3, count);

    destroy_paper(paper);
}

void test_count_fragments_null_no12(void)
{
    TEST_START();
    int count = count_fragments(NULL);
    TEST_EQUAL(0, count);
}

void run_all_tests(void) {
    printf("PAPER_CELLS_TESTS\n");

    test_create_paper_valid_no1();
    test_create_paper_invalid_no2();
    test_remove_cells_valid_no3();
    test_remove_cells_invalid_no4();
    test_count_fragments_full_no5();
    test_count_fragments_single_removal_no6();
    test_count_fragments_four_parts_no7();
    test_count_fragments_empty_no8();
    test_count_fragments_checkerboard_no9();
    test_count_fragments_row_no10();
    test_count_fragments_column_no11();
    test_count_fragments_null_no12();

    printf("SUMMARY\n");
    printf("TOTAL:%d\n", total);
    printf("PASSED:%d\n", passed);
    printf("FAILED:%d\n", failed);
    printf("RATE:%.1f\n", (float)passed / total * 100);

    if (failed == 0)
    {
        printf("ALL_OK\n");
    }
    else
    {
        printf("SOME_FAILED\n");
    }
}
