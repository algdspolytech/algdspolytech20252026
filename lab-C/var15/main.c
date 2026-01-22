#include "main.h"
#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

char words[MAX_V][MAX_LEN];
int wordCount = 0;

int adj[MAX_V][MAX_V];
int inDegree[MAX_V];
int used[MAX_V];

int findIndex(const char *s) {
  for (int i = 0; i < wordCount; i++) {
    if (strcmp(words[i], s) == 0)
      return i;
  }
  return -1;
}

int stableTopoSort(int result[]) {
  int resCount = 0;

  for (int step = 0; step < wordCount; step++) {
    int found = -1;

    for (int i = 0; i < wordCount; i++) {
      if (!used[i] && inDegree[i] == 0) {
        found = i;
        break;
      }
    }

    if (found == -1)
      return 0;

    used[found] = 1;
    result[resCount++] = found;

    for (int i = 0; i < wordCount; i++) {
      if (adj[found][i])
        inDegree[i]--;
    }
  }

  return 1;
}

int main() {
  FILE *fin = fopen("input.txt", "r");
  FILE *fout = fopen("output.txt", "w");

  if (!fin || !fout)
    return 1;

  char line[1000];
  fgets(line, sizeof(line), fin);

  char *tok = strtok(line, " \n");
  while (tok) {
    strcpy(words[wordCount++], tok);
    tok = strtok(NULL, " \n");
  }

  char a[MAX_LEN], b[MAX_LEN];
  while (fscanf(fin, "%s %s", a, b) == 2) {
    int u = findIndex(a);
    int v = findIndex(b);
    if (u != -1 && v != -1 && !adj[u][v]) {
      adj[u][v] = 1;
      inDegree[v]++;
    }
  }

  int result[MAX_V];
  if (!stableTopoSort(result)) {
    fprintf(fout, "[Error]");
  } else {
    for (int i = 0; i < wordCount; i++) {
      fprintf(fout, "%s", words[result[i]]);
      if (i + 1 < wordCount)
        fprintf(fout, " ");
    }
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
