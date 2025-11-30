#pragma once
#include<stdint.h>


typedef struct {
	char* string;

	uintptr_t link;

} XOR_node;

typedef struct {

	XOR_node* start;

} XOR_list;

int FindLength(char* string);

int KeysCompare(char* firstString, char* secondString);

XOR_list XORListInit(char* firstString, char* secondString, char* thirdString);

void XORListAdd(XOR_list list, char* string);

void XORListDeleteByKey(XOR_list* list, char* key);

void XORListDeleteByAdress(XOR_list* list, uintptr_t adress);

uintptr_t FindByKey(XOR_list* list, char* key);






