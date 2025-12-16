#define _CRT_SECURE_NO_WARNINGS

#include "concat_strings.h"
#include <stdlib.h>
#include <string.h>

char* concat_strings(Node* head) {
    if (!head) {
        char* result = malloc(1);
        result[0] = '\0';
        return result;
    }

    size_t total_len = 0;
    Node* current = head;

    while (current) {
        total_len += strlen(current->data);
        current = current->next;
    }

    char* result = malloc(total_len + 1);
    if (!result) return NULL;

    result[0] = '\0';
    current = head;

    while (current) {
        strcat(result, current->data);
        current = current->next;
    }

    return result;
}