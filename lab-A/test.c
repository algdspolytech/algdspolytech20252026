#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labA19.h"

//Вспомогательные функции

//Конвертация списка в строку (через пробел)
void ListToString(Node* head, char* buffer, size_t size) {
    buffer[0] = '\0';
    while (head) {
        strcat_s(buffer, size, head->data);
        if (head->next)
            strcat_s(buffer, size, " ");
        head = head->next;
    }
}

//Проверка равенства строк
void expect(const char* testName,
    const char* got,
    const char* expected) {
    if (strcmp(got, expected) == 0) {
        printf("OK %s\n", testName);
    }
    else {
        printf("FAIL %s\n", testName);
        printf("expected:\"%s\"\n", expected);
        printf("got:\"%s\"\n", got);
    }
}

//Проверка на пустоту списка
void expectNull(const char* testName, Node* got) {
    if (got == NULL) {
        printf("OK %s\n", testName);
    }
    else {
        printf("FAIL  %s\n", testName);
    }
}

//Тесты

//1.Добавление в пустой список
void test_AddToEmptyList_no1() {
    Node* head = NULL;
    head = push(head, "dog");
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("AddToEmptyList_no1", buffer, "dog");
}

//2.Добавление в список с одним элементом
void test_AddToSingleElementList_no2() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "giraffe");
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("AddToSingleElementList_no2", buffer, "giraffe dog");
}

//3.Добавление нескольких элементов
void test_AddMultipleElements_no3() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "giraffe");
    head = push(head, "elefant");
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("AddMultipleElements_no3", buffer, "elefant giraffe dog");
}

//4.Удаление единственного элемента
void test_DeleteSingleElement_no4() {
    Node* head = NULL;
    head = push(head, "cat");
    head = deletenode(head, "cat");
    expectNull("DeleteSingleElement_no4", head);
}

//5.Удаление первого элемента
void test_DeleteFirstElement_no5() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "cat");
    head = deletenode(head, "bigdog");
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("DeleteFirstElement_no5", buffer, "cat dog");
}

//6.Удаление несуществующего элемента
void test_DeleteNonExistingElement_no6() {
    Node* head = NULL;
    head = push(head, "river");
    head = deletenode(head, "sea");
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("DeleteNonExistingElement_no6", buffer, "river");
}

//7.Сортировка пустого списка
void test_SortEmptyList_no7() {
    Node* head = NULL;
    head = mergeSort(head);
    expectNull("SortEmptyList_no7", head);
}

//8.Сортировка одного элемента
void test_SortSingleElement_no8() {
    Node* head = NULL;
    head = push(head, "smile");
    head = mergeSort(head);
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("SortSingleElement_no8", buffer, "smile");
}

//9.Сортировка нескольких элементов
void test_SortMultipleElements_no9() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "cat");
    head = push(head, "pig");
    head = mergeSort(head);
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("SortMultipleElements_no9", buffer, "cat dog pig");
}

//10.Сортировка с повторяющимися элементами
void test_SortWithDuplicates_no10() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "august");
    head = push(head, "dog");
    head = mergeSort(head);
    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("SortWithDuplicates_no10", buffer, "august dog dog");
}
//11.Сортировка с разными символами
void test_SortMixedSymbols_no11() {
    Node* head = NULL;
    head = push(head, "dog");
    head = push(head, "123");
    head = push(head, "@cat");
    head = push(head, "!cow)");

    head = mergeSort(head);

    char buffer[128];
    ListToString(head, buffer, sizeof(buffer));
    expect("SortMixedSymbols_no11", buffer, "!cow) 123 @cat dog");
}

int main() {
    test_AddToEmptyList_no1();
    test_AddToSingleElementList_no2();
    test_AddMultipleElements_no3();
    test_DeleteSingleElement_no4();
    test_DeleteFirstElement_no5();
    test_DeleteNonExistingElement_no6();
    test_SortEmptyList_no7();
    test_SortSingleElement_no8();
    test_SortMultipleElements_no9();
    test_SortWithDuplicates_no10();
    test_SortMixedSymbols_no11();
    return 0;
}