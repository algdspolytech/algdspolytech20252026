#include <assert.h>
#include "Search_Graph.h"

void test_Push_q_n0_Valid_elem_Quque() {
    Queue q;
    init_queue(&q);

    printf("Test 1: Pushing valid element\n");
    push_q(&q, 124);
    assert(q.first != NULL);
    assert(q.last != NULL);
    assert(q.first == q.last);
    assert(q.first->neigh == 124);
    assert(q.first->prev == NULL);

    free_queue(&q);
    printf("Single element push: PASSED\n");
}
void test_Push_q_n1_Valid_elems_FIFO_ordered_queue(){
    Queue q;
    init_queue(&q);

    printf("Test 2: Push multipele elements, checking queue order\n");
    push_q(&q, 124);
    assert(q.first != NULL);
    assert(q.last != NULL);
    assert(q.first == q.last);
    assert(q.first->neigh == 124);
    assert(q.first->prev == NULL);

    push_q(&q, 235);
    assert(q.first != NULL);
    assert(q.last != NULL);
    assert(q.first != q.last);
    assert(q.last->neigh == 235);
    assert(q.first->neigh == 124);
    assert(q.first->prev == q.last);

    push_q(&q, 333);
    assert(q.last->neigh == 333);
    assert(q.first->neigh == 124);
    assert(q.first->prev->neigh == 235);
    assert(q.first->prev->prev->neigh == 333);
    free_queue(&q);
    printf("Multiple elements push: PASSED\n");}

void test_Push_q_n2_Invalid_elem_Empty_queue(){
    Queue q;
    init_queue(&q);

    printf("Test 3: Push invalid element \n");
    push_q(&q, -324);
    assert(q.last == NULL);
    assert(q.first == NULL);
    assert(q.last == q.first);
    free_queue(&q);
    printf("Push invalid element: PASSED\n");
}

void test_Push_q_n3_Zero_elem_Push_Valid_queue() {
    Queue q;
    init_queue(&q);
    printf("Test 4: Push zero \n");
    push_q(&q, 0);
    assert(q.last->neigh == 0);
    printf("Push zero: PASSED\n");
    free_queue(&q);
}

void test_push_q() {
    printf("Testing push_q function\n");

    test_Push_q_n0_Valid_elem_Quque();
    test_Push_q_n1_Valid_elems_FIFO_ordered_queue();
    test_Push_q_n2_Invalid_elem_Empty_queue();
    test_Push_q_n3_Zero_elem_Push_Valid_queue();

    printf("All push_q tests passed\n\n");
}

void test_Pop_q_n0_Empty_queue_Minus_one(){
    Queue q;
    init_queue(&q);

    printf("Test 1: Pop from empty queue\n");
    int result = pop_q(&q);
    assert(result == -1);
    assert(q.first == NULL);
    assert(q.last == NULL);
    printf("Pop from empty queue: PASSED\n");
    free_queue(&q);
}

void test_Pop_q_n1_Valid_queue_pop_Int_number() {
    Queue q;
    init_queue(&q);

    printf("Test 2: Pop an element\n");

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nMemory allocation error. test_pop_n1\n");
        exit(-1);
    }

    newNode->neigh = 42;
    newNode->prev = NULL;

    q.first = newNode;
    q.last = newNode;

    int result = pop_q(&q);
    assert(result == 42);
    assert(q.first == NULL);
    assert(q.last == NULL);
    printf("Single element pop: PASSED\n");
    free_queue(&q);
}


void test_Pop_q_n2_FIFO_oreder_pop_Right_ordered_poping() {
    Queue q;
    init_queue(&q);
    printf("Test 3: Checking FIFO order pop queue\n");

    Node *newNode_2 = (Node *) malloc(sizeof(Node));
    if (newNode_2 == NULL) {
        printf("\nMemory allocation error. test_pop_n2\n");
        exit(-1);
    }

    newNode_2->neigh = 9383;
    newNode_2->prev = NULL;

    Node *newNode_1 = (Node *) malloc(sizeof(Node));
    if (newNode_1 == NULL) {
        printf("\nMemory allocation error. test_pop_n2\n");
        exit(-1);
    }

    newNode_1->neigh = 3876;
    newNode_1->prev = newNode_2;

    Node *newNode_0 = (Node *) malloc(sizeof(Node));
    if (newNode_0 == NULL) {
        printf("\nMemory allocation error. test_pop_n2\n");
        exit(-1);
    }

    newNode_0->neigh = 324;
    newNode_0->prev = newNode_1;

    q.first = newNode_0;
    q.last = newNode_2;

    int result = pop_q(&q);
    assert(result == 324);
    assert(q.first != NULL);
    assert(q.first->neigh == 3876);
    result = pop_q(&q);
    assert(result == 3876);
    assert(q.first != NULL);
    assert(q.first->neigh == 9383);
    result = pop_q(&q);
    assert(result == 9383);
    assert(q.first == NULL);
    assert(q.last == NULL);
    printf("Pop FIFO order: PASSED\n");
    free_queue(&q);
}
void test_pop_q() {
    printf("Testing pop_q function\n");

    test_Pop_q_n0_Empty_queue_Minus_one();
    test_Pop_q_n1_Valid_queue_pop_Int_number();
    test_Pop_q_n2_FIFO_oreder_pop_Right_ordered_poping();

    printf("All pop_q tests passed\n");
}

