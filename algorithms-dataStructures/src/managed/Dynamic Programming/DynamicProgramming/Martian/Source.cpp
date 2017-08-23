#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <cstring>

#define maxSize 501
using namespace std;

enum target_mineral
{
	ye  = 0,
	blo = 1
};

int rows, cols;

int yeyenum[maxSize][maxSize];
int bloggium[maxSize][maxSize];

int maxYeyenumUpto[maxSize][maxSize];
int maxBloggiumUpto[maxSize][maxSize];
int maxCollectableMinerals[maxSize][maxSize];

inline bool isInMap(int row, int col) { return row >= 0 && col >= 0 && row < rows && col < cols; }

int calculateMaxCollectableMinerals(int row, int col)
{
	if (!isInMap(row, col))
		return 0;
	
	if (maxCollectableMinerals[row][col])
		return maxCollectableMinerals[row][col];

	return maxCollectableMinerals[row][col] = max(
		calculateMaxCollectableMinerals(row, col - 1) + maxBloggiumUpto[row][col],
		calculateMaxCollectableMinerals(row - 1, col) + maxYeyenumUpto[row][col]
	);
}

int main()
{

	while(scanf("%d %d", &rows, &cols) && !(rows == 0 && cols == 0))
	{
		memset(maxCollectableMinerals, false, sizeof maxCollectableMinerals);
		for (auto row = 0; row < rows; row++)
		{
			for (auto col = 0; col < cols; col++)
			{
				scanf("%d", &yeyenum[row][col]);

				if (col >= 1)
					maxYeyenumUpto[row][col] = maxYeyenumUpto[row][col - 1] + yeyenum[row][col];
				else
					maxYeyenumUpto[row][col] = yeyenum[row][col];
			}
		}

		for (auto row = 0; row < rows; row++)
		{
			for (auto col = 0; col < cols; col++)
			{
				scanf("%d", &bloggium[row][col]);

				if (row >= 1)
					maxBloggiumUpto[row][col] = maxBloggiumUpto[row - 1][col] + bloggium[row][col];
				else
					maxBloggiumUpto[row][col] = bloggium[row][col];
			}
		}

		printf("%d\n", calculateMaxCollectableMinerals(rows - 1, cols - 1));
	}
	return 0;
}