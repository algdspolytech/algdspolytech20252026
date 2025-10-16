#include "LongArfInt.h"
#include <assert.h>

void Test_New_digit_Content_check_Return_NULL_n0() {
    printf("Test 1: Putting too big number in new digit\n");
    int number = 71;
    digit *tmp = new_digit(number, 0);
    assert(tmp == NULL && "Error in content writing/ number > 10 ");

    printf("\nPassed Test 1\n");
}

void Test_New_digit_Content_check_Return_NULL_n1() {
    printf("\nTest 2: Putting too small number in new digit\n");
    int number = -57;
    digit *tmp = new_digit(number, 0);
    assert(tmp == NULL && "Error in content writing/ number < 0 ");

    printf("\nPassed Test 2\n");
}

void Test_New_digit_Content_check_Return_NULL_n2() {
    printf("\nTest 3: Putting valid number in new digit\n");
    int number = 5;
    digit *tmp = new_digit(number, 0);
    assert(tmp != NULL && "Error in content validness check");
    printf("\nPassed Test 3\n");
}

void Test_New_digit_Exponent_check_Return_NULL_n0() {
    printf("\nTest 4: Putting invalid exponent in new digit\n");
    int exponet = -57;
    digit *tmp = new_digit(2, exponet);
    assert(tmp == NULL && "Error in exponet writing/ number < 0 ");

    printf("\nPassed Test 4\n");
}

void Test_New_digit_Exponent_check_Return_digit_n1() {
    printf("\nTest 5: Putting valid exponent in new digit\n");
    int exponet = 57;
    digit *tmp = new_digit(2, exponet);
    assert(tmp != NULL && "Error in exponent validness check");
    free(tmp);
    printf("\nPassed Test 5\n");
}

void Test_App_end_digit_Digit_check_Return_NULL_n0() {
    printf("\nTest 6: Putting invalid number in app_end_digit\n");
    long_int number;
    init_long_int(&number);
    assert(app_end_digit(&number,54,1) == NULL && "Error in digit creating isn't catching");
    printf("\nPassed Test 6\n");
}

void Test_App_end_digit_Digit_check_Return_Long_Arif_n1() {
    printf("\nTest 7: Checking work app_end_digit with valid digit\n");
    long_int number;
    init_long_int(&number);
    assert(app_end_digit(&number,7,1) != NULL && "Error in digit validness check");
    printf("\nPassed Test 7\n");
}

void Test_App_end_digit_Digit_check_Return_NULL_n2() {
    printf("\nTest 8: Checking work app_end_digit with currupted long_arif\n");
    long_int number;
    init_long_int(&number);
    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    number.tail = tmp;
    number.head = NULL;
    assert(app_end_digit(&number,7,2) == NULL && "Error in long_int validness check");
    free(tmp);
    printf("\nPassed Test 8\n");
}

void Test_Read_long_int_Reading_check_Return_Long_arg_n0() {
    printf("\nTest 9: Checking read_long valid number read\n");
    long_int number;
    init_long_int(&number);

    FILE *test_input = fopen("test_input.txt", "w");
    fprintf(test_input, "5646546546468465468768764687");
    fclose(test_input);

    freopen("test_input.txt", "r", stdin);
    number = read_long_int();

    freopen("CON", "r", stdin);

    assert(number.head->content ==5 && "Error in number reading");
    assert(number.tail->content ==7 && "Error in number reading");
    assert(number.head->exp ==27 && "Error in number reading");
    assert(number.tail->exp ==0 && "Error in number reading");
    assert(number.sign == 1 && "Error in number reading");
    printf("\nPassed Test 9\n");
}


void Test_Read_long_int_Sign_check_Return_long_int_n1() {
    printf("\nTest 10: Checking read_long - sign read\n");
    long_int number;
    init_long_int(&number);

    FILE *test_input = fopen("test_input.txt", "w");
    fprintf(test_input, "-5465405462024568");
    fclose(test_input);

    freopen("test_input.txt", "r", stdin);
    number = read_long_int();

    freopen("CON", "r", stdin);

    assert((number.head != NULL || number.sign != -1) && "Error in read_long - sign read");
    printf("\nPassed Test 10\n");
}


