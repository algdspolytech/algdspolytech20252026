#include "surce.h"

//the code is running from .cpp file (testing file)
#ifdef __cplusplus
int mainOrig() {

//the code is running from .c file (original file)
#else
int main() {
#endif

	NodeT* test = createMixedTree(4);
	NodeT* result = createHeightTree(test);

	printTree(result, 0, 1);

	freeTree(test);
	return 1;
}

void printTree(NodeT* tree, int dataSize, int indentation) {
	if (!tree)
		return;

	printTree(tree->right, dataSize, indentation + dataSize + TREE_SPACE_SIZE);

	for (int i = 0; i < indentation; i++)
		printf(" ");
	printf("%*i\n\n", dataSize, tree->data);
	
	printTree(tree->left, dataSize, indentation + dataSize + TREE_SPACE_SIZE);
}

int getMaxElement(NodeT* tree) {
	if (!tree)
		ERROR(TREE_PTR_IS_NULL);

	int result = tree->data;

	if (tree->left)
		result = (result > tree->left->data)? result : tree->left->data;
	if (tree->right)
		result = (result > tree->right->data) ? result : tree->right->data;

	return result;
}

NodeT* treeAbs(NodeT* tree) {
	if (!tree)
		return NULL;

	NodeT* result = createLeaf(abs(tree->data));
	result->left = treeAbs(tree->left);
	result->right = treeAbs(tree->left);

	return result;
}

int getHeight(NodeT* tree) {
	if (!tree)
		return 0;

	int result = 1;
	result += (getHeight(tree->left) > getHeight(tree->right)) ?
		getHeight(tree->left) : getHeight(tree->right);
	return result;
}

NodeT* createLeaf(int data) {
	NodeT* result = (NodeT*)malloc(sizeof(NodeT));
	if (!result)
		ERROR(NOT_ENOUGHT_MEMORY);

	result->data = data;
	result->left = NULL;
	result->right = NULL;
	return result;
}

NodeT* createDisbalancedElementaryTree(int size) {
	if (size < 0)
		ERROR(INCORECRT_TREE_SIZE);
	else if (size == 0)
		return NULL;

	NodeT* resultTree = createLeaf(1);

	NodeT* previousNode = resultTree;
	for (int i = 1; i < size; i++) {
		NodeT* currentNode = createLeaf(1);
		previousNode->left = currentNode;
		previousNode = currentNode;
	}
		
	return resultTree;
}

NodeT* createBalancedElementaryTree(int size) {
	if (size < 0)
		ERROR(INCORECRT_TREE_SIZE);
	else if (size == 0)
		return NULL;

	NodeT* result = createLeaf(1);
	if (size == 1)
		return result;

	result->left = createBalancedElementaryTree(size - 1);
	result->right = createBalancedElementaryTree(size - 1);
	return result;
}

NodeT* createMixedTree(int size){
	if (size < 0)
		ERROR(INCORECRT_TREE_SIZE);
	else if (size == 0)
		return NULL;

	NodeT* result = createLeaf(1);
	result->right = createBalancedElementaryTree(size - 1);
	result->left = createDisbalancedElementaryTree(size - 1);

	return result;
}

NodeT* createHeightTree(NodeT* tree) {
	if (!tree)
		return NULL;

	NodeT* result = createLeaf(abs(getHeight(tree->left) - getHeight(tree->right)));
	result->left = createHeightTree(tree->left);
	result->right = createHeightTree(tree->right);

	return result;
}

NodeT* createCopy(NodeT* tree) {
	if (!tree)
		return NULL;

	NodeT* result = createLeaf(tree->data);
	result->left = createCopy(tree->left);
	result->right = createCopy(tree->right);

	return result;
}

void freeTree(NodeT* tree) {
	if (!tree)
		return;

	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}

void ERROR(int errorCode){
#ifdef __cplusplus
	exit(errorCode);
#endif

	switch (errorCode){
	case NOT_ENOUGHT_MEMORY:
		printf("Not enought memory");
		break;
	case INCORECRT_TREE_SIZE:
		printf("Tree size is incorrect");
		break;
	case TREE_PTR_IS_NULL:
		printf("Tree pointer is Null");
		break;
	default:
		printf("Unknown error");
		break;
	}

	exit(errorCode);
}
