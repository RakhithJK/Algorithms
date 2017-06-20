#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <vector>

using namespace std;
int rowsN, colsN, spikesPerEachPathCount;

#define	treasure	'x'
#define entrance	'@'
#define wall		'#'
#define spike		's'
#define safe		'.'
typedef pair<int, int> position;
#define row first
#define col second

char				maze[45][45];
bool				visited[45][45];
vector<position>	entrances;

int xOff[] = { 0,0,-1,1 };
int yOff[] = { 1, -1, 0,0 };

inline bool isInMap(int row, int col) { return row >= 0 && col >= 0 && row < rowsN && col < colsN; }

int			treasureSpikesCost_currentPath = 0;
position	treasureFound;

bool canCaptureTreasure(int row, int col, int currentSpikesInPath = 0)
{
	visited[row][col] = true;

	for (auto direction = 0; direction < 4; direction++)
	{
		auto nextRow = row + yOff[direction];
		auto nextCol = col + xOff[direction];

		if (!isInMap(nextRow, nextCol) || visited[nextRow][nextCol])
			continue;

		if (maze[nextRow][nextCol] == treasure)
		{
			treasureSpikesCost_currentPath = currentSpikesInPath;
			treasureFound = { nextRow, nextCol };
			return true;
		}
		
		if (maze[nextRow][nextCol] == spike)
		{
			if (currentSpikesInPath + 1 > spikesPerEachPathCount)
				continue;

			if (canCaptureTreasure(nextRow, nextCol, currentSpikesInPath + 1))
				return true;
		}
		if (maze[nextRow][nextCol] == safe && canCaptureTreasure(nextRow, nextCol, currentSpikesInPath))
			return true;
	}
	return false;
}

int entranceSpikesCost_currentPath = 0;
bool canReturnToAnyEntrance(int row, int col, int currentSpikesInPath = 0)
{
	visited[row][col] = true;

	for (auto direction = 0; direction < 4; direction++)
	{
		auto nextRow = row + yOff[direction];
		auto nextCol = col + xOff[direction];

		if (!isInMap(nextRow, nextCol) || visited[nextRow][nextCol])
			continue;
		if (maze[nextRow][nextCol] == entrance)
		{
			entranceSpikesCost_currentPath = currentSpikesInPath;
			return true;
		}
		if (maze[nextRow][nextCol] == spike)
		{
			if (currentSpikesInPath + 1 > spikesPerEachPathCount - treasureSpikesCost_currentPath)
				continue;

			if (canReturnToAnyEntrance(nextRow, nextCol, currentSpikesInPath + 1))
				return true;
		}
		if (maze[nextRow][nextCol] == safe && canReturnToAnyEntrance(nextRow, nextCol, currentSpikesInPath))
			return true;
	}
	return false;
}

int main()
{
	scanf("%d %d %d", &rowsN, &colsN, &spikesPerEachPathCount);
	for (auto row = 0; row < rowsN; row++)
		scanf("%s", &maze[row]);
	for (auto row = 0; row < rowsN; row++)
		for (auto col = 0; col < colsN; col++)
			if (maze[row][col] == entrance)
				entrances.push_back({ row,col });

	auto canSurvive = false;
	for(auto possibleEntrance : entrances)
	{
		memset(visited, false, sizeof visited);
		auto canTreasure = canCaptureTreasure(possibleEntrance.row, possibleEntrance.col);
		memset(visited, false, sizeof visited);
		auto canReturn = canReturnToAnyEntrance(treasureFound.row, treasureFound.col);
		if (canTreasure && canReturn && treasureSpikesCost_currentPath + entranceSpikesCost_currentPath <= spikesPerEachPathCount)
		{
			canSurvive = true;
			break;
		}
	}
	if(canSurvive)
		printf("SUCCESS");
	else
		printf("IMPOSSIBLE");
	return 0;
}