void Test_Read_long_int_Sign_check_Return_NULL_n2() {
    printf("\nTest 11: Checking read_long invalid character read\n");
    long_int number;
    init_long_int(&number);

    FILE *test_input = fopen("test_input.txt", "w");
    fprintf(test_input, "#45612");
    fclose(test_input);

    freopen("test_input.txt", "r", stdin);
    number = read_long_int();

    freopen("CON", "r", stdin);

    assert(number.head == NULL && "Error in invalid character check");
    printf("\nPassed Test 11\n");
}

void Test_Read_long_int_Sign_check_Return_long_int_n3() {
    printf("\nTest 12: Checking read_long + sign read\n");
    long_int number;
    init_long_int(&number);

    FILE *test_input = fopen("test_input.txt", "w");
    fprintf(test_input, "+7542");
    fclose(test_input);

    freopen("test_input.txt", "r", stdin);
    number = read_long_int();

    freopen("CON", "r", stdin);

    assert((number.head != NULL || number.sign != 1) && "Error in read_long + sign read");
    printf("\nPassed Test 12\n");
}

void Test_Read_long_int_Reading_check_Return_NULL_n4() {
    printf("\nTest 13: Checking read_long too long number read\n");
    long_int number;
    init_long_int(&number);

    FILE *test_input = fopen("too_long.txt", "w");
    for (int i = SHRT_MAX + 4; i > 0; i--)
        fprintf(test_input, "1");
    fclose(test_input);

    freopen("too_long.txt", "r", stdin);
    number = read_long_int();

    freopen("CON", "r", stdin);

    assert(number.head == NULL && "Error in number reading");
    printf("\nPassed Test 13\n");
}

void Test_Add_strt_digit_Digit_check_Return_NULL_n0() {
    printf("\nTest 14: Putting invalid number in app_strt_digit\n");
    long_int number;
    init_long_int(&number);
    assert(add_strt_digit(&number,54,1) == NULL && "Error in digit creating isn't catching");
    printf("\nPassed Test 14\n");
}

void Test_Add_strt_digit_Digit_check_Return_Long_Arif_n1() {
    printf("\nTest 15: Checking work app_strt_digit with valid digit\n");
    long_int number;
    init_long_int(&number);
    assert(add_strt_digit(&number,7,1) != NULL && "Error in digit validness check");
    printf("\nPassed Test 15\n");
}

void Test_Add_strt_digit_Digit_check_Return_NULL_n2() {
    printf("\nTest 16: Checking work app_strt_digit with currupted long_arif\n");
    long_int number;
    init_long_int(&number);
    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    number.head = NULL;
    number.tail = tmp;
    assert(add_strt_digit(&number,7,2) == NULL && "Error in long_int validness check");
    free(tmp);
    printf("\nPassed Test 16\n");
}

void Test_Copy_long_int_Digit_check_Return_NULL_n0() {
    printf("\nTest 17: Putting invalid number in copy_long_int\n");
    long_int number;
    init_long_int(&number);

    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    number.head = tmp;
    number.tail = NULL;

    long_int copy_num = copy_long_int(&number);
    assert(copy_num.head == NULL && "Error in digit creating isn't catching");

    printf("\nPassed Test 17\n");
}

void Test_Check_validness_Digit_check_Return_minus_1_n0() {
    printf("\nTest 18: Putting invalid number in check_validness\n");
    long_int number;
    init_long_int(&number);

    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    number.head = tmp;
    number.tail = NULL;

    assert(check_validness(&number) == -1 && "Error in validness check");
    free(tmp);
    printf("\nPassed Test 18\n");
}

void Test_Check_validness_Digit_check_Return_minus_1_n1() {
    printf("\nTest 19: Putting invalid number in check_validness\n");
    long_int number;
    init_long_int(&number);

    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    number.head = NULL;
    number.tail = tmp;

    assert(check_validness(&number) == -1 && "Error in validness check");
    free(tmp);
    printf("\nPassed Test 19\n");
}

