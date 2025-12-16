#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concat_strings.h"

#ifdef _WIN32
#ifndef strdup
#define strdup _strdup
#endif
#endif



// Ïðîâåðêà ñòðîê
#define ASSERT_STR_EQ(expected, actual, test_name) \
    do { \
        if (strcmp(expected, actual) != 0) { \
            char* msg = malloc(1024); \
            snprintf(msg, 1024, "FAILED: %s - Expected: '%s', Got: '%s'", test_name, expected, actual); \
            return msg; \
        } \
    } while(0)

// Ïðîâåðêà ïóñòîé ñòðîêè
#define ASSERT_EMPTY(actual, test_name) \
    do { \
        if (strcmp("", actual) != 0) { \
            char* msg = malloc(1024); \
            snprintf(msg, 1024, "FAILED: %s - Expected empty string, Got: '%s'", test_name, actual); \
            return msg; \
        } \
    } while(0)

// Çàïóñê òåñòà ñ ïðîâåðêîé
#define RUN_TEST(test_func) \
    do { \
        printf("Running %s... ", #test_func); \
        char* failure_message = test_func(); \
        if (failure_message) { \
            printf("FAILED\n"); \
            printf("  %s\n", failure_message); \
            free(failure_message); \
            failures++; \
        } else { \
            printf("PASSED\n"); \
        } \
    } while(0)



// Ôóíêöèÿ äëÿ ñîçäàíèÿ óçëà
Node* create_node(const char* str) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = strdup(str);
    node->next = NULL;
    return node;
}

// Ôóíêöèÿ äëÿ ñîçäàíèÿ ñïèñêà
Node* create_list(const char** strings, int count) {
    if (count == 0) return NULL;

    Node* head = create_node(strings[0]);
    Node* current = head;
    for (int i = 1; i < count; ++i) {
        current->next = create_node(strings[i]);
        current = current->next;
    }
    return head;
}

// Îñâîáîæäåíèå ïàìÿòè ñïèñêà
void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}



// Òåñò 1: Ïóñòîé ñïèñîê
char* test_empty_list_no1() {
    Node* head = NULL;
    char* result = concat_strings(head);
    ASSERT_EMPTY(result, "test_empty_list_no1");
    free(result);
    return NULL;
}

// Òåñò 2: Îäèí óçåë ñ ïóñòîé ñòðîêîé
char* test_single_empty_node_no2() {
    const char* strings[] = { "" };
    Node* head = create_list(strings, 1);
    char* result = concat_strings(head);
    ASSERT_EMPTY(result, "test_single_empty_node_no2");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 3: Îäèí óçåë ñ îáû÷íîé ñòðîêîé
char* test_single_node_no3() {
    const char* strings[] = { "hello" };
    Node* head = create_list(strings, 1);
    char* result = concat_strings(head);
    ASSERT_STR_EQ("hello", result, "test_single_node_no3");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 4: Íåñêîëüêî óçëîâ áåç ïóñòûõ ñòðîê
char* test_multiple_nodes_no4() {
    const char* strings[] = { "Hello", " ", "World", "!" };
    Node* head = create_list(strings, 4);
    char* result = concat_strings(head);
    ASSERT_STR_EQ("Hello World!", result, "test_multiple_nodes_no4");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 5: Íåñêîëüêî óçëîâ ñ ïóñòûìè ñòðîêàìè â ñåðåäèíå
char* test_with_empty_middle_no5() {
    const char* strings[] = { "Hello", "", "World" };
    Node* head = create_list(strings, 3);
    char* result = concat_strings(head);
    ASSERT_STR_EQ("HelloWorld", result, "test_with_empty_middle_no5");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 6: Âñå óçëû ñ ïóñòûìè ñòðîêàìè
char* test_all_empty_nodes_no6() {
    const char* strings[] = { "", "", "" };
    Node* head = create_list(strings, 3);
    char* result = concat_strings(head);
    ASSERT_EMPTY(result, "test_all_empty_nodes_no6");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 7: Îäèí óçåë ñ äëèííîé ñòðîêîé
char* test_long_string_no7() {
    char* longStr = malloc(1001);
    memset(longStr, 'A', 1000);
    longStr[1000] = '\0';
    const char* strings[] = { longStr };
    Node* head = create_list(strings, 1);
    char* result = concat_strings(head);
    ASSERT_STR_EQ(longStr, result, "test_long_string_no7");
    free(result);
    free_list(head);
    free(longStr);
    return NULL;
}

// Òåñò 8: Ìíîãî êîðîòêèõ ñòðîê
char* test_many_short_strings_no8() {
    const char* x = "x";
    char** strings = malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; ++i) {
        strings[i] = "x";
    }
    Node* head = create_list((const char**)strings, 100);
    char* result = concat_strings(head);
    char* expected = malloc(101);
    memset(expected, 'x', 100);
    expected[100] = '\0';
    ASSERT_STR_EQ(expected, result, "test_many_short_strings_no8");
    free(result);
    free_list(head);
    free(expected);
    free(strings);
    return NULL;
}

// Òåñò 9: Ñòðîêà ñ ñèìâîëàìè ïåðåâîäà ñòðîêè è òàáóëÿöèè
char* test_special_chars_no9() {
    const char* strings[] = { "\n", "\t", "\\", "\"" };
    Node* head = create_list(strings, 4);
    char* result = concat_strings(head);
    ASSERT_STR_EQ("\n\t\\\"", result, "test_special_chars_no9");
    free(result);
    free_list(head);
    return NULL;
}

// Òåñò 10: Ïîâòîðÿþùèåñÿ ñòðîêè
char* test_repeated_strings_no10() {
    const char* strings[] = { "test", "test", "test" };
    Node* head = create_list(strings, 3);
    char* result = concat_strings(head);
    ASSERT_STR_EQ("testtesttest", result, "test_repeated_strings_no10");
    free(result);
    free_list(head);
    return NULL;
}

int main() {
    int failures = 0;

    RUN_TEST(test_empty_list_no1);
    RUN_TEST(test_single_empty_node_no2);
    RUN_TEST(test_single_node_no3);
    RUN_TEST(test_multiple_nodes_no4);
    RUN_TEST(test_with_empty_middle_no5);
    RUN_TEST(test_all_empty_nodes_no6);
    RUN_TEST(test_long_string_no7);
    RUN_TEST(test_many_short_strings_no8);
    RUN_TEST(test_special_chars_no9);
    RUN_TEST(test_repeated_strings_no10);

    if (failures > 0) {
        printf("\n%d test(s) failed.\n", failures);
        return 1;
    }
    else {
        printf("\nAll tests passed!\n");
        return 0;
    }
}