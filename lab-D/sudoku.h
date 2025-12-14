#ifndef SUDOKUH
#define SUDOKUH

#define MAXN 9
#define MAXROW MAXN * MAXN * MAXN
#define MAXCOL 4 * MAXN * MAXN

typedef struct Node {
    struct Node* left, * right, * up, * down;
    struct Node* colHeader;
    int rowID, colID, count;
} Node;

typedef struct {
    int N;
    int size;
    int grid[MAXN][MAXN];
    Node header;
    Node nodes[MAXROW * 4 + MAXCOL];
    int nodeCount;
    int solution[MAXROW];
    int solSize;
} SudokuDLX;

// Инициализация структуры Судоку
void initSudoku(SudokuDLX* s, int N);

// Построение матрицы точного покрытия
void buildExactCover(SudokuDLX* s);

// Поиск решения (Algorithm X)
int solveSudoku(SudokuDLX* s);

// Заполнение сетки из найденного решения
void fillSolution(SudokuDLX* s);

#endif
