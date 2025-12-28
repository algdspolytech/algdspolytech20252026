#include <stdio.h>
#include "set.h"


void demoSet(void)
{
    printf("=== SET DEMO ===\n");

    Set* set = set_create();

    set_add(set, 10);
    set_add(set, 5);
    set_add(set, 20);
    set_add(set, 10);

    printf("Contains 5: %s\n", set_contains(set, 5) ? "YES" : "NO");
    printf("Contains 15: %s\n", set_contains(set, 15) ? "YES" : "NO");

    set_remove(set, 5);
    printf("After remove 5, contains 5: %s\n",
        set_contains(set, 5) ? "YES" : "NO");

    set_destroy(set);
}


int main(void)
{
    demoSet();
    printf("\n");

    return 0;
}
