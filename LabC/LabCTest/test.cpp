#include "pch.h"

extern "C" {
#include "../LabC/Program.c"
}

TEST(MatrixOperationsTest, areEqualNULLandNULLReturnTrue_no1) {
	EXPECT_EQ(areEqual(NULL, NULL), 1);
}

TEST(MatrixOperationsTest, areEqualNULLandNotNULLReturnFalse_no2) {
	EXPECT_EQ(areEqual(createUnitMatrix(), NULL), 0);
}

TEST(MatrixFunctionsTest, addToMatrixNULLPointerReturnNewMatrix_no3) {
	MatrixElementT element = { 0, 0, 1 };
	MatrixT* newMatrix = addToMatrix(NULL, element);

	int elemetIsAdded = areEqual(newMatrix, createMatrix(element));
	EXPECT_EQ(elemetIsAdded, 1);
}

TEST(MatrixFunctionsTest, addToMatrixFirstElemntReturnMatrixWithFirstElemnt_no4) {
	MatrixElementT first = { 0, 0, 1 };
	MatrixElementT second = { 0, 1, 1 };
	
	MatrixT* a = addToMatrix(createMatrix(first), second);
	MatrixT* b = addToMatrix(createMatrix(second), first);

	int elemetIsAddedCorrectly = areEqual(a, b);
	EXPECT_EQ(elemetIsAddedCorrectly, 1);
}

TEST(MatrixFunctionsTest, deleteElementElementNotExistReturnOriginalMatrix_no5) {
	MatrixElementT first = { 0, 0, 1 };
	MatrixElementT second = { 1, 1, 1 };

	MatrixT* a = createMatrix(first);
	a = deleteElement(a, second);
	
	int nothingChanged = areEqual(a, createMatrix(first));
	EXPECT_EQ(nothingChanged, 1);
}

TEST(MatrixFunctionsTest, deleteElementDeleteFirstElementReturnMatrixWithoutFirst_no6) {
	MatrixElementT first = { 0, 0, 1 };
	MatrixElementT second = { 1, 1, 1 };

	MatrixT* a = createMatrix(first);
	a = addToMatrix(a, second);
	a = deleteElement(a, first);

	int elementDeleted = areEqual(a, createMatrix(second));
	EXPECT_EQ(elementDeleted, 1);
}

TEST(MatrixFunctionsTest, deleteElementDeleteOnlyelementReturnNULL_no7) {
	MatrixElementT first = { 0, 0, 1 };

	MatrixT* a = createMatrix(first);
	a = deleteElement(a, first);

	int elementDeleted = areEqual(a, NULL);
	EXPECT_EQ(elementDeleted, 1);
}

TEST(FieldFunctionsTest, createCircutOfPointPointOnBoardReturnCircut_no8) {
	MatrixElementT point = { 0, 0, 0 };

	MatrixElementT circut1 = { 0, 1, 1 };
	MatrixElementT circut2 = { 1, 0, 1 };
	MatrixT* circut = createMatrix(circut1);
	circut = addToMatrix(circut, circut2);

	int circutIsCorrect = areEqual(circut, createCircutOfPoint(NULL, point, 10, 10));
	EXPECT_EQ(circutIsCorrect, 1);
}

TEST(FieldFunctionsTest, createCircutOfPointSmallFieldReturnNULL_no9) {
	MatrixElementT point = { 0, 0, 0 };

	int circutIsCorrect = areEqual(createCircutOfPoint(NULL, point, 1, 1), NULL);
	EXPECT_EQ(circutIsCorrect, 1);
}

TEST(FieldFunctionsTest, createCircutDoubleWallReturnCircut_no10) {
	MatrixElementT point1 = { 0, 0, 0 };
	MatrixElementT point2 = { 1, 0, 0 };
	MatrixT* field = createMatrix(point1);
	field = addToMatrix(field, point2);
	MatrixT* circut = createCircut(field, 10, 10);

	MatrixElementT circut1 = {0, 1, 1};
	MatrixElementT circut2 = {1, 1, 1};
	MatrixElementT circut3 = {2, 0, 1};
	MatrixElementT circut4 = {2, 1, 1};
	MatrixT* exspected = createMatrix(circut1);
	exspected = addToMatrix(exspected, circut2);
	exspected = addToMatrix(exspected, circut3);
	exspected = addToMatrix(exspected, circut4);

	int circutIsCorrect = areEqual(circut, exspected);
	EXPECT_EQ(circutIsCorrect, 1);
}