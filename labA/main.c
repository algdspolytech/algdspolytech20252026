#include <stdio.h>
#include "stack_list.h"
#include "stack_array.h"

void demoStackList()
{
    printf("=== Stack List Demo ===\n");
    StackList* stack = createStackList();

    pushList(stack, 10);
    pushList(stack, 20);
    pushList(stack, 30);

    printf("Stack size: %zu\n", sizeList(stack));

    int value;
    while (popList(stack, &value))
    {
        printf("Popped: %d\n", value);
    }

    destroyStackList(stack);
}

void demoStackArray()
{
    printf("=== Stack Array Demo ===\n");
    StackArray* stack = createStackArray();

    pushArray(stack, 100);
    pushArray(stack, 200);
    pushArray(stack, 300);

    printf("Stack size: %zu\n", sizeArray(stack));

    int value;
    while (popArray(stack, &value))
    {
        printf("Popped: %d\n", value);
    }

    destroyStackArray(stack);
}

int main()
{
    demoStackList();
    printf("\n");
    demoStackArray();
    run_all_tests();
    return 0;
}