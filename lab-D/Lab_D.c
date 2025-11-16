#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#define MAX_V 1000

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lab_D.h"

void InGraph(GrphStrc* graph, int V) {
  graph->Grph = (int**)malloc((V + 1) * sizeof(int*));
  for (int i = 0; i <= V; i++) {
    graph->Grph[i] = (int*)malloc((V + 1) * sizeof(int));
  }

  graph->w = (int*)malloc((V + 1) * sizeof(int));
  graph->path = (int*)malloc((V + 1) * sizeof(int));

  graph->ptl = 0;
  graph->flag = 0;
}

void FreeGraph(GrphStrc* graph, int V) {
  for (int i = 0; i <= V; i++) {
    free(graph->Grph[i]);
  }
  free(graph->Grph);
  free(graph->w);
  free(graph->path);
}

int ReadLst(FILE* file, GrphStrc* strct, int* V, int* s, int* t, int* K) {
  if (!file) {
    return 0;
  }

  fscanf(file, "%d %d %d %d", V, s, t, K);

  InGraph(strct, *V);

  for (int i = 1; i <= *V; i++) {
    for (int j = 1; j <= *V; j++) {
      strct->Grph[i][j] = 0;
    }
    strct->w[i] = 0;
  }

  char list[1000];
  fgets(list, sizeof(list), file);

  for (int i = 1; i <= *V; i++) {
    if (fgets(list, sizeof(list), file) == NULL) {
      break;
    }

    char* strk = strtok(list, " \n");
    while (strk != NULL) {
      int nghbr = atoi(strk);
      if (nghbr >= 1 && nghbr <= *V) {
        strct->Grph[i][nghbr] = 1;
        strct->Grph[nghbr][i] = 1;
      }
      strk = strtok(NULL, " \n");
    }
  }
}

int DeepSearc(GrphStrc* strct, int s, int len, int V, int t, int K) {
  if (strct->flag) {
    return 0;
  }

  strct->path[len] = s;

  if (s == t && len >= K) {
    strct->flag = 1;
    strct->ptl = len + 1;
    return 0;
  }

  strct->w[s] = 1;

  for (int i = 1; i <= V; i++) {
    if ((strct->Grph[s][i] == 1) && !(strct->w[i])) {
      DeepSearc(strct, i, len + 1, V, t, K);
      if (strct->flag) {
        return 0;
      }
    }
  }

  strct->w[s] = 0;
}

int Write(FILE* file, GrphStrc* strct) {
  if (!file) {
    return 0;
  }

  if (strct->flag == 1) {
    for (int i = 0; i < strct->ptl; i++) {
      fprintf(file, "%d", strct->path[i]);
      if (i < strct->ptl - 1) {
        fprintf(file, " ");
      }
    }
  } else {
    fprintf(file, "0");
  }
}

int main() {
  setlocale(LC_CTYPE, "Russian");
  FILE* filer = fopen("labDR.txt", "r");
  FILE* filew = fopen("labDW.txt", "w");

  if (!filer || !filew) {
    return 1;
  }

  GrphStrc strct;
  int V = 0, s = 0, t = 0, K = 0;

  ReadLst(filer, &strct, &V, &s, &t, &K);

  if (V < 1 || V > MAX_V || s < 1 || s > V || t < 1 || t > V || K < 0) {
    fprintf(filew, "0");
    fclose(filew);
    return 1;
  }

  DeepSearc(&strct, s, 0, V, t, K);

  Write(filew, &strct);

  FreeGraph(&strct, V);
  fclose(filer);
  fclose(filew);
  return 0;
}
