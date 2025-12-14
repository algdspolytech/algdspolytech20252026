#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N_VERT 1000
#define N_EDGE (N_VERT * N_VERT / 2)

int N, K;
int edge_u[N_EDGE], edge_v[N_EDGE];
int M = 0; 

int covered[N_EDGE]; 
int cover_count = 0;
int solution[N_VERT];
int sol_size = 0;
int found = 0;

void update_edge(int idx, int delta) {
    int old_val = covered[idx];
    covered[idx] += delta;
    
    if (old_val > 0 && covered[idx] == 0) {
        cover_count--;
    }

    else if (old_val == 0 && covered[idx] > 0) {
        cover_count++;
    }
}

void cover_vertex(int v, int delta) {
    for (int i = 0; i < M; i++) {
        if (edge_u[i] == v || edge_v[i] == v) {
            update_edge(i, delta);
        }
    }
}

void solve() {
    if (found) return;

    if (cover_count == M) {
        found = 1;
        return;
    }

    if (sol_size == K) return;

    int u = -1, v = -1;
    for (int i = 0; i < M; i++) {
        if (covered[i] == 0) {
            u = edge_u[i];
            v = edge_v[i];
            break;
        }
    }

    if (u == -1) return;

    solution[sol_size++] = u;
    cover_vertex(u, 1);
    solve();
    if (found) return;

    cover_vertex(u, -1);
    sol_size--;

    solution[sol_size++] = v;
    cover_vertex(v, 1);
    solve();
    if (found) return;

    cover_vertex(v, -1);
    sol_size--;
}

int run_solver(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    fscanf(in, "%d %d", &N, &K);

    int c;
    while ((c = fgetc(in)) != '\n' && !feof(in));

    M = 0;
    for (int i = 1; i <= N; i++) {
        int v;

        while (1) {
            int next_char = fgetc(in);
            if (next_char == '\n' || next_char == EOF) break;
            ungetc(next_char, in);
            fscanf(in, "%d", &v);

            if (v > i) {
                edge_u[M] = i;
                edge_v[M] = v;
                M++;
            }
        }
    }
    fclose(in);

    cover_count = 0;
    sol_size = 0;
    found = 0;
    memset(covered, 0, sizeof(covered));
    memset(solution, 0, sizeof(solution));
    solve();

    FILE* out = fopen(output_file, "w");
    if (!found) {
        fprintf(out, "0\n");
    }
    else {
        for (int i = 0; i < sol_size; i++) {
            if (i > 0) fprintf(out, " ");
            fprintf(out, "%d", solution[i]);
        }
        fprintf(out, "\n");
    }
    fclose(out);
    return found;
}

