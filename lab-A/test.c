// test.c
/**
 * @file test.c
 * @brief Файл тестирования функций
 *
 * @version 1.0
 * @date 2025.12.20
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include <assert.h> 
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "phonebook.h" 

 // Вспомогательная функция для настройки локали в тестах
void SetupRussianLocale() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void Test_StrDup_ValidString_ReturnsCorrectCopy_N1() {
    printf("Test 1: Valid string duplication\n");

    const char* original = "TestString";
    char* copy = StrDup(original);

    assert(copy != NULL);
    assert(strcmp(original, copy) == 0);
    assert(original != copy);

    free(copy);
    printf("Success\n");
}

void Test_StrDup_CyrillicString_ReturnsCorrectCopy_N2() {
    printf("Test 2: Cyrillic string duplication\n");

    const char* original = "Кузнецов";
    char* copy = StrDup(original);

    assert(copy != NULL);
    assert(strcmp(original, copy) == 0);
    assert(original != copy);

    free(copy);
    printf("Success\n");
}

void Test_StrDup_EmptyString_ReturnsEmptyString_N3() {
    printf("Test 3: Empty string duplication\n");

    const char* original = "";
    char* copy = StrDup(original);

    assert(copy != NULL);
    assert(strcmp(original, copy) == 0);

    free(copy);
    printf("Success\n");
}

void Test_StrDup_NULLString_ReturnsNULL_N4() {
    printf("Test 4: NULL string duplication\n");

    char* copy = StrDup(NULL);

    assert(copy == NULL);
    printf("Success\n");
}

void Test_CreateNode_ValidCyrillicData_ReturnsCorrectNode_N5() {
    printf("Test 5: Create node with valid Cyrillic data\n");

    const char* ln = "Кузнецов";
    const char* fn = "Александр";
    const char* pn = "Алексеевич";

    Node* node = CreateNode(ln, fn, pn);

    assert(node != NULL);
    assert(strcmp(node->lastName, ln) == 0);
    assert(strcmp(node->firstName, fn) == 0);
    assert(strcmp(node->patronymic, pn) == 0);
    assert(node->next == NULL);

    FreeList(node);
    printf("Success\n");
}

void Test_CreateNode_MixedCyrillicNames_ReturnsCorrectNode_N6() {
    printf("Test 6: Create node with mixed Cyrillic names\n");

    const char* ln = "Соколова";
    const char* fn = "Анна";
    const char* pn = "Михайловна";

    Node* node = CreateNode(ln, fn, pn);

    assert(node != NULL);
    assert(strcmp(node->lastName, ln) == 0);
    assert(strcmp(node->firstName, fn) == 0);
    assert(strcmp(node->patronymic, pn) == 0);

    FreeList(node);
    printf("Success\n");
}

void Test_CreateNode_NULLData_ReturnsNULL_N7() {
    printf("Test 7: Create node with NULL data\n");

    Node* node = CreateNode(NULL, "Иван", "Иванович");

    assert(node == NULL);
    printf("Success\n");
}

void Test_PersonCompare_EqualCyrillicPersons_ReturnsZero_N8() {
    printf("Test 8: Compare equal Cyrillic persons\n");

    Node a = { "Кузнецов", "Александр", "Алексеевич", NULL };
    Node b = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = PersonCompare(&a, &b);

    assert(result == 0);
    printf("Success\n");
}

void Test_PersonCompare_DifferentCyrillicLastName_ReturnsNonZero_N9() {
    printf("Test 9: Compare persons with different Cyrillic last names\n");

    Node a = { "Андреев", "Александр", "Алексеевич", NULL };
    Node b = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = PersonCompare(&a, &b);

    assert(result < 0); // "Андреев" < "Кузнецов" в алфавитном порядке
    printf("Success\n");
}

void Test_PersonCompare_SameLastNameDifferentCyrillicFirstName_ReturnsNonZero_N10() {
    printf("Test 10: Compare persons with same last name, different Cyrillic first name\n");

    Node a = { "Кузнецов", "Александр", "Алексеевич", NULL };
    Node b = { "Кузнецов", "Алексей", "Владимирович", NULL };

    int result = PersonCompare(&a, &b);

    assert(result < 0); // "Александр" < "Алексей"
    printf("Success\n");
}

void Test_PersonCompare_SameNamesDifferentPatronymic_ReturnsNonZero_N11() {
    printf("Test 11: Compare persons with same names, different Cyrillic patronymic\n");

    Node a = { "Кузнецов", "Александр", "Алексеевич", NULL };
    Node b = { "Кузнецов", "Александр", "Борисович", NULL };

    int result = PersonCompare(&a, &b);

    assert(result < 0); // "Алексеевич" < "Борисович"
    printf("Success\n");
}

void Test_InsertSortion_EmptyList_InsertsCyrillicNode_N12() {
    printf("Test 12: Insert Cyrillic node into empty list\n");

    Node* head = NULL;
    Node* node = CreateNode("Кузнецов", "Александр", "Алексеевич");

    InsertSortion(&head, node);

    assert(head == node);
    assert(head->next == NULL);

    FreeList(head);
    printf("Success\n");
}

void Test_InsertSortion_MultipleCyrillicNodes_SortsCorrectly_N13() {
    printf("Test 13: Insert multiple Cyrillic nodes, check sorting order\n");

    Node* head = NULL;

    // Создаем узлы в разном порядке
    Node* node1 = CreateNode("Кузнецов", "Алексей", "Владимирович");
    Node* node2 = CreateNode("Соколова", "Анна", "Михайловна");
    Node* node3 = CreateNode("Кузнецов", "Александр", "Дмитриевич");
    Node* node4 = CreateNode("Кузнецов", "Александр", "Алексеевич");
    Node* node5 = CreateNode("Кузнецов", "Борис", "Александрович");
    Node* node6 = CreateNode("Кузнецов", "Александр", "Борисович");

    // Вставляем в произвольном порядке
    InsertSortion(&head, node1);
    InsertSortion(&head, node2);
    InsertSortion(&head, node3);
    InsertSortion(&head, node4);
    InsertSortion(&head, node5);
    InsertSortion(&head, node6);

    // Проверяем порядок сортировки (по алфавиту):
    // 1. Кузнецов Александр Алексеевич
    // 2. Кузнецов Александр Борисович
    // 3. Кузнецов Александр Дмитриевич
    // 4. Кузнецов Алексей Владимирович
    // 5. Кузнецов Борис Александрович
    // 6. Соколова Анна Михайловна

    assert(head == node4); // Кузнецов Александр Алексеевич
    assert(head->next == node6); // Кузнецов Александр Борисович
    assert(head->next->next == node3); // Кузнецов Александр Дмитриевич
    assert(head->next->next->next == node1); // Кузнецов Алексей Владимирович
    assert(head->next->next->next->next == node5); // Кузнецов Борис Александрович
    assert(head->next->next->next->next->next == node2); // Соколова Анна Михайловна
    assert(head->next->next->next->next->next->next == NULL);

    FreeList(head);
    printf("Success\n");
}

void Test_InsertSortion_CyrillicInsertAtBeginning_InsertsCorrectly_N14() {
    printf("Test 14: Insert Cyrillic node at beginning of list\n");

    Node* head = NULL;
    Node* node1 = CreateNode("Петров", "Петр", "Петрович");
    Node* node2 = CreateNode("Андреев", "Андрей", "Андреевич");

    InsertSortion(&head, node1);
    InsertSortion(&head, node2); // Андреев должен быть первым

    assert(head == node2);
    assert(head->next == node1);
    assert(node1->next == NULL);

    FreeList(head);
    printf("Success\n");
}

void Test_InsertSortion_CyrillicInsertAtEnd_InsertsCorrectly_N15() {
    printf("Test 15: Insert Cyrillic node at end of list\n");

    Node* head = NULL;
    Node* node1 = CreateNode("Андреев", "Андрей", "Андреевич");
    Node* node2 = CreateNode("Иванов", "Иван", "Иванович");
    Node* node3 = CreateNode("Петров", "Петр", "Петрович");

    InsertSortion(&head, node1);
    InsertSortion(&head, node2);
    InsertSortion(&head, node3); // Петров в конец

    assert(head == node1);
    assert(head->next == node2);
    assert(head->next->next == node3);
    assert(node3->next == NULL);

    FreeList(head);
    printf("Success\n");
}

void Test_StartsWith_CyrillicPrefixMatches_ReturnsOne_N16() {
    printf("Test 16: Cyrillic string starts with prefix\n");

    const char* str = "Кузнецов";
    const char* prefix = "Куз";

    int result = StartsWith(str, prefix);

    assert(result == 1);
    printf("Success\n");
}

void Test_StartsWith_CyrillicPrefixDoesNotMatch_ReturnsZero_N17() {
    printf("Test 17: Cyrillic string does not start with prefix\n");

    const char* str = "Кузнецов";
    const char* prefix = "Ива";

    int result = StartsWith(str, prefix);

    assert(result == 0);
    printf("Success\n");
}

void Test_StartsWith_CyrillicEmptyPrefix_ReturnsOne_N18() {
    printf("Test 18: Empty prefix with Cyrillic string\n");

    const char* str = "Кузнецов";
    const char* prefix = "";

    int result = StartsWith(str, prefix);

    assert(result == 1);
    printf("Success\n");
}

void Test_Match_AllDashPatternWithCyrillic_ReturnsOne_N19() {
    printf("Test 19: All dash pattern matches Cyrillic record\n");

    Node person = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = match(&person, "-", "-", "-");

    assert(result == 1);
    printf("Success\n");
}

void Test_Match_CyrillicLastNameMatches_ReturnsOne_N20() {
    printf("Test 20: Cyrillic last name matches\n");

    Node person = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = match(&person, "Куз", "-", "-");

    assert(result == 1);
    printf("Success\n");
}

void Test_Match_CyrillicLastNameDoesNotMatch_ReturnsZero_N21() {
    printf("Test 21: Cyrillic last name does not match\n");

    Node person = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = match(&person, "Ива", "-", "-");

    assert(result == 0);
    printf("Success\n");
}

void Test_Match_CyrillicFullMatch_ReturnsOne_N22() {
    printf("Test 22: Full Cyrillic match\n");

    Node person = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = match(&person, "Куз", "Алекс", "Алек");

    assert(result == 1);
    printf("Success\n");
}

void Test_Match_CyrillicPartialMatch_ReturnsOne_N23() {
    printf("Test 23: Partial Cyrillic match\n");

    Node person = { "Кузнецов", "Александр", "Алексеевич", NULL };

    int result = match(&person, "К", "А", "А");

    assert(result == 1);
    printf("Success\n");
}

void Test_Match_SearchByFirstNameOnly_ReturnsCorrectResults_N24() {
    printf("Test 24: Search by Cyrillic first name only\n");

    Node person1 = { "Кузнецов", "Александр", "Алексеевич", NULL };
    Node person2 = { "Иванов", "Алексей", "Иванович", NULL };
    Node person3 = { "Петров", "Петр", "Петрович", NULL };

    int result1 = match(&person1, "-", "Алекс", "-");
    int result2 = match(&person2, "-", "Алекс", "-");
    int result3 = match(&person3, "-", "Алекс", "-");

    assert(result1 == 1); // Александр начинается с Алекс
    assert(result2 == 1); // Алексей начинается с Алекс
    assert(result3 == 0); // Петр не начинается с Алекс

    printf("Success\n");
}

void Test_FreeList_NULLList_DoesNothing_N25() {
    printf("Test 25: Free NULL list\n");

    FreeList(NULL);

    printf("Success - no crash\n");
}

void Test_FreeList_CyrillicList_FreesMemory_N26() {
    printf("Test 26: Free Cyrillic list\n");

    Node* head = NULL;
    Node* node1 = CreateNode("Кузнецов", "Александр", "Алексеевич");
    Node* node2 = CreateNode("Соколова", "Анна", "Михайловна");

    InsertSortion(&head, node1);
    InsertSortion(&head, node2);

    FreeList(head);

    printf("Success - memory freed\n");
}

void Test_InsertSortion_CyrillicMiddleInsert_InsertsCorrectly_N27() {
    printf("Test 27: Insert Cyrillic node in middle of list\n");

    Node* head = NULL;
    Node* node1 = CreateNode("Андреев", "Андрей", "Андреевич");
    Node* node2 = CreateNode("Петров", "Петр", "Петрович");
    Node* node3 = CreateNode("Иванов", "Иван", "Иванович");

    InsertSortion(&head, node1); // Андреев
    InsertSortion(&head, node2); // Петров
    InsertSortion(&head, node3); // Иванов между Андреевым и Петровым

    assert(head == node1); // Андреев первый
    assert(head->next == node3); // Иванов второй
    assert(head->next->next == node2); // Петров третий
    assert(node2->next == NULL);

    FreeList(head);
    printf("Success\n");
}

void Test_SearchAndPrint_EmptyList_NoMatches_N28() {
    printf("Test 28: Search in empty Cyrillic list\n");

    Node* head = NULL;

    SearchAndPrint(head, "Иван", "Иван", "Иванович");

    printf("Success - no crash\n");
}


int main(void) {

    SetupRussianLocale();

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_StrDup_ValidString_ReturnsCorrectCopy_N1();
    Test_StrDup_CyrillicString_ReturnsCorrectCopy_N2();
    Test_StrDup_EmptyString_ReturnsEmptyString_N3();
    Test_StrDup_NULLString_ReturnsNULL_N4();
    Test_CreateNode_ValidCyrillicData_ReturnsCorrectNode_N5();
    Test_CreateNode_MixedCyrillicNames_ReturnsCorrectNode_N6();
    Test_CreateNode_NULLData_ReturnsNULL_N7();
    Test_PersonCompare_EqualCyrillicPersons_ReturnsZero_N8();
    Test_PersonCompare_DifferentCyrillicLastName_ReturnsNonZero_N9();
    Test_PersonCompare_SameLastNameDifferentCyrillicFirstName_ReturnsNonZero_N10();
    Test_PersonCompare_SameNamesDifferentPatronymic_ReturnsNonZero_N11();
    Test_InsertSortion_EmptyList_InsertsCyrillicNode_N12();
    Test_InsertSortion_MultipleCyrillicNodes_SortsCorrectly_N13();
    Test_InsertSortion_CyrillicInsertAtBeginning_InsertsCorrectly_N14();
    Test_InsertSortion_CyrillicInsertAtEnd_InsertsCorrectly_N15();
    Test_StartsWith_CyrillicPrefixMatches_ReturnsOne_N16();
    Test_StartsWith_CyrillicPrefixDoesNotMatch_ReturnsZero_N17();
    Test_StartsWith_CyrillicEmptyPrefix_ReturnsOne_N18();
    Test_Match_AllDashPatternWithCyrillic_ReturnsOne_N19();
    Test_Match_CyrillicLastNameMatches_ReturnsOne_N20();
    Test_Match_CyrillicLastNameDoesNotMatch_ReturnsZero_N21();
    Test_Match_CyrillicFullMatch_ReturnsOne_N22();
    Test_Match_CyrillicPartialMatch_ReturnsOne_N23();
    Test_Match_SearchByFirstNameOnly_ReturnsCorrectResults_N24();
    Test_FreeList_NULLList_DoesNothing_N25();
    Test_FreeList_CyrillicList_FreesMemory_N26();
    Test_InsertSortion_CyrillicMiddleInsert_InsertsCorrectly_N27();
    Test_SearchAndPrint_EmptyList_NoMatches_N28();

    printf("\nAll tests passed successfully!\n\n\n");

    printf("Основная программа: Записная книга\n");
    phonebook();
    return 0;
}