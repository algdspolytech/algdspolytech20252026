#pragma warning(disable : 4996)
#include"adj.h"



void init_vec(Vec* v) {
    v->data = NULL;
    v->size = 0;
};
void vec_add_to_data(Vec* v) {
    int* new_entry = (int*)realloc(v->data, sizeof(int) * (v->size + 1));
    if (!new_entry) {
        return;
    }
    v->data = new_entry;

}

 void vec_push(Vec* v, int x) {
    vec_add_to_data(v);
    v->data[v->size] = x;
    v->size++;

}




 void init_graph(Graph* g) {
    g->adj = NULL;
    g->size = 0;
}

 void add_adj_to_graph(Graph* g, int n) {
    if (n <= g->size) return;

    Vec* new_vec = (Vec*)realloc(g->adj, n * sizeof(Vec));

    if (!new_vec) return;
    g->adj = new_vec;
    for (int i = g->size; i < n; i++) {
        init_vec(&g->adj[i]);
    }



    g->size = n;
}

void vec_free(Vec* v) {
    free(v->data);
    v->size = 0;
    v->data = NULL;
}


 void graph_free(Graph* g) {
    for (int i = 0; i < g->size; i++) {
        vec_free(&g->adj[i]);
    }
}



int read_adjlist_file(const char* path, Graph* g) {
    FILE* f = fopen(path, "r");
    if (!f) {
       
        return 0;
    }

    int vertex = -1;
    int number = 0;
    int reading_number = 0;
    int c;

    while ((c = fgetc(f)) != EOF) {
        if (isdigit(c)) {

            number = number * 10 + (c - '0');
            reading_number = 1;
        }
        else {
            if (reading_number) {

                if (vertex == -1) {

                    vertex = number - 1;
                    add_adj_to_graph(g, vertex + 1);
                }
                else {

                    int neighbor = number-1;

                    vec_push(&g->adj[vertex], neighbor);
                }
                number = 0;
                reading_number = 0;
            }

            if (c == '\n') {

                vertex = -1;
            }
        }
    }
    if (reading_number) {
        if (vertex == -1) {
            vertex = number - 1;
            add_adj_to_graph(g, vertex + 1);
        }
        else {
            int neighbor = number - 1;
            vec_push(&g->adj[vertex], neighbor);
        }
        number = 0;
        reading_number = 0;
    }

    fclose(f);
    return 1;
}

void print_graph(const Graph* g) {
 
    for (int i = 0; i < g->size; ++i) {
        printf("%d:", i + 1);
        for (int k = 0; k < g->adj[i].size; ++k) {
            printf(" %d", g->adj[i].data[k] + 1);
        }
        printf("\n");

    }
}



int read_adjmatrix_file(const char* path, Graph* g) {
    FILE* f = fopen(path, "r");
    if (!f) { 
        return 0;
    }

    int n = 0, ch;
    long pos = ftell(f);
    while (fscanf(f, "%d", &ch) == 1) {
        n++;
        int c = fgetc(f);
        if (c == '\n' || c == EOF) break;
        ungetc(c, f);
    }

    if (n == 0) { fclose(f); return 0; }

    fseek(f, pos, SEEK_SET);
    add_adj_to_graph(g, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            if (fscanf(f, "%d", &val) != 1) {
                
                fclose(f);
                return 0;
            }
            if (val) vec_push(&g->adj[i], j);
        }
    }

    fclose(f);
    return 1;
}

void sort_vec(Vec* v) {                       
    for (int i = 1; i < v->size; i++) {
        int key = v->data[i], j = i - 1;
        while (j >= 0 && v->data[j] > key) { v->data[j + 1] = v->data[j]; j--; }
        v->data[j + 1] = key;
    }
}

int graphs_equal(const Graph* a, const Graph* b) {
    if (a->size != b->size) return 0;
    int n = a->size;

  
    for (int i = 0; i < n; i++) {
     
        Vec va = { .data = NULL, .size = 0 };
        for (int k = 0; k < a->adj[i].size; k++)
        {
            vec_push(&va, a->adj[i].data[k]);
        }
        sort_vec(&va);


        Vec vb = { .data = NULL, .size = 0 };
        for (int k = 0; k < b->adj[i].size; k++)
        {
            vec_push(&vb, b->adj[i].data[k]);
        }
        sort_vec(&vb);

        int same = (va.size == vb.size);
        for (int k = 0;k < va.size; k++)
        {
            
                if (va.data[k] != vb.data[k])
                {
                    same = 0;
                    k = va.size;
                }
            
        }

        vec_free(&va);
        
        vec_free(&vb);

        if (!same) return 0;
    }
       return 1;
}