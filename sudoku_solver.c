#define _CRT_SECURE_NO_WARNINGS
#include "sudoku_solver.h"

RowMapper mapper;

// Инициализация маппера
void initMapper(int maxRows) {
    mapper.rowMap = (int*)malloc(maxRows * sizeof(int));
    mapper.colMap = (int*)malloc(maxRows * sizeof(int));
    mapper.valMap = (int*)malloc(maxRows * sizeof(int));
    mapper.total = 0;
}

void cleanupMapper() {
    free(mapper.rowMap);
    free(mapper.colMap);
    free(mapper.valMap);
}

void setupSolver(DLXSolver* s, int colNum, int gridDim, int subDim) {
    s->hdr.L = s->hdr.R = s->hdr.U = s->hdr.D = &s->hdr;
    s->cols = colNum;
    s->rows = s->ansCnt = 0;
    s->gridDim = gridDim;
    s->subDim = subDim;

    s->colArr = (DLXNode**)malloc(sizeof(DLXNode*) * colNum);
    s->rowArr = (DLXNode**)malloc(sizeof(DLXNode*) * (gridDim * gridDim * gridDim));
    s->colHdrs = (DLXNode**)malloc(sizeof(DLXNode*) * colNum);
    s->ans = (int*)malloc(sizeof(int) * gridDim * gridDim);

    for (int idx = 0; idx < colNum; idx++) {
        DLXNode* colNode = (DLXNode*)malloc(sizeof(DLXNode));
        colNode->L = &s->hdr;
        colNode->R = s->hdr.R;
        s->hdr.R->L = colNode;
        s->hdr.R = colNode;
        colNode->U = colNode->D = colNode->C = colNode;
        colNode->rowIdx = -1;
        colNode->cnt = 0;
        s->colHdrs[idx] = colNode;
    }
}

static void insertRow(DLXSolver* s, int* colIndices, int colCnt, int r, int c, int val) {
    DLXNode* first = NULL, * prev = NULL;
    for (int i = 0; i < colCnt; i++) {
        DLXNode* colHdr = s->colHdrs[colIndices[i]];
        DLXNode* newNode = (DLXNode*)malloc(sizeof(DLXNode));
        newNode->C = colHdr;
        newNode->rowIdx = mapper.total;
        newNode->U = colHdr->U;
        newNode->D = colHdr;
        colHdr->U->D = newNode;
        colHdr->U = newNode;
        colHdr->cnt++;

        if (!first)
            first = newNode->L = newNode->R = newNode;
        else {
            newNode->L = prev;
            newNode->R = first;
            prev->R = newNode;
            first->L = newNode;
        }
        prev = newNode;
    }
    if (first) {
        mapper.rowMap[mapper.total] = r;
        mapper.colMap[mapper.total] = c;
        mapper.valMap[mapper.total] = val;
        s->rowArr[s->rows++] = first;
        mapper.total++;
    }
}

static void hideCol(DLXNode* col) {
    col->R->L = col->L;
    col->L->R = col->R;
    for (DLXNode* rowItem = col->D; rowItem != col; rowItem = rowItem->D)
        for (DLXNode* cell = rowItem->R; cell != rowItem; cell = cell->R) {
            cell->D->U = cell->U;
            cell->U->D = cell->D;
            cell->C->cnt--;
        }
}

static void showCol(DLXNode* col) {
    for (DLXNode* rowItem = col->U; rowItem != col; rowItem = rowItem->U)
        for (DLXNode* cell = rowItem->L; cell != rowItem; cell = cell->L) {
            cell->C->cnt++;
            cell->D->U = cell;
            cell->U->D = cell;
        }
    col->R->L = col;
    col->L->R = col;
}

int backtrack(DLXSolver* s, int level) {
    if (s->hdr.R == &s->hdr) {
        s->ansCnt = level;
        return 1;
    }

    DLXNode* bestCol = s->hdr.R;
    for (DLXNode* j = bestCol->R; j != &s->hdr; j = j->R)
        if (j->cnt < bestCol->cnt)
            bestCol = j;

    if (bestCol->cnt == 0)
        return 0;

    hideCol(bestCol);
    for (DLXNode* row = bestCol->D; row != bestCol; row = row->D) {
        s->ans[level] = row->rowIdx;
        for (DLXNode* cell = row->R; cell != row; cell = cell->R)
            hideCol(cell->C);
        if (backtrack(s, level + 1))
            return 1;
        for (DLXNode* cell = row->L; cell != row; cell = cell->L)
            showCol(cell->C);
    }
    showCol(bestCol);
    return 0;
}

