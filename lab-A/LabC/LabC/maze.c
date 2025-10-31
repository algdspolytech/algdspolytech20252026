#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define n 10

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point elems[n*n];
    int start;
    int end;
    int filled;
} queue;

void create_queue(queue* q) { 
    q->start = 0;
    q->end = 0;
    q->filled = 0;
}

void add_to_queue(queue* q, point p) {
    q->elems[q->end] = p;
    q->end++;
    q->filled++;
}

point get_from_queue(queue* q) {
    point p = q->elems[q->start];
    q->start++;
    q->filled--;
    return p;
}

point parent[n][n];

int bfs(char maze[n][n], point start, point end) {
    queue q;
    create_queue(&q);
    add_to_queue(&q, start);

    int visited[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }

    visited[start.x][start.y] = 1;//начало уже посетили
    parent[start.x][start.y].x = -1; //для начала лабиринта 
    parent[start.x][start.y].y = -1;

    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    while (q.filled > 0) {
        point now_p = get_from_queue(&q);

        if (now_p.x == end.x && now_p.y == end.y)
        {
            return 1;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = now_p.x + dx[dir];
            int ny = now_p.y + dy[dir];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && maze[nx][ny] != '#') {
                visited[nx][ny] = 1;//если точка не стена, отмечаем как посещенную
                parent[nx][ny] = now_p;//добавляем точку, из которой пришли в нынешнюю
                add_to_queue(&q, (point) { nx, ny });//добавляем в очередь новую точку
            }
        }
    }

    parent[0][0] = (point){ -2,-2 }; //если не нашли путь, заполнили мусором для проверки в get_path
    return 0;
}

int get_path(point start, point end, point* path) {
    if (parent[0][0].x == -2 && parent[0][0].y == -2) {
        return 0;
    }

    point temp_path[n * n];
    int k = 0;

    point now_p = end; //восстанавливаем путь с конца

    while (now_p.x != -1 || now_p.y != -1) { //пока не дойдём до старта 
        temp_path[k] = now_p;
        k++;
        now_p = parent[now_p.x][now_p.y];//двигаемся к точке, из которой пришли до этого
    }

    for (int i = 0; i < k; i++) {//разворачиваем массив 
        path[i] = temp_path[k - 1 - i]; 
    }
    return k - 1; 
}
