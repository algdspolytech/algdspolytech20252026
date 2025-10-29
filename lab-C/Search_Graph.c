#include "Search_Graph.h"

void init_queue(Queue *q) {
    q->first = NULL;
    q->last = NULL;
}

void push_q(Queue *q, int value) {
    if (value < 0){
        printf("\nNeigboure number can't be less than 0. push_q\n");
        return;
    }
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nMemory allocation error. push_q\n");
        exit(-1);
    }

    newNode->neigh = value;
    newNode->prev = NULL;

    if (q->first == NULL) {
        q->first = newNode;
        q->last = newNode;
    } else {
        q->last->prev = newNode;
        q->last = newNode;
    }


}

int pop_q(Queue *q) {
    if (q->first == NULL) {
        printf("\nQueue is empty\n");
        return -1;
    }

    Node *temp = q->first;
    q->first = q->first->prev;

    if (q->first == NULL) {
        q->last = NULL;
    }
    int item = temp->neigh;
    free(temp);
    return item;
}

void free_queue(Queue *q) {
    while (q->first != NULL)
        pop_q(q);
}

Graph read_graph(const char *filename) {
    Graph g;

    FILE *f_g = fopen(filename, "r");
    if (f_g == NULL) {
        printf("\nUnable to open file. read_graph\n");
        g.num_verts = 0;
        return g;
    }


    fscanf(f_g, "%d\n", &g.num_verts);
    if (g.num_verts<2) {
        printf("\nNo matrix in file. read_graph\n");
        g.num_verts = 0;
        return g;
    }


    g.matrix = (int **) malloc(g.num_verts * sizeof(int *));
    if (g.matrix == NULL) {
        printf("\nMemory allocation error. init_graph_tests, main massive\n");
        g.num_verts = 0;
        fclose(f_g);
        return g;
    }
    for (int i = 0; i < g.num_verts; i++) {
        char c;
        int tmp;
        g.matrix[i] = (int *) malloc(g.num_verts * sizeof(int));
        if (g.matrix[i] == NULL) {
            printf("\nMemory allocation error. init_graph_tests, submassive\n");
            g.num_verts = 0;
            fclose(f_g);
            return g;
        }
        for (int j = 0; j < i + 1; j++) {
            fscanf(f_g, "%d", &tmp);

            if (!(tmp == 0 || tmp == 1)) {
                printf("\nAlgorithm works with unoriented graph only, oriented in file. init_graph_tests, submassive\n");
                g.num_verts = 0;
                fclose(f_g);
                return g;
            }

            g.matrix[i][j] = tmp;
        }

        while ((c = fgetc(f_g)) != '\n');
    }

    fclose(f_g);
    return g;
}


void free_graph(Graph *g) {
    for (int i = 0; i < g->num_verts; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    g->num_verts = 0;
}

int pathfinder(Graph *g, int start, int end) {
    if (g->num_verts < 2) {
        printf("\n No matrix. pathfinder\n");
        return -1;
    }
    if (start < 0 || start >= g->num_verts || end < 0 || end >= g->num_verts) {
        printf("\nOut of bounds. pathfinder\n");
        return -1;
    }

    Queue q;
    init_queue(&q);

    int *dist = (int *) malloc(g->num_verts * sizeof(int));
    if (dist==NULL) {
        printf("Mtmory allocation error. pathfinder");
        return -1;
    }
    for (int i = 0; i < g->num_verts; i++) {
        dist[i] = -1;
    }

    dist[start] = 0;
    push_q(&q, start);

    while (q.first != NULL) {
        int cur = pop_q(&q);

        if (cur == end) {
            break;
        }

        for (int vert = 0; vert < g->num_verts; vert++) {
            if (cur > vert) {
                if (g->matrix[cur][vert] == 1 && dist[vert] == -1) {
                    dist[vert] = dist[cur] + 1;
                    push_q(&q, vert);
                }
            } else if (g->matrix[vert][cur] == 1 && dist[vert] == -1) {
                dist[vert] = dist[cur] + 1;
                push_q(&q, vert);
            }
        }
    }

    int len = dist[end];

    free(dist);
    free_queue(&q);
    return len;
}

