#pragma once

#define n 10
typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point elems[n * n];
    int start;
    int end;
    int filled;
} queue;


#ifdef __cplusplus
extern "C" {
#endif

    void create_queue(queue* q);
    void add_to_queue(queue* q, point p);
    point get_from_queue(queue* q);
    int read_maze(const char filename[], char maze[n][n], point* start, point* end);
    int bfs(char maze[n][n], point start, point end);
    int get_path(point start, point end, point* shortest_path); 

    extern point parent[n][n];
#ifdef __cplusplus
}
#endif
