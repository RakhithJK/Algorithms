#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxDimensions 201
#define facingDirections 2

enum facing
{
	left  = 1,
	right = 2
};

struct state
{
	int		row;
	int		col;
	facing	facingDirection;

	state(int row, int col, facing facing) { this->row = row; this->col = col; this->facingDirection = facing; }
};

int		maxDimension, cols;
char	terrain[maxDimensions][maxDimensions];
int		maxCuttableTreesAtState[maxDimensions][maxDimensions][facingDirections];

inline bool isInMap(state state) { return state.row >= 0 && state.col >= 0 && state.row < maxDimension && state.col < cols; }

int computeMaxCuttableTreesFrom(state current) 
{
	if (!isInMap(current) || terrain[current.row][current.col] == '#')
		return 0;

	if (maxCuttableTreesAtState[current.row][current.col][current.facingDirection] != -1)
		return maxCuttableTreesAtState[current.row][current.col][current.facingDirection];

	if(current.facingDirection == right)
	{
		return maxCuttableTreesAtState[current.row][current.col][current.facingDirection] = (terrain[current.row][current.col] == 'T') + max(
			computeMaxCuttableTreesFrom(state(current.row + 1, current.col, left)),
			computeMaxCuttableTreesFrom(state(current.row, current.col + 1, right))	
		);
	}

	return maxCuttableTreesAtState[current.row][current.col][current.facingDirection] = (terrain[current.row][current.col] == 'T') + max(
		computeMaxCuttableTreesFrom(state(current.row + 1, current.col, right)),
		computeMaxCuttableTreesFrom(state(current.row, current.col - 1, left))
	);
}


int main()
{
	auto tests = 0;
	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%d %d", &maxDimension, &cols);
		memset(maxCuttableTreesAtState, -1, sizeof maxCuttableTreesAtState);

		for (auto row = 0; row < maxDimension; row++)
			scanf("%s", &terrain[row]);

		printf("%d\n", computeMaxCuttableTreesFrom(state(0, 0, facing::right)));
	}
	return 0;
}