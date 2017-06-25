#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <string>
#include <set>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

#define emerald 'X'
#define rock	'.'

typedef struct {
	int row;
	int col;
} position;

char				terrain[20][20];
int					mapSize;
array<position, 8>	currentOctave;
set<string>			octaves; 

int xOff[] = { -1,0,1, 0 };
int yOff[] = { 0,1,0,-1 };

inline bool isInMap(int row, int col)
{
	return row >= 0 && col >= 0 && row < mapSize && col < mapSize;
}
inline string hashCurrentOctave()
{
	auto currentOctaveCopy = currentOctave;
	sort(currentOctaveCopy.begin(), currentOctaveCopy.end(), [](const position& lhs, const position& rhs)
	{
		if (lhs.row == rhs.row)
			return lhs.col < rhs.col;
		return lhs.row < rhs.row;
	});
	return accumulate(currentOctaveCopy.begin(), currentOctaveCopy.end(), string(""), [](const string result, const position& position)
	{
		return result + to_string(position.row) + to_string(position.col);
	});
}
void tryConstructOctaveFrom(int currentRow, int currentCol, int pathLength)
{
	if (pathLength == 8)
	{
		octaves.insert(hashCurrentOctave());
		return;
	}
	for (auto direction = 0; direction < 4; direction++)
	{
		auto nextRow = currentRow + xOff[direction];
		auto nextCol = currentCol + yOff[direction];
		if (isInMap(nextRow, nextCol) && terrain[nextRow][nextCol] == emerald)
		{
			terrain[nextRow][nextCol] = rock;
			currentOctave[pathLength].row = nextRow;
			currentOctave[pathLength].col = nextCol;
			tryConstructOctaveFrom(nextRow, nextCol, pathLength + 1);
			terrain[nextRow][nextCol] = emerald;
		}
	}
}

void tryConstructAllOctaves()
{
	for (auto row = 0; row < mapSize; row++)
	{
		for (auto col = 0; col < mapSize; col++)
		{
			if (terrain[row][col] == emerald)
			{
				terrain[row][col] = rock;
				currentOctave[0].row = row;
				currentOctave[0].col = col;
				tryConstructOctaveFrom(row, col, 1);
				terrain[row][col] = emerald;
			}
		}
	}
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		octaves.clear();
		scanf("%d", &mapSize);
		for (auto row = 0; row < mapSize; row++)
			scanf("%s", &terrain[row]);
				
		tryConstructAllOctaves();
		printf("%d\n", octaves.size());
	}
	return 0;
}