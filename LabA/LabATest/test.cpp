#include "pch.h"

extern "C" {
	#include "../LabA/Programm.c"
}

TEST(PolyMathOpperationsTest, isZeroZeroPolyReturnTrue_no1) {
	PolynomialT* zeroPoly = createZeroPoly();	
	int res = isZero(zeroPoly);

	EXPECT_EQ(res, 1);
}

TEST(PolyMathOpperationsTest, isZeroNullPtrReturnTrue_no2) {
	PolynomialT* nullPtr = nullptr;
	int res = isZero(nullPtr);

	EXPECT_EQ(res, 1);
}

TEST(PolyMathOpperationsTest, sumPolyDirrectReferralPolyReturnZeroPoly_no3) {
	MonomialT monom = { 1, 1 };
	PolynomialT* poly1 = createPoly(monom);
	monom.coeff = -1;
	PolynomialT* poly2 = createPoly(monom);
	PolynomialT* sum = sumPoly(poly1, poly2);

	int resIsZeroPoly = isZero(sum);
	EXPECT_EQ(resIsZeroPoly, 1);
}

TEST(PolyMathOpperationsTest, sumPolyNotZeroPolyAndZeroPolyReturnNotZeroPoly_no4) {
	MonomialT monom = { 1, 1 };
	PolynomialT* notZeroPoly = createPoly(monom);
	PolynomialT* zeroPoly = createZeroPoly();

	PolynomialT* sum = sumPoly(zeroPoly, notZeroPoly);
	int sumPolyEqualsToNotZeroPoly = areEqual(sum, notZeroPoly);
	
	EXPECT_EQ(sumPolyEqualsToNotZeroPoly, 1);
}

TEST(PolyMathOpperationsTest, multiplyByPolyNotZeroPolyAndZeroPolyReturnZeroPoly_no5) {
	MonomialT monom = { 1, 1 };
	PolynomialT* notZeroPoly = createPoly(monom);
	PolynomialT* zeroPoly = createZeroPoly();

	PolynomialT* mylt = multiplyByPoly(zeroPoly, notZeroPoly);
	int myltPolyEqualsToZeroPoly = areEqual(mylt, zeroPoly);

	EXPECT_EQ(myltPolyEqualsToZeroPoly, 1);
}

TEST(PolyMathOpperationsTest, differiateConstantPolyReturnZeroPoly_no6) {
	MonomialT monom = { 1, 0 };
	PolynomialT* poly = createPoly(monom);
	
	PolynomialT* diff = differiate(poly);
	int diffEqualsToZeroPoly = areEqual(diff, createZeroPoly());

	EXPECT_EQ(diffEqualsToZeroPoly, 1);
}

TEST(ParseTests, parseMonoStringWithoutCoeffReturnCoef1_no7) {
	char str[] = "x";
	int i = 0;
	MonomialT res = parseMono(str, &i);

	int resCoeffIs1 = res.coeff == 1;
	EXPECT_EQ(resCoeffIs1, 1);
}

TEST(ParseTests, parseMonoStringWithoutDegreeReturnDegree1_no8) {
	char str[] = "x";
	int i = 0;
	MonomialT res = parseMono(str, &i);

	int resDegreeIs1 = res.degree == 1;
	EXPECT_EQ(resDegreeIs1, 1);
}

TEST(ParseTests, parseMonoStringWithoutXReturnDegree0_no9) {
	char str[] = "1";
	int i = 0;
	MonomialT res = parseMono(str, &i);

	int resDegreeIs0 = res.degree == 0;
	EXPECT_EQ(resDegreeIs0, 1);
}

TEST(ParseTests, parsePolyZeroPolyReturnZeroPoly_no10) {
	char str[] = "0+0*x";
	int i = 0;
	PolynomialT* res = parsePoly(str, &i);

	int resPolyIsZeroPoly = areEqual(res, createZeroPoly());
	EXPECT_EQ(resPolyIsZeroPoly, 1);
}

TEST(ParseTests, parsePolyPolyWithDerectRefferalMononsReturnZeroPoly_no11) {
	char str[] = "x-x";
	int i = 0;
	PolynomialT* res = parsePoly(str, &i);

	int resPolyIsZeroPoly = areEqual(res, createZeroPoly());
	EXPECT_EQ(resPolyIsZeroPoly, 1);
}