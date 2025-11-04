#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Найти кратчайший путь (по числу ребер) в графе, заданном матрицей смежности.
// matrix - одномерный массив размера n*n, matrix[i*n + j] = 0/1
// s,t - вершины (0-based)
// directed - 0 если неориентированный, 1 если ориентированный (влияет на интерпретацию матрицы)
// out_len - указатель, куда записывается длина пути (число ребер), -1 если нет пути
// Возвращает динамический массив вершин (int[]), который нужно free(). Если пути нет возвращается NULL.
int* shortest_path_bfs(const int *matrix, int n, int s, int t, int directed, int *out_len) {
    if (n <= 0 || !matrix || s < 0 || s >= n || t < 0 || t >= n) {
        if (out_len) *out_len = -1;
        return NULL;
    }
    int *queue = malloc(n * sizeof(int));
    int *prev = malloc(n * sizeof(int));
    int *vis = calloc(n, sizeof(int));
    if (!queue || !prev || !vis) { free(queue); free(prev); free(vis); if (out_len) *out_len = -1; return NULL; }

    for (int i=0;i<n;i++) prev[i] = -1;
    int qh=0, qt=0;
    queue[qt++] = s; vis[s]=1;

    while (qh < qt) {
        int v = queue[qh++];
        if (v == t) break;
        for (int u = 0; u < n; ++u) {
            int edge = matrix[v*n + u];
            if (!directed) {
                // treat matrix symmetric; interpret any nonzero in either direction as edge
                // but when matrix provided, usually both entries are set; we respect given matrix entry from v->u
            }
            if (edge && !vis[u]) {
                vis[u]=1; prev[u]=v; queue[qt++]=u;
            }
        }
    }
    if (!vis[t]) {
        free(queue); free(prev); free(vis);
        if (out_len) *out_len = -1;
        return NULL;
    }
    // reconstruct path
    int len = 0;
    int cur = t;
    while (cur != -1) { len++; cur = prev[cur]; }
    int *path = malloc(len * sizeof(int));
    cur = t;
    for (int i = len-1; i>=0; --i) { path[i] = cur; cur = prev[cur]; }
    if (out_len) *out_len = len-1; // number of edges is vertices-1
    free(queue); free(prev); free(vis);
    return path;
}

// Утилита - чтение из файла и вывод результата
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    const char *fn = argv[1];
    FILE *f = fopen(fn, "r"); if (!f) { perror("fopen"); return 1; }
    int n;
    if (fscanf(f, "%d", &n) != 1) { fprintf(stderr, "bad file\n"); fclose(f); return 1; }
    int *mat = malloc(n * n * sizeof(int));
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) {
        int x=0; if (fscanf(f, "%d", &x) != 1) x=0; mat[i*n + j] = x?1:0;
    }
    int s=-1,t=-1; if (fscanf(f, "%d %d", &s, &t) != 2) { fprintf(stderr, "need s t\n"); free(mat); fclose(f); return 1; }
    int directed = 0; // default undirected
    int dval;
    if (fscanf(f, "%d", &dval) == 1) directed = dval?1:0;
    fclose(f);
    int out_len= -1;
    int *path = shortest_path_bfs(mat, n, s, t, directed, &out_len);
    if (path == NULL) {
        printf("No path between %d and %d\n", s, t);
        printf("Length: -1\n");
        free(mat);
        return 0;
    }
    printf("Length: %d\n", out_len);
    printf("Path:"); for (int i=0;i<out_len+1;i++) printf(" %d", path[i]); printf("\n");
    free(path); free(mat);
    return 0;
}
