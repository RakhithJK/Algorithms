#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define maxBlocks 2500

using namespace std;

struct block
{
	block() {}
	block(const int width, const int depth, const int height)
	{
		this->width  = width;
		this->height = height;
		this->depth  = depth;
	}
	int width, height, depth;
};

int blocksN, maxTowerHeight = 0;
vector<block> blocks;

int maxTowerHeightUpto[maxBlocks];
int getMaxTowerHeightUpto(const int currentIx)
{
	if (maxTowerHeightUpto[currentIx] != -1)
		return maxTowerHeightUpto[currentIx];

	auto currentBlock		= blocks[currentIx];
	auto heightUptoCurrent = 0;

	for (auto nextBlockIndex = 0; nextBlockIndex < blocks.size(); nextBlockIndex++)
	{
		if (nextBlockIndex == currentIx)
			continue;

		auto nextBlock = blocks[nextBlockIndex];
	
		if (nextBlock.width < currentBlock.width && nextBlock.depth < currentBlock.depth)
			heightUptoCurrent = max(heightUptoCurrent, getMaxTowerHeightUpto(nextBlockIndex));
	}


	return maxTowerHeightUpto[currentIx] = heightUptoCurrent + currentBlock.height;
}

int main()
{
	int width, height, depth;

	while (scanf("%d", &blocksN) != EOF && blocksN)
	{
		blocks.clear();
		maxTowerHeight = 0;
		memset(maxTowerHeightUpto, -1, sizeof maxTowerHeightUpto);

		for (auto i = 0; i < blocksN; i++)
		{
			scanf("%d %d %d", &height, &width, &depth);

			vector<block> rotations = { 
				block(height, width, depth), 
				block(width, height, depth), 
				block(height, depth, width), 
				block(depth, height, width), 
				block(width, depth, height), 
				block(depth, width, height)
			};

			for (const auto rotation : rotations)
				blocks.push_back(rotation);
		}

		for (auto blockUptoCalculate = 0; blockUptoCalculate < blocks.size(); blockUptoCalculate++)
			maxTowerHeight = max(maxTowerHeight, getMaxTowerHeightUpto(blockUptoCalculate));

		printf("%d\n", maxTowerHeight);
	}

	return 0;
}