static void puzzleToMatrix(DLXSolver* s, Puzzle* p) {
    int constraints[4], n = p->dim, b = p->sub;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p->data[i][j]) {
                int num = p->data[i][j] - 1;
                constraints[0] = i * n + j;
                constraints[1] = n * n + i * n + num;
                constraints[2] = 2 * n * n + j * n + num;
                constraints[3] = 3 * n * n + ((i / b) * b + (j / b)) * n + num;
                insertRow(s, constraints, 4, i, j, num);
            }
            else {
                for (int num = 0; num < n; num++) {
                    constraints[0] = i * n + j;
                    constraints[1] = n * n + i * n + num;
                    constraints[2] = 2 * n * n + j * n + num;
                    constraints[3] = 3 * n * n + ((i / b) * b + (j / b)) * n + num;
                    insertRow(s, constraints, 4, i, j, num);
                }
            }
        }
    }
}

static void applyAnswer(DLXSolver* s, Puzzle* p) {
    for (int idx = 0; idx < s->ansCnt; idx++) {
        int rowId = s->ans[idx];
        p->data[mapper.rowMap[rowId]][mapper.colMap[rowId]] = mapper.valMap[rowId] + 1;
    }
}

void loadPuzzle(const char* fname, Puzzle* p) {
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file: %s\n", fname);
        exit(1);
    }
    fscanf(fp, "%d", &p->order);
    p->dim = p->order * p->order;
    p->sub = p->order;
    p->data = (int**)malloc(sizeof(int*) * p->dim);
    for (int i = 0; i < p->dim; i++) {
        p->data[i] = (int*)malloc(sizeof(int) * p->dim);
        for (int j = 0; j < p->dim; j++)
            fscanf(fp, "%d", &p->data[i][j]);
    }
    fclose(fp);
}

void storePuzzle(const char* fname, Puzzle* p) {
    FILE* fp = fopen(fname, "w");
    if (!fp) {
        fprintf(stderr, "Cannot create file: %s\n", fname);
        exit(1);
    }
    fprintf(fp, "%d\n", p->order);
    for (int i = 0; i < p->dim; i++) {
        for (int j = 0; j < p->dim; j++)
            fprintf(fp, "%d ", p->data[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void cleanupSolver(DLXSolver* s) {
    if (!s) return;
    for (int i = 0; i < s->rows; i++) {
        if (s->rowArr[i]) {
            DLXNode* node = s->rowArr[i];
            DLXNode* curr = node->R;
            while (curr != node) {
                DLXNode* tmp = curr;
                curr = curr->R;
                free(tmp);
            }
            free(node);
        }
    }
    for (int i = 0; i < s->cols; i++) {
        if (s->colHdrs[i])
            free(s->colHdrs[i]);
    }
    free(s->colArr);
    free(s->rowArr);
    free(s->colHdrs);
    free(s->ans);
}

void cleanupPuzzle(Puzzle* p) {
    if (!p) return;
    for (int i = 0; i < p->dim; i++) {
        free(p->data[i]);
    }
    free(p->data);
}

bool solveSudoku(Puzzle* puzzle) {
    int columns = 4 * puzzle->dim * puzzle->dim;
    int maxRows = puzzle->dim * puzzle->dim * puzzle->dim;

    initMapper(maxRows);

    DLXSolver solver;
    setupSolver(&solver, columns, puzzle->dim, puzzle->sub);

    puzzleToMatrix(&solver, puzzle);

    int result = backtrack(&solver, 0);

    if (result) {
        applyAnswer(&solver, puzzle);
    }

    cleanupSolver(&solver);
    cleanupMapper();

    return result == 1;
}

int validateSudoku(Puzzle* p) {
    int n = p->dim;
    // Проверка строк
    for (int i = 0; i < n; i++) {
        int check[10] = { 0 };
        for (int j = 0; j < n; j++) {
            int val = p->data[i][j];
            if (val < 1 || val > n) return 0;
            if (check[val]++) return 0;
        }
    }

    // Проверка столбцов
    for (int j = 0; j < n; j++) {
        int check[10] = { 0 };
        for (int i = 0; i < n; i++) {
            int val = p->data[i][j];
            if (check[val]++) return 0;
        }
    }

    // Проверка подквадратов
    int sub = p->sub;
    for (int bi = 0; bi < sub; bi++) {
        for (int bj = 0; bj < sub; bj++) {
            int check[10] = { 0 };
            for (int i = 0; i < sub; i++) {
                for (int j = 0; j < sub; j++) {
                    int val = p->data[bi * sub + i][bj * sub + j];
                    if (check[val]++) return 0;
                }
            }
        }
    }

    return 1;
}

void printSudoku(Puzzle* p) {
    printf("Order: %d\n", p->order);
    for (int i = 0; i < p->dim; i++) {
        for (int j = 0; j < p->dim; j++) {
            printf("%2d ", p->data[i][j]);
        }
        printf("\n");
    }
}