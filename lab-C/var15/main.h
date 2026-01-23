#ifndef MAIN_H
#define MAIN_H

#define MAX_V 100
#define MAX_LEN 50

extern char words[MAX_V][MAX_LEN];
extern int wordCount;

extern int adj[MAX_V][MAX_V];
extern int inDegree[MAX_V];
extern int used[MAX_V];

int findIndex(const char *s);

int stableTopoSort(int result[]);

#endif
