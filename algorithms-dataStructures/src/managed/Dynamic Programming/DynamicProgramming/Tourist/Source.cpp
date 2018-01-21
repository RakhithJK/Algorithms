#define _CRT_SECURE_NO_WARNINGS
#define maxDimensions 105

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char	terrain[maxDimensions][maxDimensions];
int		maxVisitablePlaces[maxDimensions][maxDimensions][maxDimensions];
int		maxDimension, cols;

typedef pair<int, int> position;
#define row first
#define col second

inline bool isInMap(int row, int col) { return row >= 0 && col >= 0 && row < maxDimension && col < cols; }
inline bool isInMap(position p) { return isInMap(p.row, p.col); }
inline char at(position p) { return terrain[p.row][p.col]; }

int calculateMaxVisitablePositionsFrom(position southEastPosition, int northWestPositionRow) {

	auto northWestPosition = position { northWestPositionRow, (southEastPosition.row + southEastPosition.col) - northWestPositionRow };
	printf("%d %d %d %d\n", southEastPosition.row, southEastPosition.col, northWestPosition.row, northWestPosition.col);

	if (!isInMap(southEastPosition) || !isInMap(northWestPosition) || at(southEastPosition) == '#' || at(northWestPosition) == '#') 
		return 0;

	if (maxVisitablePlaces[southEastPosition.row][southEastPosition.col][northWestPositionRow] != -1)
		return maxVisitablePlaces[southEastPosition.row][southEastPosition.col][northWestPositionRow];

	auto maxVisitablePositions = 0;

	if (at(southEastPosition) == '*') maxVisitablePositions++;
	if (at(northWestPosition) == '*') maxVisitablePositions++;
	if (southEastPosition == northWestPosition && at(southEastPosition) == '*') 
		maxVisitablePositions = 1;

	auto optimalPath = max(
		max(
			calculateMaxVisitablePositionsFrom(position(southEastPosition.row + 1, southEastPosition.col), northWestPositionRow),
			calculateMaxVisitablePositionsFrom(position(southEastPosition.row + 1, southEastPosition.col), northWestPositionRow + 1)
		),
		max(
			calculateMaxVisitablePositionsFrom(position(southEastPosition.row, southEastPosition.col + 1), northWestPositionRow),
			calculateMaxVisitablePositionsFrom(position(southEastPosition.row, southEastPosition.col + 1), northWestPositionRow + 1)
		)
	);

	maxVisitablePositions += optimalPath;

	return maxVisitablePlaces[southEastPosition.row][southEastPosition.col][northWestPositionRow] = maxVisitablePositions;
}

int main()
{
	int tests;

	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%d %d", &cols, &maxDimension);
		memset(maxVisitablePlaces, -1, sizeof maxVisitablePlaces);
		for(auto row  = 0; row < maxDimension; row++)
			scanf("%s", &terrain[row]);

		printf("%d\n", calculateMaxVisitablePositionsFrom({ 0,0 }, 0));

	}
	return 0;
}