#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct matrixElement {
	int i;
	int j;
	int key;
} MatrixElementT;

typedef struct matrix{
	MatrixElementT element;
	struct matrix* next;
} MatrixT;

MatrixT* readFieldDeleted(int m, int n);
MatrixT* createCircutOfPoint(MatrixT* circut, MatrixElementT currentPoint, int m, int n);
MatrixT* createCircut(MatrixT* field, int m, int n);

MatrixT* deleteFigure(MatrixT* field, MatrixElementT current, int m, int n);

MatrixT* createMatrix(MatrixElementT element);
MatrixT* createUnitMatrix();

MatrixT* addFirstElement(MatrixT* matrix, MatrixElementT element);
MatrixT* addToMatrixByPointer(MatrixT* matrix, MatrixT* previousElement, MatrixElementT element);
MatrixT* addToMatrix(MatrixT* matrix, MatrixElementT element);

MatrixT* findElement(MatrixT* matrix, MatrixElementT element, int needPrevious);

MatrixT* deleteFirstElement(MatrixT* matrix);
MatrixT* deleteElementByPrevious(MatrixT* matrix, MatrixT* previous);
MatrixT* deleteElement(MatrixT* matrix, MatrixElementT element);
void freeMatrix(MatrixT* matrix);

int areEqualElem(MatrixElementT a, MatrixElementT b);
int areEqual(MatrixT* a, MatrixT* b);

char* errors[] = {
	"ErrorCode - 0: Not enought memory",
	"-------not a error-------",
	"ErrorCode - 2: There is not such an element"
};

void printError(int errorCode);