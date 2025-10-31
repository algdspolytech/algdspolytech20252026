#pragma warning (disable:4996)



#include <assert.h> 
#include "Header.h" 


void Test_FromStr2Num_AlphaDigitString_ReturnNULLN1() {
    printf("Test 1: Numbers and letters or delimetrs mixed in string\n");
    
   
    int len = 4;
    const char* str = ".f75";

    int res = FromStr2Num(str, len);

    assert((res == -1));
    printf("Returned NULL. Error:letters or delimetrs mixed in string\n");
}

void Test_FromStr2Num_DigitString_ReturnNUMN2(){
    printf("Test 2:Just digits in string\n");


    int len = 3;
    const char* str = "137";

    int res = FromStr2Num(str, len);

    assert((res == 137));
    printf("Success\n");

}

void Test_IfSameWorker_DifferentWorkers_ReturnTrueN3() {
    printf("Test 3:Same workers\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Иван";
    B.surname = "Цой";

    res = IfSameWorker(&A, &B);

    assert((res == 1));
    printf("Success\n");

}

void Test_IfSameWorker_DifferentWorkers_ReturnFalseN4() {
    printf("Test 4:Different workers\n");


    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    res = IfSameWorker(&A, &B);

    assert((res == 0));
    printf("Success\n");

}

void Test_WorkerCmp_DifferentWorkers_ReturnTrueN5() {
    printf("Test 5:More hours\n");


    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 4;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    res = WorkerCmp(&A, &B);

    assert((res == 1));
    printf("Success\n");

}

void Test_WorkerCmp_DifferentWorkers_ReturnFalseN6() {
    printf("Test 6:Less Hours\n");


    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    res = WorkerCmp(&A, &B);

    assert((res == 0));
    printf("Success\n");

}

void Test_WorkerCmp_DifferentWorkers_ReturnFalseN7() {
    printf("Test 7:SameHours\n");


    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";
    res = WorkerCmp(&A, &B);

    assert((res == 0));
    printf("Success\n");

}

void Test_InsertWorker_PushForward_ValidValN8() {
    printf("Test 8:PushForward\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 1;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";


    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker= &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = InsertWorker(Head, Curr);

    assert((Head->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Head->NextWorker);
    free(Head);
}

void Test_InsertWorker_PushBack_ValidValN9() {
    printf("Test 9:PushBack\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 7;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = InsertWorker(Head, Curr);

    assert((Head->NextWorker->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_InsertWorker_Insert_ValidValN10() {
    printf("Test 10:Insert\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 2;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = InsertWorker(Head, Curr);

    assert((Head->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_InsertSort_NULLStaff_ReturnNULLN11() {
    printf("Test 11:NULLStaff\n");

    Staff* Head = NULL;

    Head = InsertSort(Head);

    assert((Head == NULL));
    printf("Returned NULL. Error:NULL Staff\n");
}

void Test_InsertSort_SortedStaff_ValidValN12() {
    printf("Test 12:SortedStaff\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 2;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 3;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    Head = InsertSort(Head);

    assert((Head->CurrWorker == &A) && (Head->NextWorker->CurrWorker == &B) && (Head->NextWorker->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_InsertSort_RandStaff_ValidValN13() {
    printf("Test 13:RandStaff\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 2;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    Head = InsertSort(Head);

    assert((Head->CurrWorker == &A) && (Head->NextWorker->CurrWorker == &C) && (Head->NextWorker->NextWorker->CurrWorker == &B));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_CreateWorker_NULLLines_ReturnNULLN14() {
    printf("Test 14:NULLLines\n");
    char* lines = NULL;
    Worker* res;
    res = CreateWorker(lines, 6, 1);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lines\n");
    free(res);
}

void Test_CreateWorker_NULLLen_ReturnNULLN15() {
    printf("Test 15:NULLLen\n");
    char* lines = "15.01.2024 Цой Мария 7";
    Worker* res;
    res = CreateWorker(lines, 0, 1);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL len\n");
    free(res);
}

void Test_CreateWorker_RandWorker_ValidValN16() {
    printf("Test 16:Worker\n");

    const char* lines = 
    "15.01.2024 Цой Мария 7\n";
    int i = 0;
    int len = 21;
    Worker A;
    A.day = 15;
    A.hours = 7;
    A.month = 1;
    A.name = "Мария";
    A.surname = "Цой";
    A.year = 2024;
    Worker* res;
    res = CreateWorker(lines, len, &i);

    assert((A.day == res->day) && (A.month == res->month) && (A.year == res->year) && (A.hours == res->hours) && (strcmp(A.name, res->name) == 0) && (strcmp(A.surname, res->surname) == 0));
    printf("Success\n");
    free(res->name);
    free(res->surname);
    free(res);
}

void Test_CreateStaff_NULLLines_ReturnNULLN17() {
    printf("Test 17:NULLLines\n");
    char* lines = NULL;
    int len = 21;
    Staff* res;
    res = CreateStaff(lines, len);

    assert(res == NULL);
    printf("Returned NULL. NULL Lines\n");
}

void Test_CreateStaff_RandStaff_ValidValN18() {
    printf("Test 18:RandStaff\n");
    char* lines = "15.01.2024 Цой Мария 7\n03.01.2024 Хагэнэдзука Иван 7";
    int len = 76;
    Staff* res;
    Worker A;
    Worker B;
    A.day = 15; B.day = 3;
    A.month = 1; B.month = 1;
    A.year = 2024; B.year = 2024;
    A.name = "Мария"; B.name = "Иван";
    A.surname = "Цой"; B.surname = "Хагэнэдзука";
    A.hours = 7; B.hours = 7;
    res = CreateStaff(lines, len);

    assert((strcmp(res->CurrWorker->surname,A.surname)==0)&&(strcmp(res->NextWorker->CurrWorker->surname,B.surname)==0));
    printf("Success\n");
    FreeStaff(res);
}

void Test_ReadOneData_NULLLines_ReturnNULLN19() {
    printf("Test 19:NULLLines\n");
    char* lines = "NULL";
    int i = 0;
    int l = 0;
    char* res = ReadOneData(lines, 0, &i, &l, ' ');

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lines\n");
    FreeStaff(res);
}

void Test_ReadOneData_NoEndChar_ReturnNULLN20() {
    printf("Test 20:NoEndChar\n");
    char* lines = "15.01.2024 Цой Мария 7\n03.01.2024 Хагэнэдзука Иван 7";
    int i = 0;
    int l = 0;
    char* res = ReadOneData(lines, 0, &i, &l, '/');

    assert(res == NULL);
    printf("Returned NULL. Error:There is no EndChar in lines\n");
}

void Test_ReadOneData_ReadData_ValidValN21() {
    printf("Test 21:ReadData\n");
    char* lines = "15.01.2024 Цой Мария 7\n03.01.2024 Хагэнэдзука Иван 7";
    int i = 0;
    int l = 0;
    char* res = ReadOneData(lines, 76, &i, &l, '.');

    assert(strcmp(res,"15")==0);
    printf("Success\n");
    free(res);
}

void Test_Print_NoNonePtinted_ReturnFalseN22() {
    printf("Test 22:NoNonePtinted\n");


    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.hours = 2;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.hours = 3;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    res = PrintStaff(Head, 7);

    assert((res == 0));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_Print_NULLStaff_ReturnFalseN23() {
    printf("Test 23:NULLStaff\n");

    Staff* Head = NULL;
    int res;

    res = PrintStaff(Head, 7);

    assert((res == 0));
    printf("Success\n");
}

void Test_Print_WorkersPtinted_ReturnTrueN24() {
    printf("Test 24:WorkersPtinted\n");

    Worker A;
    Worker B;
    Worker C;
    int res;

    A.day = 1;
    A.year = 2024;
    A.hours = 1;
    A.month = 5;
    A.name = "Иван";
    A.surname = "Цой";

    B.day = 4;
    B.year = 2024;
    B.hours = 2;
    B.month = 2;
    B.name = "Лаврентий";
    B.surname = "Хагэнэдзука";

    C.day = 4;
    C.year = 2024;
    C.hours = 3;
    C.month = 2;
    C.name = "Ф";
    C.surname = "К";

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    res = PrintStaff(Head, 1);

    assert((res == 1));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

int main(void) {

    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_FromStr2Num_AlphaDigitString_ReturnNULLN1();
    Test_FromStr2Num_DigitString_ReturnNUMN2();
    Test_IfSameWorker_DifferentWorkers_ReturnTrueN3();
    Test_IfSameWorker_DifferentWorkers_ReturnFalseN4();
    Test_WorkerCmp_DifferentWorkers_ReturnTrueN5();
    Test_WorkerCmp_DifferentWorkers_ReturnFalseN6();
    Test_WorkerCmp_DifferentWorkers_ReturnFalseN7();
    Test_InsertWorker_PushForward_ValidValN8();
    Test_InsertWorker_PushBack_ValidValN9();
    Test_InsertWorker_Insert_ValidValN10();
    Test_InsertSort_NULLStaff_ReturnNULLN11();
    Test_InsertSort_SortedStaff_ValidValN12(); 
    Test_InsertSort_RandStaff_ValidValN13();
    Test_CreateWorker_NULLLines_ReturnNULLN14();
    Test_CreateWorker_NULLLen_ReturnNULLN15(); 
    Test_CreateWorker_RandWorker_ValidValN16();
    Test_CreateStaff_NULLLines_ReturnNULLN17();
    Test_CreateStaff_RandStaff_ValidValN18();
    Test_ReadOneData_NULLLines_ReturnNULLN19();
    Test_ReadOneData_NoEndChar_ReturnNULLN20();
    Test_ReadOneData_ReadData_ValidValN21();
    Test_Print_NoNonePtinted_ReturnFalseN22();
    Test_Print_NULLStaff_ReturnFalseN23();
    Test_Print_WorkersPtinted_ReturnTrueN24();

    return 0;
}
