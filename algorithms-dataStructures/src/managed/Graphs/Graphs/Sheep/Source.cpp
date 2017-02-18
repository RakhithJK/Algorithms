#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>

using namespace std;

typedef		pair<int, int>	location;
const		int				infinity = numeric_limits<int>::max() / 2;

int sectorId, sizeY, sizeX, survivedSheep, survivedWolves;

vector<string>	map;
set<location>	visitedLoc;
int				xOff[] = { 0, 0, -1, 1 };
int				yOff[] = { -1,1,0,0 };

inline bool isInMap(int y, int x)
{
	return y >= 0 && x >= 0 && y < sizeY && x < sizeX;
}
inline bool isEscapeLocation(int row, int col)
{
	return (row == 0		 &&	col == 0			&& map[row][col] == '.')	&&
		   (row == 0		 &&	col == sizeX - 1	&& map[row][col] == '.')	&&
		   (row == sizeY - 1 && col == 0			&& map[row][col] == '.')	&&
		   (row == sizeY - 1 && col == sizeX - 1	&& map[row][col] == '.');
}

inline void visitSector(int startRow, int startCol)
{
	queue<location> q;
	q.push({ startRow, startCol });

	int sectorWolves = 0;
	int sectorSheep = 0;

	while (!q.empty())
	{
		auto currentLocation = q.front();
		q.pop();

		if (visitedLoc.find(currentLocation) != visitedLoc.end())
			continue;

		visitedLoc.insert(currentLocation);

		if (map[currentLocation.first][currentLocation.second] == 'k')
			sectorSheep++;
		if (map[currentLocation.first][currentLocation.second] == 'v')
			sectorWolves++;

		if (isEscapeLocation(currentLocation.first, currentLocation.second))
			return;

		for (int o = 0; o < 4; o++)
		{
			int newY = currentLocation.first + yOff[o];
			int newX = currentLocation.second + xOff[o];
			if (
				isInMap(newY, newX) &&
				visitedLoc.find({ newY, newX }) == visitedLoc.end() &&
				map[newY][newX] != '#'
			)
			{
				q.push({ newY, newX });
			}
		}
	}

	if (sectorSheep > sectorWolves)
	{
		survivedSheep += sectorSheep;
	}
	else
	{
		survivedWolves += sectorWolves;
	}
}

inline void visitAllSectors()
{
	for (int row = 0; row < sizeY; row++)
	{
		for (int col = 0; col < sizeX; col++)
		{
			if (map[row][col] != '#' && visitedLoc.find({ row, col }) == visitedLoc.end())
			{
				sectorId++;
				visitSector(row, col);
			}
		}
	}
}

int main()
{
	scanf("%d %d", &sizeY, &sizeX);
	sectorId = 0;

	for (int r = 0; r < sizeY; r++)
	{
		string columns;
		cin >> columns;
		map.push_back(columns);
	}

	visitAllSectors();
	cout << survivedSheep << ' ' << survivedWolves;
	return 0;
}