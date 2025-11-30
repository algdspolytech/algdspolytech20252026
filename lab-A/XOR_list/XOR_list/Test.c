#include "Functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<assert.h>
#pragma warning(disable: 4996);

void Test_FindLength_String_ReturnZero() {
    printf("Test 1: Empty string\n");


    char string[] = "\0";


    int res = FindLength(string);


    assert((res == 0));
    printf("Success!\n\n");
}

void Test_FindLength_String_Return3() {
    printf("Test 2: Not empty string\n");


    char string[] = "abc\0";


    int res = FindLength(string);


    assert((res == 3));
    printf("Success!\n\n");
}

void Test_KeysCompare_TwoStrings_ReturnTrue() {
    printf("Test 3: Identical strings\n");

    char string1[] = "test\0";
    char string2[] = "test\0";


    int res = KeysCompare(string1, string2);


    assert((res == 1));
    printf("Success!\n\n");
}


void Test_KeysCompare_TwoStrings_ReturnFalse() {
    printf("Test 4: Different strings\n");

    char string1[] = "Test\0";
    char string2[] = "test\0";


    int res = KeysCompare(string1, string2);


    assert((res == 0));
    printf("Success!\n\n");
}


void Test_XORListInit_ThreeStrings_ReturnCorrectXORList() {
    printf("Test 5: Correct initialization\n");


    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";

    char* String1 = (char*)malloc(sizeof(char) * 6);
    char* String2 = (char*)malloc(sizeof(char) * 6);
    char* String3 = (char*)malloc(sizeof(char) * 6);

    strcpy(String1, string1);
    strcpy(String2, string2);
    strcpy(String3, string3);



    XOR_list res = XORListInit(String1, String2, String3);
    XOR_node* res2 = (XOR_node*)(res.start->link);
    XOR_node* res3 = (XOR_node*)((uintptr_t)res.start ^ res2->link);


    assert(KeysCompare(res.start->string, String1) == 1 && KeysCompare(res2->string, String2) == 1 && KeysCompare(res3->string, String3) == 1);
    printf("Success!\n\n");
}

void Test_XORListAdd_OneString_AddedToEnd() {
    printf("Test 6: Add node to end of list\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char newString[] = "newNode";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);
    char* newStr = (char*)malloc(sizeof(char) * 8);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);
    strcpy(newStr, newString);

    XOR_list list = XORListInit(str1, str2, str3);
    XORListAdd(list, newStr);

    // Traverse to verify addition
    XOR_node* first = list.start;
    XOR_node* second = (XOR_node*)first->link;
    XOR_node* third = (XOR_node*)((uintptr_t)first ^ second->link);
    XOR_node* fourth = (XOR_node*)((uintptr_t)second ^ third->link);

    assert(KeysCompare(fourth->string, newStr) == 1);
    printf("Success!\n\n");
}

