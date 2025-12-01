#pragma once
#ifdef __cplusplus
extern "C" {
#endif
	struct SubsetResult {
		int* elements;
		int count;
		int found;
	};
	struct SubsetResult* findSubsetSum(unsigned int B, int N, int* sizes);
	void freeSubsetResult(struct SubsetResult* result);
	void saveResultToFile(struct SubsetResult* result, const char* filename);
	struct SubsetResult* readAndSolve(const char* inputFilename);
#ifdef __cplusplus
}
#endif