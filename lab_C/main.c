#include <stdio.h>
#include "paper_cells.h"

void demo_paper_cells(void)
{
    printf("DEMO\n");

    printf("EXAMPLE1\n");
    PaperGrid* paper1 = create_paper(3, 3);
    int coords1[1][2] = { {1,1} };
    remove_cells(paper1, 1, coords1);
    printf("FRAGMENTS:%d\n", count_fragments(paper1));
    destroy_paper(paper1);

    printf("EXAMPLE2\n");
    PaperGrid* paper2 = create_paper(3, 3);
    int coords2[5][2] = { {0,1}, {1,0}, {1,1}, {1,2}, {2,1} };
    remove_cells(paper2, 5, coords2);
    printf("FRAGMENTS:%d\n", count_fragments(paper2));
    destroy_paper(paper2);
}

int main(void)
{
    printf("START\n");
    demo_paper_cells();
    printf("\n");
    run_all_tests();
    return 0;
}
