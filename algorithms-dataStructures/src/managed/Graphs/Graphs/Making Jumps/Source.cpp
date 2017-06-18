#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include <algorithm>
#include<vector>

using namespace std;

bool visitableArea[10][10];
int rows;

bool isInMap(int row, int col) { return row >= 0 && col >= 0 && row < 10 && col < 10; }

int yOff[] = { -2,-2,-1,-1,1,1,2,2 };
int xOff[] = { -1,1,-2,2,-2,2,-1,1 };

int startRow;
int startCol;
int totalVisitablePositions;
int maxVisitedInARow;

void visitAllInCurrentPathFrom(int row, int col, int currentlyVisitedAlongPath)
{
	maxVisitedInARow = max(maxVisitedInARow, currentlyVisitedAlongPath);
	for(auto direction = 0; direction < 8; direction++)
	{
		auto nextRow = row + yOff[direction];
		auto nextCol = col + xOff[direction];
	
		if(isInMap(nextRow, nextCol) &&	visitableArea[nextRow][nextCol])
		{
			visitableArea[nextRow][nextCol] = false;
			visitAllInCurrentPathFrom(nextRow, nextCol, currentlyVisitedAlongPath + 1);
			visitableArea[nextRow][nextCol] = true;
		}
	}
}

int getNumberOfUnvisitablePositionsInSinglePath()
{
	maxVisitedInARow = 0;
	visitableArea[startRow][startCol] = false;
	visitAllInCurrentPathFrom(startRow, startCol, 1);
	return  totalVisitablePositions - maxVisitedInARow;
}

int main()
{
	int skippedRowCols, rowCols, currentTest = 0;
	scanf("%d", &rows);
	while(rows)
	{
		currentTest++;
		totalVisitablePositions = 0;
		memset(visitableArea, false, sizeof visitableArea);
		for (auto row = 0; row < rows; row++)
		{
			scanf("%d %d", &skippedRowCols, &rowCols);
			totalVisitablePositions += rowCols;
			for (auto col = skippedRowCols; col < (skippedRowCols + rowCols); col++)
				visitableArea[row][col] = true;
		}
		auto foundStart = false;
		for (auto row = 0; row < rows && !foundStart; row++)
		{
			for (auto col = 0; col < 10 && !foundStart; col++)
			{
				if (visitableArea[row][col])
				{
					startRow = row;
					startCol = col;
					foundStart = true;
				}
			}
		}
		auto unvisitablePositionsInSinglePath = getNumberOfUnvisitablePositionsInSinglePath();
		if (unvisitablePositionsInSinglePath == 0)
			printf("Case %d, 0 squares can not be reached.\n", currentTest);
		if(unvisitablePositionsInSinglePath == 1)
			printf("Case %d, 1 square can not be reached.\n", currentTest);
		if(unvisitablePositionsInSinglePath > 1)
			printf("Case %d, %d squares can not be reached.\n", currentTest, unvisitablePositionsInSinglePath);
		scanf("%d", &rows);
	}
	return 0;
}