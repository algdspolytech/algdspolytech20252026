#include <stdio.h>
#include <stdlib.h>
#include "graph_utils.h"

static int ok = 0;
static int fail = 0;

#define CHECK(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("ERROR: %s\n", msg); \
            fail++; \
            return; \
        } \
    } while (0)

void test_init_graph_StandardCase_t1(void) {
    Graph* g = init_graph(4);
    CHECK(g != NULL, "Graph should be created");
    CHECK(g->nodes == 4, "Should have 4 nodes");

    for (int i = 0; i < 4; i++) {
        CHECK(g->connections[i] == NULL, "All connections should be empty");
    }

    release_graph(g);
    ok++;
    printf("OK: test_init_graph_StandardCase_t1\n");
}

void test_link_nodes_SingleLink_t2(void) {
    Graph* g = init_graph(3);

    link_nodes(g, 0, 1);
    CHECK(g->connections[0] != NULL, "Link should exist");
    CHECK(g->connections[0]->target == 1, "Should point to node 1");
    CHECK(g->connections[0]->link == NULL, "Should be single link");

    release_graph(g);
    ok++;
    printf("OK: test_link_nodes_SingleLink_t2\n");
}

void test_link_nodes_MultipleLinks_t3(void) {
    Graph* g = init_graph(3);

    link_nodes(g, 0, 1);
    link_nodes(g, 0, 2);

    CHECK(g->connections[0] != NULL, "Links should exist");
    CHECK(g->connections[0]->target == 2, "First link to node 2");
    CHECK(g->connections[0]->link != NULL, "Should have next link");
    CHECK(g->connections[0]->link->target == 1, "Second link to node 1");

    release_graph(g);
    ok++;
    printf("OK: test_link_nodes_MultipleLinks_t3\n");
}

void test_grid_to_graph_EmptyGrid_t4(void) {
    Grid* data = malloc(sizeof(Grid));
    data->grid = NULL;
    data->dimension = 0;

    Graph* g = grid_to_graph(data);
    CHECK(g == NULL, "Should return NULL for empty grid");

    free(data);
    ok++;
    printf("OK: test_grid_to_graph_EmptyGrid_t4\n");
}

void test_grid_to_graph_SingleNode_t5(void) {
    Grid* data = malloc(sizeof(Grid));
    data->dimension = 1;
    data->grid = malloc(sizeof(int*));
    data->grid[0] = malloc(sizeof(int));
    data->grid[0][0] = 0;

    Graph* g = grid_to_graph(data);
    CHECK(g != NULL, "Graph should be created");
    CHECK(g->nodes == 1, "Should have 1 node");
    CHECK(g->connections[0] == NULL, "Should have no links");

    release_graph(g);
    release_grid(data);
    ok++;
    printf("OK: test_grid_to_graph_SingleNode_t5\n");
}

void test_grid_to_graph_TwoNodes_t6(void) {
    Grid* data = malloc(sizeof(Grid));
    data->dimension = 2;
    data->grid = malloc(2 * sizeof(int*));
    data->grid[0] = malloc(2 * sizeof(int));
    data->grid[1] = malloc(2 * sizeof(int));

    data->grid[0][0] = 0;
    data->grid[0][1] = 1;
    data->grid[1][0] = 1;
    data->grid[1][1] = 0;

    Graph* g = grid_to_graph(data);
    CHECK(g != NULL, "Graph should be created");
    CHECK(g->connections[0] != NULL, "Node 0 should have links");
    CHECK(g->connections[0]->target == 1, "Node 0 links to node 1");
    CHECK(g->connections[1] != NULL, "Node 1 should have links");
    CHECK(g->connections[1]->target == 0, "Node 1 links to node 0");

    release_graph(g);
    release_grid(data);
    ok++;
    printf("OK: test_grid_to_graph_TwoNodes_t6\n");
}

void test_grid_to_graph_NoLinks_t7(void) {
    Grid* data = malloc(sizeof(Grid));
    data->dimension = 3;
    data->grid = malloc(3 * sizeof(int*));

    for (int i = 0; i < 3; i++) {
        data->grid[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            data->grid[i][j] = 0;
        }
    }

    Graph* g = grid_to_graph(data);
    CHECK(g != NULL, "Graph should be created");

    for (int i = 0; i < 3; i++) {
        CHECK(g->connections[i] == NULL, "All nodes should have no links");
    }

    release_graph(g);
    release_grid(data);
    ok++;
    printf("OK: test_grid_to_graph_NoLinks_t7\n");
}

void test_grid_to_graph_FullLinks_t8(void) {
    Grid* data = malloc(sizeof(Grid));
    data->dimension = 2;
    data->grid = malloc(2 * sizeof(int*));
    data->grid[0] = malloc(2 * sizeof(int));
    data->grid[1] = malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            data->grid[i][j] = 1;
        }
    }

    Graph* g = grid_to_graph(data);
    CHECK(g != NULL, "Graph should be created");

    for (int i = 0; i < 2; i++) {
        int cnt = 0;
        Edge* e = g->connections[i];
        while (e != NULL) {
            cnt++;
            e = e->link;
        }
        CHECK(cnt == 2, "Each node should have 2 links");
    }

    release_graph(g);
    release_grid(data);
    ok++;
    printf("OK: test_grid_to_graph_FullLinks_t8\n");
}

void test_release_NullInput_t9(void) {
    release_graph(NULL);
    release_grid(NULL);

    ok++;
    printf("OK: test_release_NullInput_t9\n");
}

void test_load_grid_BadFile_t10(void) {
    Grid* d = load_grid("missing.txt");
    CHECK(d == NULL, "Should return NULL for bad file");

    ok++;
    printf("OK: test_load_grid_BadFile_t10\n");
}

void execute_tests(void) {
    printf("Running tests...\n\n");

    test_init_graph_StandardCase_t1();
    test_link_nodes_SingleLink_t2();
    test_link_nodes_MultipleLinks_t3();
    test_grid_to_graph_EmptyGrid_t4();
    test_grid_to_graph_SingleNode_t5();
    test_grid_to_graph_TwoNodes_t6();
    test_grid_to_graph_NoLinks_t7();
    test_grid_to_graph_FullLinks_t8();
    test_release_NullInput_t9();
    test_load_grid_BadFile_t10();

    printf("\n=== SUMMARY ===\n");
    printf("Passed: %d\n", ok);
    printf("Failed: %d\n", fail);
    printf("Total:  %d\n", ok + fail);
}