void test_Free_queue_n0_Empty_queue_Empty_queue() {
    printf("Test 1: Using free_queue on empty queue\n");
    Queue q;
    init_queue(&q);
    free_queue(&q);
    assert(q.first == NULL);
    assert(q.last == NULL);
    printf("Using free_queue on empty queue: PASSED\n");
}

void test_Free_queue_n1_Empting_queue_Empty_queue() {
    printf("Test 1: Using free_queue on queue\n");
    Queue q;
    init_queue(&q);

    Node *newNode_1 = (Node *) malloc(sizeof(Node));
    if (newNode_1 == NULL) {
        printf("\nMemory allocation error. test_Free_queue_n1\n");
        exit(-1);
    }

    Node *newNode_2 = (Node *) malloc(sizeof(Node));
    if (newNode_2 == NULL) {
        printf("\nMemory allocation error. test_Free_queue_n1\n");
        exit(-1);
    }

    Node *newNode_3 = (Node *) malloc(sizeof(Node));
    if (newNode_3 == NULL) {
        printf("\nMemory allocation error. test_Free_queue_n1\n");
        exit(-1);
    }

    newNode_1->neigh = 23;
    newNode_1->prev = NULL;

    newNode_2->neigh = 1421;
    newNode_2->prev = newNode_1;

    newNode_3->neigh = 29023974;
    newNode_3->prev = newNode_2;

    q.first = newNode_3;
    q.last = newNode_1;

    assert(q.first != NULL);
    assert(q.last != NULL);
    assert(q.first != q.last);
    assert(q.last->neigh == 23);
    assert(q.first->neigh == 29023974);
    free_queue(&q);
    assert(q.first == NULL);
    assert(q.last == NULL);

    printf("Using free_queue on queue: PASSED\n");
}

void test_free_queue() {
    printf("Testing free_queue function\n");
    test_Free_queue_n0_Empty_queue_Empty_queue();
    test_Free_queue_n1_Empting_queue_Empty_queue();
    printf("All free_queue test passed\n");
}

void test_Read_graph_n0_Valid_txt_Valid_matrix() {
    printf("Test 1: Read valid graph\n");
    Graph g = read_graph("matrix.txt");
    assert(g.num_verts == 15);
    assert(g.matrix != NULL);
    assert(g.matrix[3][0]==1);
    free_graph(&g);
    printf("Read valid graph: PASSED\n");
}

void test_Read_graph_n1_NULL_txt_No_matrix() {
    printf("Test 2: Read non-existent file\n");
    Graph g = read_graph("AMOGUS.txt");
    assert(g.num_verts == 0);
    printf("Pop empty queue: PASSED\n");
}

void test_Read_graph_n2_Invalid_content_txt_No_matrix() {
    printf("Test 3: Read invalid file\n");
    Graph g = read_graph("1_number_test.txt");
    assert(g.num_verts == 0);
    printf("Pop empty queue: PASSED\n");
}

void test_read_graph() {
    printf("Testing graph reading\n");

    test_Read_graph_n0_Valid_txt_Valid_matrix();
    test_Read_graph_n1_NULL_txt_No_matrix();
    test_Read_graph_n2_Invalid_content_txt_No_matrix();

    printf("Graph reading tests passed\n");
}

void test_Pathfinder_n0_Path_to_element_itself_Zero() {
    int **matrix_1 = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrix_1[i] = (int*)malloc(3 * sizeof(int));
        for (int j = 0; j < i+1; j++) {
            matrix_1[i][j] = 0;
        }
    }

    matrix_1[0][0] = 0;
    matrix_1[1][0] = 1; matrix_1[1][1] = 0;
    matrix_1[2][0] = 1; matrix_1[2][1] = 1; matrix_1[2][2] = 0;

    Graph g;
    g.num_verts = 3;
    g.matrix = matrix_1;


    printf("Test 1: Path to itself\n");
    assert(pathfinder(&g, 0, 0) == 0);
    printf(" Path to itself: PASSED\n");
    free_graph(&g);

}

