#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <cmath>

#define maxSize 1005
const int mod = pow(2, 31) - 1;
const int rowDirections[] = { 0, 1, -1, 0 };
const int colDirections[] = { 1, 0, 0, -1};

typedef long long bigint;
using namespace std;

int    maxDimension;
char   terrain[maxSize][maxSize];
bigint waysFrom[maxSize][maxSize];
bool   visited[maxSize][maxSize];

inline bool isInMap(int row, int col)
{
	return row >= 0 && col >= 0 && row < maxDimension && col < maxDimension;
}

inline bool canVisit(int row, int col) { return isInMap(row, col) && terrain[row][col] == '.'; }

bigint computeWaysFrom(int row, int col)
{
	if (row == maxDimension - 1 && col == maxDimension - 1)
		return 1;

	if (waysFrom[row][col] != -1)
		return waysFrom[row][col];

	bigint subWays = 0;

	for(auto direction = 0; direction < 2; direction++)
	{
		auto nextRow = row + rowDirections[direction];
		auto nextCol = col + colDirections[direction];

		if (canVisit(nextRow, nextCol))
			subWays = (subWays + computeWaysFrom(nextRow, nextCol)) % mod;
	}

	return waysFrom[row][col] = subWays;
}

bool doesAllDirectionsPathExist()
{
	queue<pair<int, int>> q;
	q.push({ 0, 0 });

	while(!q.empty())
	{
		auto row = q.front().first;
		auto col = q.front().second;
		q.pop();

		if (row == maxDimension - 1 && col == maxDimension - 1)
			return true;

		for (auto direction = 0; direction < 4; direction++)
		{
			auto nextRow = row + rowDirections[direction];
			auto nextCol = col + colDirections[direction];

			if (canVisit(nextRow, nextCol) && !visited[row][col])
				q.push({ nextRow, nextCol });
		}

		visited[row][col] = true;
	}

	return false;
}

int main()
{
	scanf("%d", &maxDimension);
	
	memset(visited, false, sizeof visited);
	memset(waysFrom, -1, sizeof waysFrom);

	for (auto row = 0; row < maxDimension; row++)
		scanf("%s", &terrain[row]);

	auto canReachWithAllDirections = doesAllDirectionsPathExist();

	if (!canReachWithAllDirections)
		printf("INCONCEIVABLE");
	else
	{
		auto message = computeWaysFrom(0, 0) > 0 ? to_string(computeWaysFrom(0, 0)) : "THE GAME IS A LIE";
		printf("%s", message.c_str());
	}

	return 0;
}