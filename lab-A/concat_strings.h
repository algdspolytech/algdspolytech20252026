#pragma once

#ifndef CONCAT_STRINGS_H
#define CONCAT_STRINGS_H

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

char* concat_strings(Node* head);
#endif