void Test_XORListDeleteByKey_FirstNode_Deleted() {
    printf("Test 7: Delete first node by key\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "test1";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    XORListDeleteByKey(&list, key);

    assert(KeysCompare(list.start->string, str2) == 1);
    printf("Success!\n\n");
}

void Test_XORListDeleteByKey_MiddleNode_Deleted() {
    printf("Test 8: Delete middle node by key\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "test2";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    XORListDeleteByKey(&list, key);

    XOR_node* first = list.start;
    XOR_node* second = (XOR_node*)first->link;

    assert(KeysCompare(first->string, str1) == 1);
    assert(KeysCompare(second->string, str3) == 1);
    printf("Success!\n\n");
}

void Test_XORListDeleteByKey_LastNode_Deleted() {
    printf("Test 9: Delete last node by key\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "test3";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    XORListDeleteByKey(&list, key);

    XOR_node* first = list.start;
    XOR_node* second = (XOR_node*)first->link;

    assert(KeysCompare(first->string, str1) == 1);
    assert(KeysCompare(second->string, str2) == 1);
    assert(second->link = (uintptr_t)first);
    printf("Success!\n\n");
}

void Test_XORListDeleteByKey_NonExistentKey_NoChange() {
    printf("Test 10: Delete non-existent key - no change\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "nonexistent";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    XORListDeleteByKey(&list, key);

    XOR_node* first = list.start;
    XOR_node* second = (XOR_node*)first->link;
    XOR_node* third = (XOR_node*)((uintptr_t)first ^ second->link);

    assert(KeysCompare(first->string, str1) == 1);
    assert(KeysCompare(second->string, str2) == 1);
    assert(KeysCompare(third->string, str3) == 1);
    printf("Success!\n\n");
}

void Test_XORListDeleteByAddress_FirstNode_Deleted() {
    printf("Test 11: Delete first node by address\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    uintptr_t targetAddr = (uintptr_t)list.start;
    XORListDeleteByAdress(&list, targetAddr);

    assert(KeysCompare(list.start->string, str2) == 1);
    printf("Success!\n\n");
}

void Test_XORListDeleteByAddress_MiddleNode_Deleted() {
    printf("Test 12: Delete middle node by address\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    uintptr_t targetAddr = (uintptr_t)((XOR_node*)list.start->link);
    XORListDeleteByAdress(&list, targetAddr);

    XOR_node* first = list.start;
    XOR_node* second = (XOR_node*)first->link;

    assert(KeysCompare(first->string, str1) == 1);
    assert(KeysCompare(second->string, str3) == 1);
    printf("Success!\n\n");
}

void Test_FindByKey_ExistingKey_ReturnsCorrectAddress() {
    printf("Test 13: Find existing key returns correct address\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "test2";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    uintptr_t foundAddr = FindByKey(&list, key);

    uintptr_t secondNode = list.start->link;
    assert(foundAddr == secondNode);
    printf("Success!\n\n");
}

void Test_FindByKey_FirstKey_ReturnsCorrectAddress() {
    printf("Test 14: Find first key returns correct address\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";
    char key[] = "test1";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    uintptr_t foundAddr = FindByKey(&list, key);

    assert(foundAddr == (uintptr_t)list.start);
    printf("Success!\n\n");
}

void Test_FindByKey_NonExistentKey_ReturnsNULL() {
    printf("Test 15: Find non-existent key returns NULL\n");

    char string1[] = "test1";
    char string2[] = "test2";
    char string3[] = "test3";

    char key[] = "nonexistent";

    char* str1 = (char*)malloc(sizeof(char) * 6);
    char* str2 = (char*)malloc(sizeof(char) * 6);
    char* str3 = (char*)malloc(sizeof(char) * 6);

    strcpy(str1, string1);
    strcpy(str2, string2);
    strcpy(str3, string3);

    XOR_list list = XORListInit(str1, str2, str3);
    uintptr_t foundAddr = FindByKey(&list, key);

    assert(foundAddr == NULL);
    printf("Success!\n\n");
}






int main() {

    Test_FindLength_String_ReturnZero();
    Test_FindLength_String_Return3();
    Test_KeysCompare_TwoStrings_ReturnTrue();
    Test_KeysCompare_TwoStrings_ReturnFalse();
    Test_XORListInit_ThreeStrings_ReturnCorrectXORList();


    Test_XORListAdd_OneString_AddedToEnd();
    Test_XORListDeleteByKey_FirstNode_Deleted();
    Test_XORListDeleteByKey_MiddleNode_Deleted();
    Test_XORListDeleteByKey_LastNode_Deleted();
    Test_XORListDeleteByKey_NonExistentKey_NoChange();
    Test_XORListDeleteByAddress_FirstNode_Deleted();
    Test_XORListDeleteByAddress_MiddleNode_Deleted();
    Test_FindByKey_ExistingKey_ReturnsCorrectAddress();
    Test_FindByKey_FirstKey_ReturnsCorrectAddress();
    Test_FindByKey_NonExistentKey_ReturnsNULL();

    return 0;
}




