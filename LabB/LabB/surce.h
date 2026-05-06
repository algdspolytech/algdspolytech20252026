#pragma once
#include <stdio.h>

typedef struct block {
	size_t size;
	int isFree;
	struct block* next;
	struct block* previous;
} BlockT;

int areEq(BlockT block1, BlockT block2);

#define BUFFER_SIZE 1024
static char buffer[BUFFER_SIZE];
static BlockT* memoryBlocks = NULL;
static int isInit = 0;

void memoryInit();
void splitBlock(BlockT* current, size_t size);
void mergeBlocks(BlockT* current);

void* myMalloc(size_t size);
void myFree(void* ptr);