void test_Pathfinder_n1_Path_to_invalid_vertesies_Minus_one() {
    int **matrix = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrix[i] = (int*)malloc(3 * sizeof(int));
        for (int j = 0; j < i + 1; j++) {
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 0;
    matrix[1][0] = 1; matrix[1][1] = 0;
    matrix[2][0] = 1; matrix[2][1] = 1; matrix[2][2] = 0;

    Graph g;
    g.num_verts = 3;
    g.matrix = matrix;

    printf("Test 2: Invalid vertices\n");
    assert(pathfinder(&g, -235, 113) == -1);
    assert(pathfinder(&g, 12, 211) == -1);
    printf("Invalid vertices: PASSED\n");
    free_graph(&g);

}

void test_Pathfinder_n2_Path_to_unconected_vertesies_Minus_one() {
    int **matrix = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrix[i] = (int*)malloc(3 * sizeof(int));
        for (int j = 0; j < i + 1; j++) {
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 0;
    matrix[1][0] = 1; matrix[1][1] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 0;

    Graph g;
    g.num_verts = 3;
    g.matrix = matrix;

    printf("Test 3: Path to unconnected points\n");
    assert(pathfinder(&g, 0, 2) == -1);
    assert(pathfinder(&g, 1, 2) == -1);
    printf("Path to unconnected points: PASSED\n");
    free_graph(&g);

}

void test_Pathfinder_n3_Paths_lens_Correct_lens() {
    printf("Test 4: Correctness of length finding \n");
    int **matrix = (int**)malloc(5 * sizeof(int*));
    for (int i = 0; i < 5; i++) {
        matrix[i] = (int*)malloc(5 * sizeof(int));
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = 0;
        }
    }

    matrix[1][0] = 1;
    matrix[2][1] = 1;
    matrix[3][2] = 1;
    matrix[4][3] = 1;
    Graph g;
    g.num_verts = 5;
    g.matrix = matrix;

    assert(pathfinder(&g, 0, 0) == 0);
    assert(pathfinder(&g, 0, 1) == 1);
    assert(pathfinder(&g, 0, 2) == 2);
    assert(pathfinder(&g, 0, 3) == 3);
    assert(pathfinder(&g, 0, 4) == 4);
    printf("Correctness of finding the length: PASSED\n");
    free_graph(&g);
}

void test_Pathfinder_n4_invalid_vertesise_matrix_minus_one() {
    Graph g;
    printf("Test 5: Inputing matrix with number of ?vertesies? less than 2 ");
    g.num_verts = 1;
    assert(pathfinder(&g, 0, 4) == -1);
    g.num_verts = -97;
    assert(pathfinder(&g, 0, 4) == -1);
    printf("Inputing matrix with number of ?vertesies? less than 2: PASSED\n");
}

void test_Pathfinder_n5_Same_verts_lens_Same_lens() {
    printf("Test 6: Equality of routes from start to end and from end to start\n");
    int **matrix = (int**)malloc(5 * sizeof(int*));
    for (int i = 0; i < 5; i++) {
        matrix[i] = (int*)malloc(5 * sizeof(int));
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = 0;
        }
    }

    matrix[1][0] = 1;
    matrix[2][1] = 1;
    matrix[3][2] = 1;
    matrix[4][3] = 1;
    Graph g;
    g.num_verts = 5;
    g.matrix = matrix;

    assert(pathfinder(&g, 0, 1) == pathfinder(&g, 1 , 0));
    assert(pathfinder(&g, 0, 2) == pathfinder(&g, 2, 0));
    assert(pathfinder(&g, 0, 3) == pathfinder(&g, 3, 0));
    assert(pathfinder(&g, 0, 4) == pathfinder(&g, 4, 0));
    printf("Equality of routes from start to end and from end to start : PASSED\n");
    free_graph(&g);
}

void test_pathfinder() {
    printf("Testing pathfinder\n");
    test_Pathfinder_n0_Path_to_element_itself_Zero();
    test_Pathfinder_n1_Path_to_invalid_vertesies_Minus_one();
    test_Pathfinder_n2_Path_to_unconected_vertesies_Minus_one();
    test_Pathfinder_n3_Paths_lens_Correct_lens();
    test_Pathfinder_n4_invalid_vertesise_matrix_minus_one();
    test_Pathfinder_n5_Same_verts_lens_Same_lens();
    printf("All pathfinder tests passed\n");
}


int main() {
    test_pop_q();
    test_free_queue();
    test_push_q();
    test_read_graph();
    test_pathfinder();

    printf("\nAll tests passed\n");
    return 0;
}