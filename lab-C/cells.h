#ifndef CELLS
#define CELLS

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int** grid;
    int M;
    int N;
} Grid;

Grid* CreateGrid(int M, int N);
void FreeGrid(Grid* pg);
void RemoveCell(Grid* pg, int x, int y);
int ConnectComponents(Grid* pg);
Grid* LoadFile(const char* filename);
Grid* LoadStdin();

#ifdef __cplusplus
}
#endif

#endif
