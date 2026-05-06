#include "pch.h"

extern "C" {
	#include "../LabB/surce.c"
}

TEST(memoryFunctions, splitBlockTooBigSizeNothingChanged_no1) {
	memoryInit();
	BlockT oldBlock = *memoryBlocks;
	
	splitBlock(memoryBlocks, BUFFER_SIZE);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
}

TEST(memoryFunctions, splitBlockNegativeSizeNothingChanged_no2) {
	memoryInit();
	BlockT oldBlock = *memoryBlocks;

	splitBlock(memoryBlocks, -1);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
}

TEST(memoryFunctions, splitBlockNormalSizeBlockSizeChanged_no3) {
	memoryInit();
	BlockT blocksCopy = *memoryBlocks;

	splitBlock(memoryBlocks, sizeof(char));
	EXPECT_EQ(memoryBlocks->size, sizeof(char));

	*memoryBlocks = blocksCopy;
}

TEST(memoryFunctions, splitBlockNotFreeBlockNothingChanged_no4) {
	memoryInit();
	memoryBlocks->isFree = 0;
	BlockT oldBlock = *memoryBlocks;

	splitBlock(memoryBlocks, sizeof(char));
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
	memoryBlocks->isFree = 1;
}

TEST(memoryFunctions, mergeBloksNotFreeBlockNothingChanged_no5) {
	memoryInit();
	memoryBlocks->isFree = 0;
	BlockT oldBlock = *memoryBlocks;

	mergeBlocks(memoryBlocks);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
	memoryBlocks->isFree = 1;
}

TEST(memoryFunctions, mergeBloksMergedBlockNothingChanged_no6) {
	memoryInit();
	BlockT oldBlock = *memoryBlocks;

	mergeBlocks(memoryBlocks);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
}

TEST(memoryFunctions, mergeBloksSplitedBlockSituationBeforeSplit_no7) {
	memoryInit();
	BlockT oldBlock = *memoryBlocks;

	splitBlock(memoryBlocks, sizeof(char));
	mergeBlocks(memoryBlocks);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));

	*memoryBlocks = oldBlock;
}

TEST(memoryFunctions, myMallocTooBigSizeReturnNULL_no8) {
	EXPECT_FALSE(myMalloc(BUFFER_SIZE*sizeof(char)));
}

TEST(memoryFunctions, myMallocNegativeSizeReturnNULL_no9) {
	EXPECT_FALSE(myMalloc(-1 * sizeof(char)));
}

TEST(memoryFunctions, myFreePtrOutOfRangeNothingChanged_no10) {
	memoryInit();
	BlockT oldBlock = *memoryBlocks;

	myFree(NULL);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));
	*memoryBlocks = oldBlock;

	myFree((char*)memoryBlocks + memoryBlocks->size);
	EXPECT_TRUE(areEq(oldBlock, *memoryBlocks));
	*memoryBlocks = oldBlock;
}

