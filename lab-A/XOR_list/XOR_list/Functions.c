#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<assert.h>
#pragma warning(disable: 4996);

typedef struct {
	char* string;

	uintptr_t link;

} XOR_node;

typedef struct {
	
	XOR_node* start;

} XOR_list;



int FindLength(char* string) {
	int len = 0;

	while (string[len] != '\0') {
		len++;
	}

	return len;
}




int KeysCompare(char* firstString, char* secondString) {
	if (FindLength(firstString) != FindLength(secondString)) {
		return 0;
	}
	
	int i = 0;

	while (firstString[i] != '\0') {
		if (firstString[i] != secondString[i]) {
			return 0;
		}
		i++;
	}

	return 1;
}



XOR_list XORListInit(char* firstString, char* secondString, char* thirdString) {
	XOR_list XORList;


	XOR_node* firstNode = (XOR_node*)malloc(sizeof(XOR_node));
	XOR_node* secondNode = (XOR_node*)malloc(sizeof(XOR_node));
	XOR_node* thirdNode = (XOR_node*)malloc(sizeof(XOR_node));

	firstNode->string = firstString;
	secondNode->string = secondString;
	thirdNode->string = thirdString;


	firstNode->link = (uintptr_t)secondNode;
	secondNode->link = (uintptr_t)firstNode ^ (uintptr_t)thirdNode;
	thirdNode->link = (uintptr_t)secondNode;


	XORList.start = firstNode;
	return XORList;
}



void XORListAdd(XOR_list list, char* string) {
	XOR_node* newNode = (XOR_node*)malloc(sizeof(XOR_node));

	newNode->string = string;


	XOR_node* currentNode = (XOR_node*)list.start->link;
	XOR_node* nextNode = (XOR_node*)((uintptr_t)list.start ^ currentNode->link);
	XOR_node* buff;

	while ((uintptr_t)currentNode != nextNode->link) {
		buff = (XOR_node*)((uintptr_t)currentNode ^ nextNode->link);
		currentNode = nextNode;
		nextNode = buff;
	}


	nextNode->link = (uintptr_t)(currentNode) ^ (uintptr_t)(newNode);
	newNode->link = (uintptr_t)nextNode;
}



void XORListDeleteByKey(XOR_list* list, char* key) {
	XOR_node* buff;

	if (KeysCompare(list->start->string, key) == 1) {
		XOR_node* firstNode = list->start;
		XOR_node* secondNode = (XOR_node*)(firstNode->link);
		XOR_node* thirdNode = (XOR_node*)((uintptr_t)firstNode ^ secondNode->link);

		secondNode->link = (uintptr_t)thirdNode;
		list->start = secondNode;
		free(firstNode);
	}
	else {
		XOR_node* prevNode = list->start;
		XOR_node* currentNode = (XOR_node*)(prevNode->link);

		
		while (KeysCompare(currentNode->string, key) == 0 && prevNode != (XOR_node*)currentNode->link && prevNode != list->start) {
			buff = (XOR_node*)((uintptr_t)prevNode ^ currentNode->link);
			prevNode = currentNode;
			currentNode = buff;
		}

		if (KeysCompare(currentNode->string, key) == 1) {
			if (prevNode != (XOR_node*)currentNode->link) {
				XOR_node* nextNode = (XOR_node*)((uintptr_t)prevNode ^ currentNode->link);
				XOR_node* A = (XOR_node*)((uintptr_t)currentNode ^ prevNode->link);
				XOR_node* B = (XOR_node*)((uintptr_t)currentNode ^ nextNode->link);

				prevNode->link = (uintptr_t)A ^ (uintptr_t)nextNode;
				nextNode->link = (uintptr_t)prevNode ^ (uintptr_t)B;

				free(currentNode);
			}
			else {
				prevNode->link = (uintptr_t)currentNode ^ prevNode->link;
				free(currentNode);
			}
		}
	}
}



void XORListDeleteByAdress(XOR_list* list, uintptr_t adress) {
	XOR_node* buff;

	if ((uintptr_t)list->start == adress) {
		XOR_node* firstNode = list->start;
		XOR_node* secondNode = (XOR_node*)(firstNode->link);
		XOR_node* thirdNode = (XOR_node*)((uintptr_t)firstNode ^ secondNode->link);

		secondNode->link = (uintptr_t)thirdNode;
		list->start = secondNode;
		free(firstNode);
	}
	else {
		XOR_node* prevNode = list->start;
		XOR_node* currentNode = (XOR_node*)(prevNode->link);


		while ((uintptr_t)currentNode != adress && prevNode != (XOR_node*)currentNode->link && prevNode != list->start) {
			buff = (XOR_node*)((uintptr_t)prevNode ^ currentNode->link);
			prevNode = currentNode;
			currentNode = buff;
		}

		if ((uintptr_t)currentNode == adress) {
			if (prevNode != (XOR_node*)currentNode->link) {
				XOR_node* nextNode = (XOR_node*)((uintptr_t)prevNode ^ currentNode->link);
				XOR_node* A = (XOR_node*)((uintptr_t)currentNode ^ prevNode->link);
				XOR_node* B = (XOR_node*)((uintptr_t)currentNode ^ nextNode->link);

				prevNode->link = (uintptr_t)A ^ (uintptr_t)nextNode;
				nextNode->link = (uintptr_t)prevNode ^ (uintptr_t)B;

				free(currentNode);
			}
			else {
				prevNode->link = (uintptr_t)currentNode ^ prevNode->link;
				free(currentNode);
			}
		}
	}
}


uintptr_t FindByKey(XOR_list* list, char* key) {
	if (KeysCompare(list->start->string, key) == 1) {
		return (uintptr_t)(list->start);
	}
	else {
		XOR_node* currentNode = (XOR_node*)list->start->link;
		XOR_node* nextNode = (XOR_node*)((uintptr_t)list->start ^ currentNode->link);
		XOR_node* buff;

		while (nextNode->link != (uintptr_t)currentNode) {
			if (KeysCompare(currentNode->string, key) == 1) {
				return (uintptr_t)currentNode;
			}
			else {
				buff = nextNode;
				nextNode = (XOR_node*)((uintptr_t)currentNode ^ nextNode->link);
				currentNode = nextNode;
			}
		}
		if (KeysCompare(currentNode->string, key) == 1) {
			return (uintptr_t)currentNode;
		}
		else if (KeysCompare(nextNode->string, key) == 1) {
			return (uintptr_t)currentNode;
		}
		else {
			return NULL;
		}
	}


}


