#define _CRT_SECURE_NO_WARNINGS

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> position;

#define row				first
#define col				second
#define infinity		100000000
#define maxDimension	21
#define maxDirtyTilesN	12

int  rowsN, colsN;
char terrain[maxDimension][maxDimension];
int  distances[maxDimension][maxDimension];

position			start;
vector<position>	dirtyTiles;
map<int, position>  nodes;
map<position, int>  idOfPosition;

int dirtyTilesNumber = 0;

inline int allVisitedMask() { return (1 << dirtyTilesNumber) - 1; }
inline bool isInMap(position p) { return p.row >= 0 && p.col >= 0 && p.row < rowsN && p.col < colsN; }

const int rowDirections[] = { 0, 1, -1, 0 };
const int colDirections[] = { 1, 0, 0, -1 };

bool allPairShortestPathFrom(int sourceId)
{
	auto source = nodes[sourceId];

	queue<pair<position, int>>	q;
	set<position>				visitedDirtyTiles;
	bool						visited[maxDimension][maxDimension];
	int							distanceTo[maxDimension][maxDimension];

	for (int row = 0; row < rowsN; row++)
		for (int col = 0; col < colsN; col++)
			distanceTo[row][col] = infinity;

	memset(visited, false, sizeof visited);
	q.push({ source, 0 });

	while(!q.empty())
	{
		auto currentPosition = q.front().first;
		auto currentDistance = q.front().second;

		q.pop();

		if(visited[currentPosition.row][currentPosition.col])
			continue;

		for(auto direction = 0; direction < 4; direction++)
		{
			auto nextPositionRow = currentPosition.row + rowDirections[direction],
				 nextPositionCol = currentPosition.col + colDirections[direction];
			auto nextPosition    = position { nextPositionRow, nextPositionCol };

			if(!isInMap(nextPosition) || terrain[nextPositionRow][nextPositionCol] == 'x')
				continue;

			if (any_of(dirtyTiles.begin(), dirtyTiles.end(), [&](const position _) { return _ == nextPosition; }))
				visitedDirtyTiles.insert(nextPosition);

			distanceTo[nextPositionRow][nextPositionCol] = min(distanceTo[nextPositionRow][nextPositionCol], currentDistance + 1);
			q.push({ nextPosition ,	distanceTo[nextPositionRow][nextPositionCol] });
		}

		visited[currentPosition.row][currentPosition.col] = true;
	}

	distances[sourceId][idOfPosition[{start.row, start.col}]] = distanceTo[start.row][start.col];
	for (const auto tile : dirtyTiles)
		distances[idOfPosition[source]][idOfPosition[tile]] = distanceTo[tile.row][tile.col];

	return visitedDirtyTiles.size() == dirtyTilesNumber;
}

inline int isVisited(int mask, int position) { return mask & (1 << position); }
inline int markPositionInMaskAsVisited(int mask, int position) { return mask | (1 << position); }

int minimumCostPathOf[maxDirtyTilesN][1 << maxDirtyTilesN];
int minimumCostPathFrom(int currentPosition, int currentMask)
{
	if (__builtin_popcount(currentMask) == dirtyTilesNumber)
		return 0;

	if (minimumCostPathOf[currentPosition][currentMask] != -1)
		return minimumCostPathOf[currentPosition][currentMask];

	auto minCostFromCurrent		= infinity;
	auto maskWithCurrentVisited = markPositionInMaskAsVisited(currentMask, currentPosition);

	for(auto adjacent = 0; adjacent < nodes.size(); adjacent++)
	{
		if (isVisited(currentMask, adjacent))
			continue;
		if(adjacent == currentPosition)
			continue;
	
		minCostFromCurrent = min(
			minCostFromCurrent, 
			distances[currentPosition][adjacent] + minimumCostPathFrom(adjacent, maskWithCurrentVisited)
		);	
	}
		
	return minCostFromCurrent;
}

int main() {
	while(scanf("%d %d", &colsN, &rowsN) && rowsN && colsN)
	{
		dirtyTilesNumber = 0;
		dirtyTiles.clear();
		nodes.clear();
		idOfPosition.clear();

		for (auto row = 0; row < rowsN; row++)
		{
			scanf("%s", &terrain[row]);
			for (auto col = 0; col < colsN; col++)
			{
				if (terrain[row][col] == 'o')
					start = position({ row, col }), nodes[dirtyTilesNumber] = { row, col }, idOfPosition[{ row, col }] = dirtyTilesNumber, dirtyTilesNumber++;

				if (terrain[row][col] == '*')
					dirtyTiles.push_back({ row, col }), nodes[dirtyTilesNumber] = { row, col }, idOfPosition[{ row, col }] = dirtyTilesNumber, dirtyTilesNumber++;
			}
		}

		dirtyTilesNumber--;

		if(!allPairShortestPathFrom(0))	
			printf("-1\n");
		
		else
		{
			for (auto node = 1; node < nodes.size(); node++)
				allPairShortestPathFrom(node);

			memset(minimumCostPathOf, -1, sizeof minimumCostPathOf);
			auto minCost = minimumCostPathFrom(idOfPosition[{start.row, start.col}], 0);
			printf("%d\n", minCost);
		}
	}
	return 0;
}