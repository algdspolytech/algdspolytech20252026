#include "hamilton.h"
#include <assert.h>


void create_test_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s", content);
    fclose(f);
}


int read_output(const char* filename, int result[]) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    int val, count = 0;
    if (fscanf(f, "%d", &val) == 1 && val == 0) {
        fclose(f);
        return 0;  // путь не существует
    }
    rewind(f);

    while (fscanf(f, "%d", &val) == 1) {
        result[count++] = val - 1; 
    }
    fclose(f);
    return count;
}


void TestFindHamiltonianPath_LinearGraph_HappyPath_no1() {
    const char* input =
        "3\n"
        "2\n"
        "1 3\n"
        "2\n";

    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;

    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
            break;
        }
    }

    assert(found);
    assert(is_valid_hamiltonian_path(g, path));
    print_path_to_file("output.txt", path, g->n);

    int result[MAX_V];
    int len = read_output("output.txt", result);
    assert(len == 3);
    assert(result[0] == 0 || result[0] == 2);  
    free_graph(g);
    printf("Test no1 PASSED\n");
}


void TestFindHamiltonianPath_IsolatedVertex_returnFalse_no2() {
    const char* input =
        "3\n"
        "2\n"
        "1\n"
        "\n";  

    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;

    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
            break;
        }
    }

    assert(!found);
    print_path_to_file("output.txt", path, 0);  // 0 означает нет пути

    int result[MAX_V];
    int len = read_output("output.txt", result);
    assert(len == 0);
    free_graph(g);
    printf("Test no2 PASSED\n");
}


void TestFindHamiltonianPath_OneVertex_returnValidVal_no3() {
    const char* input = "1\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];

    bool found = find_hamiltonian_path(g, path, 0);
    assert(found);
    assert(path[0] == 0);
    print_path_to_file("output.txt", path, g->n);

    int result[MAX_V];
    int len = read_output("output.txt", result);
    assert(len == 1 && result[0] == 0);
    free_graph(g);
    printf("Test no3 PASSED\n");
}


void TestFindHamiltonianPath_TwoConnected_returnValidVal_no4() {
    const char* input =
        "2\n"
        "2\n"
        "1\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V] = { 0 };
    bool found = find_hamiltonian_path(g, path, 0);
    assert(found);
    assert(is_valid_hamiltonian_path(g, path));
    print_path_to_file("output.txt", path, g->n);
    free_graph(g);
    printf("Test no4 PASSED\n");
}


void TestFindHamiltonianPath_TwoDisconnected_returnFalse_no5() {
    const char* input =
        "2\n"
        "\n"
        "\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
            break;
        }
    }
    assert(!found);
    print_path_to_file("output.txt", path, 0);
    free_graph(g);
    printf("Test no5 PASSED\n");
}


void TestFindHamiltonianPath_CompleteGraph_HappyPath_no6() {
    const char* input =
        "4\n"
        "2 3 4\n"
        "1 3 4\n"
        "1 2 4\n"
        "1 2 3\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
        }
    }
    assert(found);
    assert(is_valid_hamiltonian_path(g, path));
    print_path_to_file("output.txt", path, g->n);
    free_graph(g);
    printf("Test no6 PASSED\n");
}


void TestFindHamiltonianPath_CycleGraph_HappyPath_no7() {
    const char* input =
        "4\n"
        "2 4\n"
        "1 3\n"
        "2 4\n"
        "1 3\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
        }
    }
    assert(found);
    print_path_to_file("output.txt", path, g->n);
    free_graph(g);
    printf("Test no7 PASSED\n");
}


void TestFindHamiltonianPath_StarGraph_HappyPath_no8() {
    const char* input =
        "4\n"
        "2 3 4\n"
        "1\n"
        "1\n"
        "1\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
        }
    }
    assert(found);
    assert(is_valid_hamiltonian_path(g, path));
    print_path_to_file("output.txt", path, g->n);
    free_graph(g);
    printf("Test no8 PASSED\n");
}


void TestFindHamiltonianPath_DisconnectedGraph_returnFalse_no9() {
    const char* input =
        "4\n"
        "2\n"
        "1\n"
        "4\n"
        "3\n";
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
        }
    }
    assert(!found);
    print_path_to_file("output.txt", path, 0);
    free_graph(g);
    printf("Test no9 PASSED\n");
}


void TestFindHamiltonianPath_DeadEnd_returnFalse_no10() {
    const char* input =
        "4\n"
        "2\n"
        "1 3\n"
        "2\n"
        "\n";  
    create_test_file("input.txt", input);
    Graph* g = create_graph_from_file("input.txt");
    int path[MAX_V];
    bool found = false;
    for (int start = 0; start < g->n && !found; start++) {
        if (find_hamiltonian_path(g, path, start)) {
            found = true;
        }
    }
    assert(!found);
    print_path_to_file("output.txt", path, 0);
    free_graph(g);
    printf("Test no10 PASSED\n");
}


int main() {
    int passed = 0;
    int total = 10;

    TestFindHamiltonianPath_LinearGraph_HappyPath_no1(); passed++;
    TestFindHamiltonianPath_IsolatedVertex_returnFalse_no2(); passed++;
    TestFindHamiltonianPath_OneVertex_returnValidVal_no3(); passed++;
    TestFindHamiltonianPath_TwoConnected_returnValidVal_no4(); passed++;
    TestFindHamiltonianPath_TwoDisconnected_returnFalse_no5(); passed++;
    TestFindHamiltonianPath_CompleteGraph_HappyPath_no6(); passed++;
    TestFindHamiltonianPath_CycleGraph_HappyPath_no7(); passed++;
    TestFindHamiltonianPath_StarGraph_HappyPath_no8(); passed++;
    TestFindHamiltonianPath_DisconnectedGraph_returnFalse_no9(); passed++;
    TestFindHamiltonianPath_DeadEnd_returnFalse_no10(); passed++;

    printf("\nУспешно пройдено: %d из %d тестов\n", passed, total);
    return 0;
}