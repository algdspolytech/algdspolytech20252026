#include "VertexCover.h"
#include <assert.h>


//subfunction to make a files for proper testing functions
void create_test_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", content);
    fclose(file);
}

void test_Load_graph_n0_Valid_file_Graph() {
    printf("Testing load_graph with valid file\n");

    create_test_file("test_valid.txt", "3 2\n1 2\n2 3\n1 3\n");

    int k;
    Graph *g = load_graph("test_valid.txt", &k);

    assert(g != NULL);
    assert(k == 2);
    assert(g->vertex_count == 3);
    assert(g->edge_count == 3);

    assert(g->edges[0].u == 1 && g->edges[0].v == 2);
    assert(g->edges[1].u == 2 && g->edges[1].v == 3);
    assert(g->edges[2].u == 1 && g->edges[2].v == 3);

    free_graph(g);
    remove("test_valid.txt");
    printf("test_load_graph_success passed\n");
}

void test_Load_graph_n1_Non_exis_file_Null() {
    printf("Testing load_graph with non-existent file\n");

    int k;
    Graph *g = load_graph("non_existent_file.txt", &k);

    assert(g == NULL);
    printf("test_load_graph_file_not_found passed\n");
}

void test_Load_graph_n2_Invalid_data_Null() {
    printf("Testing load_graph with invalid format\n");

    create_test_file("test_invalid.txt", "invalid data\n");

    int k;
    Graph *g = load_graph("test_invalid.txt", &k);

    assert(g == NULL);

    remove("test_invalid.txt");
    printf("test_load_graph_invalid_format passed\n");
}

void Load_graph_tests() {
    test_Load_graph_n0_Valid_file_Graph();
    test_Load_graph_n1_Non_exis_file_Null();
    test_Load_graph_n2_Invalid_data_Null();
}

void test_Add_vertex_n0_Valid_verts_Cover() {
    printf("Testing add_vertex_valid\n");

    VertexCover *ds = init_vertex_cover();

    add_vertex(ds, 1);
    assert(ds->count == 1);
    assert(ds->vertices[0] == 1);

    add_vertex(ds, 435);
    assert(ds->count == 2);
    assert(ds->vertices[0] == 1);
    assert(ds->vertices[1] == 435);

    free_vertex_cover(ds);
    printf("add_vertex_valid passed\n");
}

void test_Add_vertex_n1_Invalid_verts_Init_cover() {
    printf("Testing add_vertex_invalid\n");

    VertexCover *ds = init_vertex_cover();
    add_vertex(ds, -15);
    assert(ds->count == 0);
    assert(ds->vertices == NULL);

    add_vertex(ds, 456423);
    assert(ds->count == 0);
    assert(ds->vertices == NULL);

    free_vertex_cover(ds);
    printf("add_vertex_invalid passed\n");
}

void Add_vertex_tests() {
    test_Add_vertex_n0_Valid_verts_Cover();
    test_Add_vertex_n1_Invalid_verts_Init_cover();
}

void test_Check_cover_n0_Valid_cover_Cover() {
    printf("Testing check_cover with valid cover\n");

    Graph *g = init_graph();
    g->vertex_count = 3;

    g->edges = (Edge *) malloc(3 * sizeof(Edge));
    g->edges[0].u = 1;
    g->edges[0].v = 2;
    g->edges[1].u = 2;
    g->edges[1].v = 3;
    g->edges[2].u = 1;
    g->edges[2].v = 3;
    g->edge_count = 3;

    VertexCover *ds = init_vertex_cover();
    add_vertex(ds, 1);

    int result = check_cover(g, ds);
    assert(result == 1);

    free_vertex_cover(ds);
    free_graph(g);
    printf("check_cover_valid passed\n");
}

