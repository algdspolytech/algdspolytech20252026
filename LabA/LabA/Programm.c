#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "Programm.h"

//the code is running from .cpp file (testing file)
#ifdef __cplusplus
void mainOrig(){

//the code is running from .c file (original file)
#else
void main() {
#endif
	char* test = getString("input.txt");
	int i = 0;
	PolynomialT* poly1 = parsePoly(test, &i);
	i++;
	PolynomialT* poly2 = parsePoly(test, &i);
	free(test);
	PolynomialT* sum = sumPoly(poly1, poly2);
	PolynomialT* mul = multiplyByPoly(poly1, poly2);
	PolynomialT* dif = differiate(poly1);

	FILE* file = fopen("output.txt", "w");
	printPoly(sum, file);
	fprintf(file, "\n");
	printPoly(mul, file);
	fprintf(file, "\n");
	printPoly(dif, file);

	printf("\n");
	
	fclose(file);
	freePoly(poly1);
	freePoly(poly2);
}

int isZero(PolynomialT* poly) {
	int result = 1;

	PolynomialT* current = poly;
	while ((current != NULL) && result) {
		result = (current->monom.coeff == 0);
		current = current->nextMonom;
	}

	return result;
}

int areEqual(PolynomialT* polyA, PolynomialT* polyB)
{
	int result = 1;
	
	deleteZero(polyA);
	deleteZero(polyB);

	PolynomialT* currentA = polyA;
	PolynomialT* currentB = polyB;
	do {
		if (!currentA && !currentB)
			return 1;
		else if (!currentA || !currentB)
			return 0;
		
		result = currentA->monom.coeff == currentB->monom.coeff;
		currentA = currentA->nextMonom;
		currentB = currentB->nextMonom;
	} while (result);
}

PolynomialT* sumPoly(PolynomialT* a, PolynomialT* b)
{
	PolynomialT* result = createCopy(a);
	
	int isCleared = 0;
	PolynomialT* currentB = b;
	while (currentB) {
		if (!isCleared) {
			PolynomialT* currentA = findMono(result, currentB->monom.degree);
			if (currentA) {
				int newCoeff = currentA->monom.coeff + currentB->monom.coeff;

				if (newCoeff == 0)
					isCleared = !deleteMono(result, currentA->monom.degree);
				else
					currentA->monom.coeff = newCoeff;
			}
			else
				addMono(result, currentB->monom);
		}
		else {
			result = createPoly(currentB->monom);
			isCleared = 0;
		}
		currentB = currentB->nextMonom;
	}

	if (isCleared)
		return createZeroPoly();
	return result;
}

PolynomialT* multiplyByMono(PolynomialT* a, MonomialT b)
{
	if (b.coeff == 0) {
		return createZeroPoly();
	}
	else {
		PolynomialT* result = createCopy(a);

		PolynomialT* current = result;
		while (current) {
			current->monom.coeff *= b.coeff;
			current->monom.degree += (current->monom.coeff)? b.degree : 0;
			current = current->nextMonom;
		}

		return result;
	}
}

PolynomialT* multiplyByPoly(PolynomialT* a, PolynomialT* b)
{
	PolynomialT* result = multiplyByMono(a, b->monom);

	PolynomialT* currentB = b->nextMonom;
	while (currentB) {
		PolynomialT* currentTerm = multiplyByMono(a, currentB->monom);
		result = sumPoly(result, currentTerm);
		currentB = currentB->nextMonom;
	}

	return result;
}

PolynomialT* differiate(PolynomialT* a)
{
	PolynomialT* result = createCopy(a);
	if (result->monom.degree == 0) {
		int isConst = !deleteFirstMono(result);
		if (isConst) {
			MonomialT resultMono = { 0, 0 };
			return createPoly(resultMono);
		}
	}

	PolynomialT* current = result;
	while (current) {
		current->monom.coeff *= current->monom.degree;
		current->monom.degree--;

		current = current->nextMonom;
	}

	return result;
}

PolynomialT* createPoly(MonomialT mono)
{
	PolynomialT* newPoly = (PolynomialT*)malloc(sizeof(PolynomialT));
	if (!newPoly) {
		printf("Not enought memory");
		exit(0);
	}

	newPoly->monom = mono;
	newPoly->nextMonom = NULL;

	return newPoly;
}

PolynomialT* createZeroPoly()
{
	MonomialT zeroMonom = { 0, 1 };
	return createPoly(zeroMonom);
}

PolynomialT* createCopy(PolynomialT* original)
{
	PolynomialT* copy = createPoly(original->monom);
	
	PolynomialT* current = original->nextMonom;
	while (current) {
		addMono(copy, current->monom);
		current = current->nextMonom;
	}

	return copy;
}

PolynomialT* findPrevious(PolynomialT* poly, int degree)
{
	PolynomialT* result = NULL;
	
	PolynomialT* current = poly;
	while (current && current->monom.degree < degree) {
		result = current;
		current = current->nextMonom;
	}

	return result;
}

PolynomialT* findMono(PolynomialT* poly, int degree)
{
	PolynomialT* result = NULL;

	PolynomialT* current = poly;

	while (current) {
		if (current->monom.degree == degree)
			return current;
		else if (current->monom.degree > degree)
			return NULL;

		current = current->nextMonom;
	}

	return result;
}

int addMono(PolynomialT* poly, MonomialT mono)
{
	if (!poly) {
		printf("Error: NULL - pointer(func: addMono)");
		exit(0);
	}

	PolynomialT* simple = findMono(poly, mono.degree);
	if (simple) {
		int newCoeff = simple->monom.coeff + mono.coeff;
		
		if (newCoeff == 0)
			return deleteMono(poly, mono.degree);
		else
			simple->monom.coeff = newCoeff;

		return 1;
	}
	
	PolynomialT* previous = findPrevious(poly, mono.degree);
	if (previous)
		addMonoByPrevious(previous, mono);
	else
		addFirstMono(poly, mono);
	
	return 1;
}

void addMonoByPrevious(PolynomialT* previousElement, MonomialT monom)
{
	PolynomialT* newElement = (PolynomialT*)malloc(sizeof(PolynomialT));
	if (!newElement) {
		printf("Not enought memory");
		exit(0);
	}
	newElement->monom = monom;

	if (previousElement) {
		newElement->nextMonom = previousElement->nextMonom;
		previousElement->nextMonom = newElement;
	}
	else {
		printf("Error: NULL-pointer (func: addMonoByPrevious)");
	}
}

void addFirstMono(PolynomialT* poly, MonomialT monom)
{
	MonomialT temporal = poly->monom;
	poly->monom = monom;
	addMonoByPrevious(poly, temporal);
}

int deleteFirstMono(PolynomialT* poly)
{
	PolynomialT* next = poly->nextMonom;
	
	if (next) {
		MonomialT temporal = poly->monom;
		poly->monom = next->monom;
		next->monom = temporal;
		
		poly->nextMonom = next->nextMonom;
		free(next);
		return 1;
	}
	else {
		free(poly);
		return 0;
	}
}

int deleteMono(PolynomialT* poly, int degree)
{
	PolynomialT* element = findMono(poly, degree);
	
	if (element) {
		PolynomialT* prev = findPrevious(poly, degree);
		if (prev) {
			prev->nextMonom = element->nextMonom;
			free(element);
		}
		else
			return deleteFirstMono(poly);
	}
	else {
		printf("Error: there is no element with degree: %i (func: deleteMono)", degree);
	}

	return 1;
}

void deleteZero(PolynomialT* poly)
{
	if (isZero(poly)) {
		MonomialT zeroMono = { 0, 1 };
		addFirstMono(poly, zeroMono);
		freePoly(poly->nextMonom);
		poly->nextMonom = NULL;
	}
	else {
		PolynomialT* current = poly;
		while (current) {
			if (current->monom.coeff == 0)
				deleteMono(poly, current->monom.degree);
			current = current->nextMonom;
		}
	}
}

void freePoly(PolynomialT* poly)
{
	if (poly->nextMonom)
		freePoly(poly->nextMonom);

	free(poly);
}

MonomialT parseMono(char* str, int* start)
{
	int signCoeff = 1;
	int coeff = 0;
	int degree = 1;

	int i = *start;
	if (str[i] == '-')
		signCoeff *= -1;
	else if (str[i] != '+')
		i--;
	i++;
	coeff = parseNumber(str, &i);
	if (coeff == 0 && str[i] == 'x')
		coeff = 1;

	if (str[i] == '*')
		i++;
	
	if (str[i] == 'x' && str[i + 1] == '^') {
		i += 2;
		degree = parseNumber(str, &i);
	}
	else if (str[i] != 'x')
		degree = 0;
	else {
		degree = 1;
		i++;
	}

	*start = i;
	MonomialT result = { coeff * signCoeff, degree };
	return result;
}

PolynomialT* parsePoly(char* str, int* start)
{
	int i = *start;
	PolynomialT* result = NULL;
	int needNewMemory = 1;
	
	while (str[i]!='\n' && str[i] != '\0') {
		MonomialT current = parseMono(str, &i);
		
		if (needNewMemory) {
			result = createPoly(current);
			needNewMemory = 0;
		}
		else
			needNewMemory = !addMono(result, current);
	}

	*start = i;
	if (needNewMemory || isZero(result))
		return createZeroPoly();
	return result;
}

int parseNumber(char* str, int* start)
{
	int i = *start;
	int result = 0;
	while (str[i] <= '9' && str[i] >= '0') {
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	*start = i;

	return result;
}

char* getString(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("There is no file: %s", fileName);
		exit(0);
	}
	char* result = (char*)malloc(sizeof(char));
	if (!result) {
		printf("Not enought memory");
		exit(0);
	}
	int i = 0;

	char current;
	fscanf(file, "%c", &current);
	while (!feof(file)) {
		char* save = result;
		char* resultMore = (char*)realloc((void*)result, sizeof(char)*(i+2));
		if (!result) {
			printf("Not enought memory");
			exit(0);
		}
		result = resultMore;

		result[i] = current;
		i++;
		fscanf(file, "%c", &current);
	}
	result[i] = '\0';

	return result;
}

void printMono(MonomialT mono, FILE* file)
{
	if (mono.coeff == 1 && mono.degree == 0)
		fprintf(file, "1");
	else if (mono.coeff == -1)
		fprintf(file, "-");
	else if (mono.coeff != 1)
		fprintf(file, "%i", mono.coeff);

	if (mono.coeff == 0)
		return;
	else if (mono.coeff != 1 && mono.degree != 0)
		fprintf(file, "*");

	if (mono.degree == 1)
		fprintf(file, "x");
	else if (mono.degree != 0)
		fprintf(file, "x^%i", mono.degree);
}

void printPoly(PolynomialT *poly, FILE* file)
{
	if (isZero(poly)) {
		fprintf(file, "0");
		return;
	}

	PolynomialT* currentPoly = poly;
	while (currentPoly->monom.coeff == 0)
		currentPoly = currentPoly->nextMonom;

	do {
		printMono(currentPoly->monom, file);

		do {
			currentPoly = currentPoly->nextMonom;
		} while (currentPoly && currentPoly->monom.coeff == 0);

		if (currentPoly && currentPoly->monom.coeff > 0)
			fprintf(file, "+");
	} while (currentPoly != NULL);
}