#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

vector<vector<int>> numbersGrid;
vector<int>			leftPairSums;
vector<int>			rightPairSums;

long long calculateNumberOfQuadroupletsThatSumToZero()
{
	long long quads = 0;
	sort(leftPairSums.begin(), leftPairSums.end());
	sort(rightPairSums.begin(), rightPairSums.end());
	for(auto leftSum : leftPairSums)
	{
		auto rangeOfInversePairs = equal_range(rightPairSums.begin(), rightPairSums.end(), -leftSum);
		if(rangeOfInversePairs.first != rangeOfInversePairs.second)
		{
			quads += abs(rangeOfInversePairs.first - rangeOfInversePairs.second);
		}
	}
	return quads;
}

int main()
{
	int rows;
	scanf("%d", &rows);
	for(auto r = 0; r < rows; r++)
	{
		vector<int> row(4);
		scanf("%d %d %d %d", &row[0], &row[1], &row[2], &row[3]);
		numbersGrid.push_back(row);
	}
	for (auto i = 0; i < rows; i++)
	{
		for(auto j = 0; j < rows; j++)
		{
			leftPairSums.push_back(numbersGrid[i][0] + numbersGrid[j][1]);
			rightPairSums.push_back(numbersGrid[i][2] + numbersGrid[j][3]);
		}
	}
	printf("%lld", calculateNumberOfQuadroupletsThatSumToZero());
	return 0;
}