void test_Check_cover_n1_Invalid_cover_Null() {
    printf("Testing check_cover with invalid cover\n");

    Graph *g = init_graph();
    g->vertex_count = 3;

    g->edges = (Edge *) malloc(2 * sizeof(Edge));
    g->edges[0].u = 1;
    g->edges[0].v = 2;
    g->edges[1].u = 2;
    g->edges[1].v = 3;
    g->edge_count = 2;

    VertexCover *ds = init_vertex_cover();
    add_vertex(ds, 1);

    int result = check_cover(g, ds);
    assert(result == 0);

    free_vertex_cover(ds);
    free_graph(g);
    printf("check_cover_invalid passed\n");
}

void Check_cover_tests() {
    test_Check_cover_n0_Valid_cover_Cover();
    test_Check_cover_n1_Invalid_cover_Null();
}

void test_Find_vertex_cover_n0_Valid_graph_Cover() {
    printf("Testing find_vertex_cover when solution exists\n");

    Graph *g = init_graph();
    g->vertex_count = 3;
    g->edges = (Edge *) malloc(3 * sizeof(Edge));
    g->edges[0].u = 1;
    g->edges[0].v = 2;
    g->edges[1].u = 2;
    g->edges[1].v = 3;
    g->edges[2].u = 1;
    g->edges[2].v = 3;
    g->edge_count = 3;

    VertexCover *ds = find_vertex_cover(g, 1, 1);
    assert(ds != NULL);
    assert(ds->count == 1);

    int valid = check_cover(g, ds);
    assert(valid == 1);

    free_vertex_cover(ds);
    free_graph(g);
    printf("find_vertex_cover_valid passed\n");
}

void test_Find_vertex_cover_n1_Invalid_graph_Null() {
    printf("Testing find_vertex_cover when no solution exists\n");

    Graph *g = init_graph();
    g->vertex_count = 4;
    g->edges = (Edge *) malloc(3 * sizeof(Edge));
    g->edges[0].u = 1;
    g->edges[0].v = 2;
    g->edges[1].u = 2;
    g->edges[1].v = 3;
    g->edges[2].u = 3;
    g->edges[2].v = 4;
    g->edge_count = 3;

    VertexCover *ds = find_vertex_cover(g, 0, 1);
    assert(ds == NULL);

    free_graph(g);
    printf("find_vertex_cover_invalid passed\n");
}
void Find_vertex_cover_tests() {
    test_Find_vertex_cover_n0_Valid_graph_Cover();
    test_Find_vertex_cover_n1_Invalid_graph_Null();
}
void test_Write_vertex_cover_n0_Valid_cover_Valid_file() {
    printf("Testing write_vertex_cover with valid cover\n");

    VertexCover *ds = init_vertex_cover();
    add_vertex(ds, 1);
    add_vertex(ds, 3);

    FILE *output_file = fopen("test_output.txt", "w");

    write_vertex_cover(ds, "test_output.txt");


    fclose(output_file);


    FILE *file = fopen("test_output.txt", "r");
    assert(file != NULL);
    int u,v;
    assert(fscanf(file, "%d %d", &u, &v)==2);
    assert(u==1);
    assert(v==3);

    fclose(file);
    free_vertex_cover(ds);
    remove("test_output.txt");
    printf("write_vertex_cover_valid passed\n");
}

void test_Write_vertex_cover_n1_Null_cover_0() {
    printf("Testing write_vertex_cover with NULL\n");

    FILE *output_file = fopen("test_output_null.txt", "w");

    write_vertex_cover(NULL, "test_output_null.txt");

    fclose(output_file);

    FILE *file = fopen("test_output_null.txt", "r");
    assert(file != NULL);
    int u;
    assert(fscanf(file, "%d", &u)==1);
    assert(u==0);

    fclose(file);
    remove("test_output_null.txt");
    printf("write_vertex_cover_0 passed\n");
}

void Write_vertex_cover_tests() {
    test_Write_vertex_cover_n0_Valid_cover_Valid_file();
    test_Write_vertex_cover_n1_Null_cover_0();
}

int main() {
    printf("Running unit tests\n\n");

    Load_graph_tests();
    Add_vertex_tests();
    Check_cover_tests();
    Find_vertex_cover_tests();
    Write_vertex_cover_tests();

    printf("\nAll tests passed\n");
    return 0;
}
