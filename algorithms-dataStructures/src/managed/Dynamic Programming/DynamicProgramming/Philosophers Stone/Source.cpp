#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxDimensions 101

int rowsN, colsN;
auto isInMap = [&](int row, int col) { return row >= 0 && col >= 0 && row < rowsN && col < colsN; };


int grid[maxDimensions][maxDimensions];
int maxCollectableStones[maxDimensions][maxDimensions];

int computeMaxCollectableStonesFrom(int row, int col)
{
	if (!isInMap(row, col))
		return 0;

	if (row == 0)
		return maxCollectableStones[row][col] = grid[row][col];

	if (maxCollectableStones[row][col] != 0)
		return maxCollectableStones[row][col];

	auto maxCollectableStonesUptoCurrentState = {
		computeMaxCollectableStonesFrom(row - 1, col - 1),
		computeMaxCollectableStonesFrom(row - 1, col),
		computeMaxCollectableStonesFrom(row - 1, col + 1)
	};

	return maxCollectableStones[row][col] = grid[row][col] + *max_element(maxCollectableStonesUptoCurrentState.begin(), maxCollectableStonesUptoCurrentState.end());
}

int main()
{
	int tests;
	cin >> tests;

	while (tests--)
	{
		cin >> rowsN >> colsN;

		memset(maxCollectableStones, false, sizeof maxCollectableStones);

		for (auto row = 0; row < rowsN; row++)
			for (auto col = 0; col < colsN; col++)		
				cin >> grid[row][col];		
		
		auto sol = -1;	
		for (auto col = 0; col < colsN; col++)
			sol = max(sol, computeMaxCollectableStonesFrom(rowsN - 1, col));

		cout << sol << endl;
	}
	return 0;
} 