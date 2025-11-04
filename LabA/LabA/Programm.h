#pragma once
#include <stdio.h>

typedef struct monomial {
	int coeff;
	int degree;
} MonomialT;

typedef struct polynomial {
	MonomialT monom;
	struct polynomial* nextMonom;
}PolynomialT;

void printMono(MonomialT mono, FILE* file);
void printPoly(PolynomialT* poly, FILE* file);

int isZero(PolynomialT* poly);
int areEqual(PolynomialT* poly1, PolynomialT* poly2);
PolynomialT* sumPoly(PolynomialT* a, PolynomialT* b);
PolynomialT* multiplyByMono(PolynomialT* a, MonomialT b);
PolynomialT* multiplyByPoly(PolynomialT* a, PolynomialT* b);
PolynomialT* differiate(PolynomialT* a);

PolynomialT* createPoly(MonomialT mono);
PolynomialT* createZeroPoly();
PolynomialT* createCopy(PolynomialT* original);

PolynomialT* findPrevious(PolynomialT* poly, int degree);
PolynomialT* findMono(PolynomialT* poly, int degree);

int addMono(PolynomialT* poly, MonomialT mono);
void addMonoByPrevious(PolynomialT* previousElement, MonomialT monom);
void addFirstMono(PolynomialT* poly, MonomialT monom);

int deleteFirstMono(PolynomialT* poly);
int deleteMono(PolynomialT* poly, int degree);
void deleteZero(PolynomialT* poly);
void freePoly(PolynomialT* poly);

MonomialT parseMono(char* str, int* start);
PolynomialT* parsePoly(char* str, int* start);
int parseNumber(char* str, int* start);

char* getString(char* fileName);