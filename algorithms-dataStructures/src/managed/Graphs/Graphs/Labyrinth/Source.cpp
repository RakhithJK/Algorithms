#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

int					testsN, labSizeX, labSizeY;
vector<int>			pathLengths;
vector<string>		currentLab;
set<pair<int, int>> visited;
pair<int, int>		longestDistancePosition;


inline bool isInLab(int row, int col)
{
	return row >= 0 && col >= 0 && row < labSizeX && col < labSizeY;
}

int pathLength = -1;
void dfs(int row, int col, int currentPathLength)
{
	if (currentPathLength >= pathLength)
	{
		pathLength = currentPathLength;
		longestDistancePosition = { row, col };
	}
		
	visited.insert({row, col});

	int xOff[4] = { 1, -1, 0, 0 };
	int yOff[4] = { 0 , 0, -1, 1 };

	for(int off = 0; off < 4; off++)
	{
		int newRow = row + xOff[off];
		int newCol = col + yOff[off];

		if (
			isInLab(newRow, newCol)						&&
			currentLab[newRow][newCol]			== '.'	&&
			visited.find({ newRow, newCol })	== visited.end()
		)
		{
			dfs(newRow, newCol, currentPathLength + 1);
		}
	}
}

int calculateLongestPath()
{
	for (int x = 0; x < labSizeX; x++)
	{
		for (int y = 0; y < labSizeY; y++)
		{
			if (currentLab[x][y] == '.' && visited.find({ x,y }) == visited.end())
			{
				dfs(x, y, 0);
			}
		}
	}

	pathLength = -1;
	visited.clear();
	dfs(longestDistancePosition.first, longestDistancePosition.second, 0);

	return pathLength;
}


int main()
{
	scanf("%d", &testsN);
	for (int t = 0; t < testsN; t++)
	{
		scanf("%d %d", &labSizeY, &labSizeX);
		string row;

		for (int x = 0; x < labSizeX; x++)
		{
			cin >> row;
			currentLab.push_back(row);
		}

		pathLengths.push_back(calculateLongestPath());
		currentLab.clear();
		visited.clear();
		pathLength = -1;
	}

	for (auto length : pathLengths)
		printf("Maximum rope length is %d.\n", length);

	return 0;
}