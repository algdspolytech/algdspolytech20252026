#include "surce.h"


#ifdef __cplusplus
int mainOrig(){

#else
int main() {
#endif
	
	int* a = (int*)myMalloc(sizeof(int));
	*a = 1;
	myFree(a);
	return 1;
}

int areEq(BlockT block1, BlockT block2){
	return 
		block1.next == block2.next &&
		block1.previous == block2.previous &&
		block1.isFree == block2.isFree &&
		block1.size == block2.size;
}

void memoryInit() {
	if (isInit)
		return;

	memoryBlocks = (BlockT*)buffer;

	memoryBlocks->isFree = 1;
	memoryBlocks->size = sizeof(char) * BUFFER_SIZE - sizeof(BlockT);
	memoryBlocks->next = NULL;
	memoryBlocks->previous = NULL;
	isInit = 1;
}

void splitBlock(BlockT* current, size_t size) {
	if (!current->isFree || size < 1 || current->size - sizeof(BlockT) <= size)
		return;

	BlockT* next = (BlockT*)((char*)current + sizeof(BlockT) + size);
	
	next->previous = current;
	next->next = current->next;
	if (current->next) {
		BlockT* currentNext = current->next;
		currentNext->previous = next;
	}
	current->next = next;

	next->isFree = 1;
	next->size = current->size - size - sizeof(BlockT);
	current->size = size;
}

void mergeBlocks(BlockT* current) {
	if (!current->isFree)
		return;

	BlockT* next = current->next;
	if (next && next->isFree) {
		current->size += next->size + sizeof(BlockT);
		current->next = next->next;
		if (current->next) {
			BlockT* newNext = current->next;
			newNext->previous = current;
		}
	}

	BlockT* previous = current->previous;
	if (previous && previous->isFree) {
		current->size += previous->size + sizeof(BlockT);
		current->previous = previous->previous;
		if (current->previous) {
			BlockT* newPrevious = current->previous;
			newPrevious->next = current;
		}
	}
}

void* myMalloc(size_t size) {
	if (size <= 0)
		return NULL;

	memoryInit();
	BlockT* current = memoryBlocks;

	while (current && (!current->isFree || current->size - sizeof(BlockT) <= size))
		current = current->next;
	
	if (!current)
		return NULL;
	
	splitBlock(current, size);
	current->isFree = 0;
	return (void*)((char*)current + sizeof(BlockT));
}

void myFree(void* ptr) {
	BlockT* currentBlock = (BlockT*)((char*)ptr - sizeof(BlockT));
	if (currentBlock < memoryBlocks ||
		currentBlock >= (BlockT*)((char*)memoryBlocks + memoryBlocks->size))
		return;

	currentBlock->isFree = 1;
	mergeBlocks(currentBlock);
}