void Test_Check_validness_Digit_check_Return_minus_1_n2() {
    printf("\nTest 20: Putting valid digits but invalid exponets\n");
    long_int number;
    init_long_int(&number);

    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 2;
    digit *tmp1 = (digit *) malloc(sizeof(digit));
    tmp1->next = NULL;
    tmp1->prev = NULL;
    tmp1->content = 4;
    tmp1->exp = 10;
    number.head = tmp1;
    number.head->next = tmp;
    number.tail = tmp;

    assert(check_validness(&number) == -1 && "Error in exponent check");
    free(tmp);
    free(tmp1);
    printf("\nPassed Test 20\n");
}

void Test_Check_validness_Digit_check_Return_1_n3() {
    printf("\nTest 21: Putting valid digits but invalid exponets\n");
    long_int number;
    init_long_int(&number);

    digit *tmp = (digit *) malloc(sizeof(digit));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->content = 3;
    tmp->exp = 0;
    digit *tmp1 = (digit *) malloc(sizeof(digit));
    tmp1->next = NULL;
    tmp1->prev = NULL;
    tmp1->content = 4;
    tmp1->exp = 1;
    number.head = tmp1;
    number.head->next = tmp;
    number.tail = tmp;


    assert(check_validness(&number) == 1 && "Error in exponent check");
    free(tmp);
    free(tmp1);
    printf("\nPassed Test 21\n");
}

void Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n0() {
    printf("\nTest 22: Sum of two positive numbers with numbers with different digits power first > second\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 4, 2);
    app_end_digit(&num1, 0, 1);
    app_end_digit(&num1, 1, 0);


    app_end_digit(&num2, 5, 1);
    app_end_digit(&num2, 6, 0);


    result = summ_long_int(&num1, &num2);

    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 4 && "Error in summing algorithm");
    assert(result.head->next->content == 5 && "Error in summing algorithm");
    assert(result.tail->content == 7 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 22\n");
}

void Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n1() {
    printf("\nTest 23: Sum of two positive numbers with numbers with different digits power first < second\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    app_end_digit(&num2, 5, 4);
    app_end_digit(&num2, 3, 3);
    app_end_digit(&num2, 9, 2);
    app_end_digit(&num2, 0, 1);
    app_end_digit(&num2, 3, 0);


    app_end_digit(&num1, 6, 0);


    result = summ_long_int(&num1, &num2);

    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 5 && "Error in summing algorithm");
    assert(result.head->next->content == 3 && "Error in summing algorithm");
    assert(result.head->next->next->content == 9 && "Error in summing algorithm");
    assert(result.tail->prev->content == 0 && "Error in summing algorithm");
    assert(result.tail->content == 9 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 23\n");
}

void Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n2() {
    printf("\nTest 24: Sum of two positive numbers with numbers with digits overflow\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num2, 7, 2);
    app_end_digit(&num2, 4, 1);
    app_end_digit(&num2, 9, 0);

    app_end_digit(&num1, 4, 2);
    app_end_digit(&num1, 3, 1);
    app_end_digit(&num1, 7, 0);


    result = summ_long_int(&num1, &num2);

    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 1 && "Error in summing algorithm");
    assert(result.head->next->content == 1 && "Error in summing algorithm");
    assert(result.tail->prev->content == 8 && "Error in summing algorithm");
    assert(result.tail->content == 6 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 24\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n0() {
    printf("\nTest 25: Sum of positive and negative numbers with different digits power first > second\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 1, 3);
    app_end_digit(&num1, 0, 2);
    app_end_digit(&num1, 5, 1);
    app_end_digit(&num1, 0, 0);


    app_end_digit(&num2, 5, 1);
    app_end_digit(&num2, 0, 0);
    num2.sign = -1;

    result = summ_long_int(&num1, &num2);


    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 1 && "Error in summing algorithm");
    assert(result.head->next->content == 0 && "Error in summing algorithm");
    assert(result.tail->prev->content == 0 && "Error in summing algorithm");
    assert(result.tail->content == 0 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 25\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n1() {
    printf("\nTest 26: Sum of positive and negative numbers with different digits power firts > second and digit underflow\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 1, 3);
    app_end_digit(&num1, 0, 2);
    app_end_digit(&num1, 0, 1);
    app_end_digit(&num1, 0, 0);


    app_end_digit(&num2, 5, 1);
    app_end_digit(&num2, 0, 0);
    num2.sign = -1;

    result = summ_long_int(&num1, &num2);


    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 9 && "Error in summing algorithm");
    assert(result.head->next->content == 5 && "Error in summing algorithm");
    assert(result.tail->content == 0 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 26\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n2() {
    printf(
        "\nTest 27: Sum of positive and negative numbers with same digits power firts > second and digit underflow\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 4, 2);
    app_end_digit(&num1, 0, 1);
    app_end_digit(&num1, 0, 0);


    app_end_digit(&num2, 3, 2);
    app_end_digit(&num2, 5, 1);
    app_end_digit(&num2, 0, 0);
    num2.sign = -1;

    result = summ_long_int(&num1, &num2);


    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 5 && "Error in summing algorithm");
    assert(result.tail->content == 0 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 27\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n3() {
    printf(
        "\nTest 28: Sum of positive and negative numbers with same digits power and most significant digit first > second and digit underflow\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 4, 2);
    app_end_digit(&num1, 0, 1);
    app_end_digit(&num1, 0, 0);
    num1.sign = -1;


    app_end_digit(&num2, 3, 2);
    app_end_digit(&num2, 5, 1);
    app_end_digit(&num2, 0, 0);


    result = summ_long_int(&num1, &num2);


    assert(result.sign == -1 && "Error in sign determination");
    assert(result.head->content == 5 && "Error in summing algorithm");
    assert(result.tail->content == 0 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 28\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n4() {
    printf(
        "\nTest 29: Sum of positive and negative numbers with same digits power and most significant digit second > first \n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 4, 2);
    app_end_digit(&num1, 6, 1);
    app_end_digit(&num1, 7, 0);
    num1.sign = -1;


    app_end_digit(&num2, 7, 2);
    app_end_digit(&num2, 1, 1);
    app_end_digit(&num2, 4, 0);


    result = summ_long_int(&num1, &num2);


    assert(result.sign == 1 && "Error in sign determination");
    assert(result.head->content == 2 && "Error in summing algorithm");
    assert(result.head->next->content == 4 && "Error in summing algorithm");
    assert(result.tail->content == 7 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 29\n");
}

void Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n5() {
    printf("\nTest 30: Sum of positive and negative numbers with diferent digits power second > first \n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 8, 2);
    app_end_digit(&num1, 4, 1);
    app_end_digit(&num1, 6, 0);
    num1.sign = -1;


    app_end_digit(&num2, 4, 0);


    result = summ_long_int(&num1, &num2);


    assert(result.sign == -1 && "Error in sign determination");
    assert(result.head->content == 8 && "Error in summing algorithm");
    assert(result.head->next->content == 4 && "Error in summing algorithm");
    assert(result.tail->content == 2 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 30\n");
}

void Test_Summ_long_int_Zero_Sum_Return_Zero_n0() {
    printf("\nTest 31: Sum of number and its alternate\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    app_end_digit(&num1, 1, 2);
    app_end_digit(&num1, 2, 1);
    app_end_digit(&num1, 3, 0);
    num1.sign = 1;


    app_end_digit(&num2, 1, 2);
    app_end_digit(&num2, 2, 1);
    app_end_digit(&num2, 3, 0);
    num2.sign = -1;

    result = summ_long_int(&num1, &num2);

    assert(result.sign == 1 && "negativ zero");
    assert(result.head->content == 0 && "Erorr in summing algorithm");
    assert(result.head->exp == 0 && "Error in summing algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 31\n");
}


void Test_Mult_long_int_Too_long_number_Return_NULL_n0() {
    printf("\nTest 32: Multiplication of too long positive number\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    FILE *test_input = fopen("too_long.txt", "w");
    for (int i = SHRT_MAX+1; i > 0; i--)
        fprintf(test_input, "1");
    fclose(test_input);

    freopen("too_long.txt", "r", stdin);
    num1 = read_long_int();

    freopen("CON", "r", stdin);


    app_end_digit(&num2, 3, 1);
    app_end_digit(&num2, 4, 0);
    num2.sign = 1;

    result = mult_long_int(&num1, &num2);


    assert(result.sign == 1 && "Erorr in initialasing number ");
    assert(result.head == NULL && "Erorr in exponent checking ");
    assert(result.tail == NULL && "Erorr in exponent checking ");


    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 32\n");
}

void Test_Mult_long_int_Positive_Return_Correct_product_n1() {
    printf("\nTest 33: Multiplication of positive numbers\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    app_end_digit(&num1, 3, 3);
    app_end_digit(&num1, 7, 2);
    app_end_digit(&num1, 7, 1);
    app_end_digit(&num1, 1, 0);


    app_end_digit(&num2, 1, 1);
    app_end_digit(&num2, 5, 0);


    result = mult_long_int(&num1, &num2);


    assert(result.sign == 1 && "Erorr in sign determenation");
    assert(result.head->content == 5 && "Erorr in multiplication algorithm");
    assert(result.head->next->next->content == 5 && "Erorr in multiplication algorithm");
    assert(result.tail->content == 5 && "Erorr in multiplication algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 33\n");
}

void Test_Mult_long_int_Positive_negative_Return_Correct_product_n2() {
    printf("\nTest 34: Multiplication of positive and negative numbers\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    app_end_digit(&num1, 7, 3);
    app_end_digit(&num1, 7, 2);
    app_end_digit(&num1, 4, 1);
    app_end_digit(&num1, 1, 0);
    num1.sign = -1;

    app_end_digit(&num2, 1, 4);
    app_end_digit(&num2, 9, 3);
    app_end_digit(&num2, 3, 2);
    app_end_digit(&num2, 4, 1);
    app_end_digit(&num2, 5, 0);


    result = mult_long_int(&num1, &num2);


    assert(result.sign == -1 && "Erorr in sign determenation");
    assert(result.head->content == 1 && "Erorr in multiplication algorithm");
    assert(result.head->exp == 8 && "Erorr in multiplication algorithm");
    assert(result.head->next->next->content ==9 && "Erorr in multiplication algorithm");
    assert(result.head->next->next->exp == 6 && "Erorr in multiplication algorithm");
    assert(result.tail->content == 5 && "Erorr in multiplication algorithm");
    assert(result.tail->exp == 0 && "Erorr in multiplication algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 34\n");
}

void Test_Mult_long_int_Zero_Return_Zero_n3() {
    printf("\nTest 35: Multiplication by zero\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);


    app_end_digit(&num1, 1, 2);
    app_end_digit(&num1, 2, 1);
    app_end_digit(&num1, 3, 0);


    app_end_digit(&num2, 0, 0);


    result = mult_long_int(&num1, &num2);

    assert(result.sign == 1 && "Negative zero");
    assert(result.head->content == 0 && "Erorr in multiplication algorithm");
    assert(result.head->exp == 0 && "Erorr in multiplication algorithm");

    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 35\n");
}


void Test_Power_long_int_Positive_Exponent_Return_Correct_number_n0() {
    printf("\nTest 36: Positive exponent\n");
    long_int base, result;
    init_long_int(&base);


    app_end_digit(&base, 2, 0);


    result = power_long_int(&base, 3);

    assert(result.sign == 1 && "Erorr in sign determenation");
    assert(result.head->content == 8 && "Erorr in multiplication algorithm");

    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 36\n");
}

void Test_Power_long_int_Exponent_Zero_Return_One_n1() {
    printf("\nTest 37: Exponent zero\n");
    long_int base, result;
    init_long_int(&base);

    app_end_digit(&base, 5, 0);
    base.sign = 1;

    result = power_long_int(&base, 0);


    assert(result.sign == 1 && "Exp == 0 error sign");
    assert(result.head->content == 1 && "Exp == 0 error content");
    assert(result.head->exp == 0 && "Exp == 0 error exp");

    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 37\n");
}

void Test_Power_long_int_Exponent_One_Return_Base_n2() {
    printf("\nTest 38: Exponent one\n");
    long_int base, result;
    init_long_int(&base);


    app_end_digit(&base, 7, 0);
    base.sign = 1;

    result = power_long_int(&base, 1);


    assert(result.sign == 1 && "Exp == 1 error sign");
    assert(result.head->content == 7 && "Exp == 1 error content");


    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 38\n");
}

void Test_Power_long_int_Negative_Base_Even_Exponent_Return_Positive_n3() {
    printf("\nTest 39: Negative base with even exponent\n");
    long_int base, result;
    init_long_int(&base);


    app_end_digit(&base, 3, 0);
    base.sign = -1;

    result = power_long_int(&base, 2);


    assert(result.sign == 1 && "Exp%2==0 && > 0 base < 0 error sign");
    assert(result.head->content == 9 && "Exp%2==0 && > 0 base < 0 error content");

    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 39\n");
}

void Test_Power_long_int_Negative_Base_Odd_Exponent_Return_Negative_n4() {
    printf("\nTest 40: Negative base with odd exponent\n");
    long_int base, result;
    init_long_int(&base);


    app_end_digit(&base, 3, 0);
    base.sign = -1;

    result = power_long_int(&base, 3);


    assert(result.sign == -1 && "Exp%2==1, base < 0,  error sign");
    assert(result.head->content == 2 && "Exp%2==1 && > 0 base < 0 error content");

    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 40\n");
}

void Test_Power_long_int_Negative_Exponent_Return_Empty_n5() {
    printf("\nTest 41: Negative exponent \n");
    long_int base, result;
    init_long_int(&base);


    app_end_digit(&base, 2, 0);
    base.sign = 1;

    result = power_long_int(&base, -1);

    assert(result.head == NULL && "Negative exp == NULL but it return smth");

    clear_long_int(&base);
    clear_long_int(&result);
    printf("\nPassed Test 41\n");
}


void Test_Print_long_int_Valid_Number_Return_Printed_n0() {
    printf("\nTest 42: Print valid positive number\n");
    long_int number, number_read;
    init_long_int(&number);
    init_long_int(&number_read);

    app_end_digit(&number, 1, 2);
    app_end_digit(&number, 2, 1);
    app_end_digit(&number, 3, 0);
    number.sign = 1;

    printf("\nExpected output: 123");
    printf("\nActual output: ");
    print_long_int(&number);
    printf("\n");


    freopen("print_test.txt", "w", stdout);
    print_long_int(&number);
    freopen("CON", "w", stdout);

    freopen("print_test.txt", "r", stdin);
    number_read = read_long_int();
    freopen("CON", "r", stdin);

    assert(number.head->content == number_read.head->content && "Printing error");
    assert(number.sign == number_read.sign && "Printing error sign ");
    assert(number.tail->content == number_read.tail->content && "Printing error");


    clear_long_int(&number);
    clear_long_int(&number_read);
    printf("\nPassed Test 42\n");
}

void Test_Print_long_int_Valid_Negative_Number_Return_Printed_n1() {
    printf("\nTest 43: Print valid negative number\n");
    long_int number,number_read;
    init_long_int(&number);
    init_long_int(&number_read);

    app_end_digit(&number, 4, 2);
    app_end_digit(&number, 5, 1);
    app_end_digit(&number, 6, 0);
    number.sign = -1;

    printf("\nExpected output: -456");
    printf("\nActual output: ");
    print_long_int(&number);
    printf("\n");

    freopen("print_test.txt", "w", stdout);
    print_long_int(&number);
    freopen("CON", "w", stdout);

    freopen("print_test.txt", "r", stdin);
    number_read = read_long_int();
    freopen("CON", "r", stdin);

    assert(number.head->content == number_read.head->content && "Printing error");
    assert(number.sign == number_read.sign && "Printing error sign ");
    assert(number.tail->content == number_read.tail->content && "Printing error");


    clear_long_int(&number);
    clear_long_int(&number_read);
    printf("\nPassed Test 43\n");
}

void Test_Print_long_int_Empty_Number_Return_NULL_n2() {
    printf("\nTest 44: Print empty number\n");
    long_int number;
    init_long_int(&number);

    assert(print_long_int(&number) == NULL && "No number == NULL but it return smth");

    printf("\nPassed Test 44\n");
}

void Test_Mult_long_int_Too_long_number_Return_NULL_n6() {
    printf("\nTest 45: Sum of too long positive number\n");
    long_int num1, num2, result;
    init_long_int(&num1);
    init_long_int(&num2);

    FILE *test_input = fopen("too_long.txt", "w");
    for (int i = SHRT_MAX+1; i > 0; i--)
        fprintf(test_input, "1");
    fclose(test_input);

    freopen("too_long.txt", "r", stdin);
    num1 = read_long_int();

    freopen("CON", "r", stdin);


    app_end_digit(&num2, 3, 1);
    app_end_digit(&num2, 4, 0);
    num2.sign = 1;

    result = summ_long_int(&num1, &num2);


    assert(result.sign == 1 && "Erorr in initialasing number ");
    assert(result.head == NULL && "Erorr in exponent checking ");
    assert(result.tail == NULL && "Erorr in exponent checking ");


    clear_long_int(&num1);
    clear_long_int(&num2);
    clear_long_int(&result);
    printf("\nPassed Test 45\n");
}


int main(void) {

    Test_New_digit_Content_check_Return_NULL_n0();
    Test_New_digit_Content_check_Return_NULL_n1();
    Test_New_digit_Content_check_Return_NULL_n2();
    Test_New_digit_Exponent_check_Return_NULL_n0();
    Test_New_digit_Exponent_check_Return_digit_n1();
    Test_App_end_digit_Digit_check_Return_NULL_n0();
    Test_App_end_digit_Digit_check_Return_Long_Arif_n1();
    Test_App_end_digit_Digit_check_Return_NULL_n2();
    Test_Read_long_int_Reading_check_Return_Long_arg_n0();
    Test_Read_long_int_Sign_check_Return_long_int_n1();
    Test_Read_long_int_Sign_check_Return_NULL_n2();
    Test_Read_long_int_Sign_check_Return_long_int_n3();
    Test_Read_long_int_Reading_check_Return_NULL_n4();
    Test_Add_strt_digit_Digit_check_Return_NULL_n0();
    Test_Add_strt_digit_Digit_check_Return_Long_Arif_n1();
    Test_Add_strt_digit_Digit_check_Return_NULL_n2();
    Test_Copy_long_int_Digit_check_Return_NULL_n0();
    Test_Check_validness_Digit_check_Return_minus_1_n0();
    Test_Check_validness_Digit_check_Return_minus_1_n1();
    Test_Check_validness_Digit_check_Return_minus_1_n2();
    Test_Check_validness_Digit_check_Return_1_n3();
    Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n0();
    Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n1();
    Test_Summ_long_int_Valid_Numbers_Return_Correct_sum_n2();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n0();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n1();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n2();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n3();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n4();
    Test_Summ_long_int_Positive_Negative_Return_Correct_sum_n5();
    Test_Summ_long_int_Zero_Sum_Return_Zero_n0();
    Test_Mult_long_int_Too_long_number_Return_NULL_n0();
    Test_Mult_long_int_Positive_Return_Correct_product_n1();
    Test_Mult_long_int_Positive_negative_Return_Correct_product_n2();
    Test_Mult_long_int_Zero_Return_Zero_n3();
    Test_Power_long_int_Positive_Exponent_Return_Correct_number_n0();
    Test_Power_long_int_Exponent_Zero_Return_One_n1();
    Test_Power_long_int_Exponent_One_Return_Base_n2();
    Test_Power_long_int_Negative_Base_Even_Exponent_Return_Positive_n3();
    Test_Power_long_int_Negative_Base_Odd_Exponent_Return_Negative_n4();
    Test_Power_long_int_Negative_Exponent_Return_Empty_n5();
    Test_Print_long_int_Valid_Number_Return_Printed_n0();
    Test_Print_long_int_Valid_Negative_Number_Return_Printed_n1();
    Test_Print_long_int_Empty_Number_Return_NULL_n2();
    Test_Mult_long_int_Too_long_number_Return_NULL_n6();

    return 0;
}
