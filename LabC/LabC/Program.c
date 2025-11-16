#pragma warning(disable:4996)

#include "Program.h"

#ifdef  __cplusplus
void mainOrig(char args[]) {
#else
void main(char args[]) {
#endif	
	printf("Enter size of squared field (M x N):\nM: ");
	int m, n;
	scanf("%i", &m);
	printf("N: ");
	scanf("%i", &n);
	
	MatrixT* fieldDeleted = readFieldDeleted(m, n);
	MatrixT* circut = createCircut(fieldDeleted, m, n);

	int figureCount = 0;
	while (circut) {
		circut = deleteFigure(circut, circut->element, m, n);
		figureCount++;
	}
	printf("\nFigures in the field: %i\n", figureCount);
}

MatrixT* readFieldDeleted(int m, int n)
{
	MatrixT* fieldDeleted = NULL;
	printf("\nEnter amount of deleted points: ");
	int k;
	while (scanf("%i", &k) && k > n * m) {
		printf("Amount can't be greater than field size: %i\n", m * n);
		printf("Reenter amount: ");
	}
	for (int i = 0; i < k; i++) {
		int x, y;
		printf("Enter point no %i (x, y): ", i + 1);
		while (scanf("%i %i", &x, &y) && (x < 0 || x >= m || y < 0 || y >= n)) {
			printf("Point must be in {[0, 0] x (%i, %i)}\n", m, n);
			printf("Reenter point: ");
		}
		MatrixElementT current = { x, y, 0 };
		fieldDeleted = addToMatrix(fieldDeleted, current);
	}
	return fieldDeleted;
}

MatrixT* createCircutOfPoint(MatrixT* circut, MatrixElementT currentPoint, int m, int n) {
	for (int j = currentPoint.j - 1; j <= currentPoint.j + 1; j++) {
		if (j < 0 || j >= n)
			continue;

		for (int i = currentPoint.i - 1; i <= currentPoint.i + 1; i++) {
			if (i == currentPoint.i && j == currentPoint.j)
				continue;
			if (i < 0 || i >= m)
				continue;

			MatrixElementT newElement = { i, j, 1 };
			circut = addToMatrix(circut, newElement);
		}
	}

	return circut;
}

MatrixT* createCircut(MatrixT* field, int m, int n) {
	MatrixT* current = field;
	MatrixT* circut = NULL;

	while(current){
		circut = createCircutOfPoint(circut, current->element, m, n);
		current = current->next;
	}
	current = field;
	while (current) {
		circut = deleteElement(circut, current->element);
		current = current->next;
	}

	return circut;
}

MatrixT* deleteFigure(MatrixT* field, MatrixElementT current, int m, int n) {
	field = deleteElement(field, current);
	
	MatrixElementT up = {current.i + 1, current.j, 1};
	MatrixElementT down = {current.i - 1, current.j, 1};
	MatrixElementT left = {current.i, current.j - 1, 1};
	MatrixElementT right = {current.i, current.j + 1, 1};
	MatrixElementT directions[] = {up, down, left, right};

	for (int i = 0; i < 4; i++) {
		MatrixElementT temp = directions[i];
		if (temp.i < 0 || temp.j < 0 || temp.i >= m || temp.j >= n)
			continue;
		if (findElement(field, temp, 0))
			field = deleteFigure(field, temp, m, n);
	}

	return field;
}

MatrixT* createMatrix(MatrixElementT element) {
	MatrixT* result = (MatrixT*)malloc(sizeof(MatrixT));
	if (!result)
		printError(0);

	result->element = element;
	result->next = NULL;

	return result;
}

MatrixT* createUnitMatrix() {	
	MatrixElementT unit = { 0, 0, 1 };
	return createMatrix(unit);
}

MatrixT* addFirstElement(MatrixT* matrix, MatrixElementT element) {
	MatrixElementT secondElement = matrix->element;
	matrix->element = element;

	return addToMatrixByPointer(matrix, matrix, secondElement);
}

MatrixT* addToMatrixByPointer(MatrixT* matrix, MatrixT* previousElement, MatrixElementT element) {
	if (!previousElement)
		return addFirstElement(matrix, element);


	MatrixT* newElement = (MatrixT*)malloc(sizeof(MatrixT));
	if (!newElement)
		printError(0);
	newElement->element = element;

	MatrixT* nextElement = previousElement->next;
	previousElement->next = newElement;
	newElement->next = nextElement;
	
	return matrix;
}

MatrixT* addToMatrix(MatrixT* matrix, MatrixElementT element) {
	if (!matrix)
		return(createMatrix(element));

	MatrixT* previous = NULL;
	MatrixT* current = matrix;
	while (current && current->element.j < element.j) {
		previous = current;
		current = current->next;
	}
	if (current && current->element.j == element.j) {
		while (current && current->element.j == element.j && current->element.i < element.i ) {
			previous = current;
			current = current->next;
		}
		if (current && current->element.i == element.i) {
			current->element.key = element.key;
			return matrix;
		}
	}
	
	return addToMatrixByPointer(matrix, previous, element);
}

MatrixT* findElement(MatrixT* matrix, MatrixElementT element, int needPrevious) {
	MatrixT* previous = NULL;
	MatrixT* current = matrix;
	while (current && current->element.j < element.j) {
		previous = current;
		current = current->next;
	}
	if (current && current->element.j == element.j) {
		while (current && current->element.j == element.j && current->element.i < element.i) {
			previous = current;
			current = current->next;
		}
		if (current && current->element.i == element.i)
		{
			if (needPrevious)
				return previous;
			else
				return current;
		}
	}
	if (needPrevious)
		printError(2);
	else
		return NULL;
}

MatrixT* deleteFirstElement(MatrixT* matrix) {
	if (!matrix)
		return matrix;
	if (!matrix->next)
		return NULL;

	MatrixElementT temporal = matrix->element;
	matrix->element = matrix->next->element;
	matrix->next->element = temporal;
	
	return deleteElementByPrevious(matrix, matrix);
}

MatrixT* deleteElementByPrevious(MatrixT* matrix, MatrixT* previous) {
	if(!previous)
		return deleteFirstElement(matrix);
	if (!previous->next)
		return matrix;

	MatrixT* current = previous->next;
	previous->next = previous->next->next;
	free(current);

	return matrix;
}

MatrixT* deleteElement(MatrixT* matrix, MatrixElementT element)
{
	MatrixT* current = findElement(matrix, element, 0);
	if (!current)
		return matrix;

	MatrixT* previous = findElement(matrix, element, 1);
	return deleteElementByPrevious(matrix, previous);
}

void freeMatrix(MatrixT* matrix)
{
	if (matrix->next) {
		freeMatrix(matrix->next);
		matrix->next = NULL;
	}
	free(matrix);
}

int areEqualElem(MatrixElementT a, MatrixElementT b) {
	int result = 
		a.i == b.i &&
		a.j == b.j &&
		a.key == b.key;
	return result;
}

int areEqual(MatrixT* a, MatrixT* b) {

	int result = 1;
	MatrixT* currentA = a;
	MatrixT* currentB = b;
	while (result && currentA && currentB) {
		if (!areEqualElem(currentA->element, currentB->element))
			result = 0;
		currentA = currentA->next;
		currentB = currentB->next;
	}

	if (!a && !b)
		return 1;
	else if (!a || !b)
		return 0;
	return result;
}

void printError(int errorCode) {
	printf("***\n%s\n***", errors[errorCode]);
	exit(errorCode);
}
