#include "graph_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF HUGE_VAL

#define STRA_LENGTH 256
#define NUM_LENGTH 64
#define NODE_ORDER 10

graph_t *read_graph(const char *filename) {

  graph_t *ans = (graph_t *)malloc(sizeof(graph_t));

  int m = 0, n = 0;

  FILE *F = fopen(filename, "r");
  if (!F) {
    free(ans);
    return NULL;
  }

  char buffer[STRA_LENGTH], current[NUM_LENGTH];
  fgets(buffer, STRA_LENGTH, F);
  n = strtol(buffer, NULL, NODE_ORDER);

  double **adjacency = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; i++) {
    adjacency[i] = (double *)malloc(sizeof(double) * n);
  }
  ans->adjacency = adjacency;

  char *thisItem;
  for (int i = 0; i < n; i++) {
    fgets(buffer, STRA_LENGTH, F);
    thisItem = strtok(buffer, " ");
    ans->adjacency[i][0] = strtod(thisItem, NULL);
    for (int j = 1; j < n; j++) {
      thisItem = strtok(NULL, " ");
      ans->adjacency[i][j] = strtod(thisItem, NULL);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (adjacency[i][j] != INF) {
        m++;
      }
    }
  }

  ans->n = n;
  ans->m = m;
  fclose(F);
  return ans;
}

path_t *make_path(int n, int s) {
  path_t *ans = (path_t *)malloc(sizeof(path_t));
  double *d = (double *)malloc(sizeof(double) * n);
  double *pi = (double *)malloc(sizeof(double) * n);
  for (int i = 0; i < n; i++) {
    d[i] = INF;
    pi[i] = NAN;
  }
  d[s - 1] = 0;
  ans->d = d;
  ans->pi = pi;
  return ans;
}

void free_path(path_t *path) {
  free(path->d);
  free(path->pi);
  free(path);
}

void free_graph(graph_t *graph) {
  int n = graph->n;
  for (int i = 0; i < n; i++) {
    free(graph->adjacency[i]);
  }
  free(graph->adjacency);
  free(graph);
}

void print_graph(graph_t *graph) {
  int n = graph->n;
  printf("Number of nodes: %i || Number of edges: %i\n[\n", n, graph->m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.2f ", graph->adjacency[i][j]);
    }
    printf("\n");
  }
  printf("]\n");
}

void relax(graph_t *graph, int u, int v, double *d, double *pi) {
  if (!(u < graph->n && v < graph->n)) {
    return;
  }
  if (d[v] > d[u] + graph->adjacency[u][v]) {
    d[v] = d[u] + graph->adjacency[u][v];
    pi[v] = u;
  }
}

bool bellman_ford(graph_t *graph, path_t *path, int s, int e) {
  int n = graph->n, m = graph->m;
  double *pi = path->pi, *d = path->d;

  for (int c = 0; c < n - 1; c++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        relax(graph, i, j, d, pi);
      }
    }
  }

  for (int v = 0; v < n; v++) {
    for (int u = 0; u < n; u++) {
      if (d[v] > d[u] + graph->adjacency[u][v]) {
        return false;
      }
    }
  }
  return true;
}

double nodes_distance(int s, int e, const char *filename) {
  graph_t *graph = read_graph(filename);
  if (!graph) {
    free(graph);
    return NAN;
  }
  printf("------------------------------------------------\n");
  printf("Your graph is: \n");
  print_graph(graph);

  path_t *path = make_path(graph->n, s);

  double ans;
  if (bellman_ford(graph, path, s, e)) {
    ans = path->d[e - 1];
  } else {
    ans = -INF;
  }
  printf("The distance between node %i and node %i is: %.5f\n", s, e, ans);
  printf("------------------------------------------------\n");
  free_path(path);
  free_graph(graph);
  return ans;
}
