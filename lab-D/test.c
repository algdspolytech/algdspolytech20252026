
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "func.h"
#define MAX_DIGITS 100
#define NUM_OPERATION 4

#define RUN_MAIN_PROGRAM
#ifdef RUN_MAIN_PROGRAM

char operations[]={'+','-','*','/'};

int arrays_equal(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }
    return 1;
}


void TestSolveEquation_plus_and_minus_no1() {
    printf("==========TEST 1==========\n");
    int digits[]={1,2,4,5,10};
    char operations[]={'+','-','+','-'};
    double result=solve_equation(digits,operations,5);
    assert(result==-6);
    
    printf("PASSED...\n");
}
void TestSolveEquation_mult_and_division_no2(){
    printf("==========TEST 2==========\n");
    int digits[]={1,2,4,5,10};
    char operations[]={'*','/','*','/'};
    double result=solve_equation(digits,operations,5);
    assert(result==0.25);
    
    printf("PASSED...\n");
}
void TestSolveEquation_mixed__no3() {
    printf("==========TEST 3==========\n");
    int digits[]={1,2,4,5,10};
    char operations[]={'+','/','*','-'};
    double result=solve_equation(digits,operations,5);
    assert(result==-6.5);
    
    printf("PASSED...\n");
}
void TestSolveEquation_division_by_zero_no4() {
    printf("==========TEST 4==========\n");
    int digits[]={1,0,4,5,10};
    char operations[]={'/','+','*','-'};
    double result=solve_equation(digits,operations,5);
     assert(isnan(result));
    
    printf("PASSED...\n");
}
void TestSolveEquation_empty_no5() {
    printf("==========TEST 5==========\n");
    int digits[]={1};
    char operations[]={'+'};
    double result=solve_equation(digits,operations,5);
    assert(result==1);
    
    printf("PASSED...\n");
}

void TestDigitsSplit_simple_no6() {
    printf("==========TEST 6==========\n");
    char num_str[] = "1234";
    int digits[4];
    int k=digits_split(num_str,digits);
    assert(k==4);
    int expected[]={1,2,3,4};
    assert(arrays_equal(digits,expected,4)==1);
    
    printf("PASSED...\n");
}
void TestDigitsSplit_one_digit_no7(){
    printf("==========TEST 7==========\n");
    char num_str[] ="1";
    int digits[1];
    int k=digits_split(num_str,digits);
    assert(k==1);
    int expected[]={1};
    assert(digits[0]==expected[0]);

}
void TestFindEquation_basic_found_no8(){
       printf("==========TEST 8==========\n");
    int digits[] = {1,2,3,4};
    int n = 4;
    char result_oper[MAX_DIGITS] = {0};
    char current_oper[MAX_DIGITS] = {0};
    int target=10;
    
    int found = find_equation(digits, n, 0, result_oper, current_oper, operations, target);
    
    assert(found == 1); // 1+2+3+4=10
    
    assert(result_oper[0] == '+' && result_oper[1]=='+' && result_oper[2]== '+');
    printf("PASSED...\n");
}
void TestFindEquation_mixed_found_no9(){
       printf("==========TEST 9==========\n");
    int digits[] = {1,1,4,4};
    int n = 4;
    char result_oper[MAX_DIGITS] = {0};
    char current_oper[MAX_DIGITS] = {0};
    int target=0; 
    
    int found = find_equation(digits, n, 0, result_oper, current_oper, operations, target);
   
    assert(found == 1);  // 1-1*4/4
   
    printf("PASSED...\n");
}
void TestFindEquation_not_found_no10() {
    printf("==========TEST 10==========\n");
    int digits[] = {1,1,1};
    int n = 3;
    char result_oper[MAX_DIGITS] = {0};
    char current_oper[MAX_DIGITS] = {0};
    int target=5;
    int found = find_equation(digits, n, 0, result_oper, current_oper, operations, target);
    
    assert(found == 0); 
    printf("PASSED...\n");
}
void TestFindEquation_one_digit_no11() {
    printf("==========TEST 11==========\n");
    char num_str[] = "123";
    int digits[MAX_DIGITS];
    int n = digits_split(num_str, digits);
    char result_oper[MAX_DIGITS] = {0};
    char current_oper[MAX_DIGITS] = {0};
    int target=123;
    int found = find_equation(digits, n, 0, result_oper, current_oper, operations, target);
    
    assert(found == 1); 
    printf("PASSED...\n");
}
void TestFindEquation_division_by_zero_no12() {
    printf("==========TEST 12==========\n");
    int digits[] = {1,0,0};
    int n = 3;
    char result_oper[MAX_DIGITS] = {0};
    char current_oper[MAX_DIGITS] = {0};
    int target=3;
    int found = find_equation(digits, n, 0, result_oper, current_oper, operations, target);
    
    assert(found == 0); 
    printf("PASSED...\n");
}
int main(){
    TestSolveEquation_plus_and_minus_no1();
    TestSolveEquation_mult_and_division_no2();
    TestSolveEquation_mixed__no3();
    TestSolveEquation_division_by_zero_no4();
    TestSolveEquation_empty_no5();
    TestDigitsSplit_simple_no6();
    TestDigitsSplit_one_digit_no7();
    TestFindEquation_basic_found_no8();
    TestFindEquation_mixed_found_no9();
    TestFindEquation_not_found_no10();
    TestFindEquation_one_digit_no11();
    TestFindEquation_division_by_zero_no12();
}






#endif