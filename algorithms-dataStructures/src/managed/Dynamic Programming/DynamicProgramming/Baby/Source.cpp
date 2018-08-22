#define _CRT_SECURE_NO_WARNINGS


#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif

#define maxQueens 17
#define maxMask 1 << maxQueens

#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

struct position
{
	position() {}
	position(int row, int col) { this->row = row; this->col = col; }
	int row;
	int col;
};

inline bool isQueenPaired(int mask, int queenIx) { return mask & (1 << queenIx); }
inline int markQueenAsPaired(int mask, int queenIx) { return mask | (1 << queenIx); }

int cache[maxMask][maxQueens];

int queensN, allPairedQueensMask;
vector<position> misplacedPositions;
vector<position> correctlyPlacedPositions;

inline int stepsToPlaceCorrectly(const position& wrong, const position& correct)
{
	return abs(wrong.row - correct.row) + abs(wrong.col - correct.col);
}

int computeStepsOfState(int pairingMask, int currentQueenIx)
{
	if (cache[pairingMask][currentQueenIx] != -1)
		return cache[pairingMask][currentQueenIx];

	if (pairingMask == allPairedQueensMask)
		return cache[pairingMask][currentQueenIx] = 0;

	auto steps = 100000;

	auto currentQueen = misplacedPositions[currentQueenIx];

	for (auto queenIx = 0; queenIx < queensN; queenIx++)
	{
		auto correctQueenPosition = correctlyPlacedPositions[queenIx];

		if (!isQueenPaired(pairingMask, queenIx))
			steps = min(
				steps,
				stepsToPlaceCorrectly(currentQueen, correctQueenPosition) + computeStepsOfState(markQueenAsPaired(pairingMask, queenIx), currentQueenIx + 1)
			);
	}

	return cache[pairingMask][currentQueenIx] = steps;
}
int main()
{
	while (scanf("%d", &queensN) && queensN)
	{
		misplacedPositions = vector<position>(queensN);
		correctlyPlacedPositions = vector<position>(queensN);

		for (auto row = 0; row < queensN; row++)
		{
			misplacedPositions[row].row = row;
			scanf("%d", &misplacedPositions[row].col);
			misplacedPositions[row].col--;
		}

		for (auto row = 0; row < queensN; row++)
		{
			correctlyPlacedPositions[row].row = row;
			scanf("%d", &correctlyPlacedPositions[row].col);
			correctlyPlacedPositions[row].col--;
		}

		memset(cache, -1, sizeof cache);
		allPairedQueensMask = (1 << queensN) - 1;
		auto steps = computeStepsOfState(0, 0);
		printf("%d\n", steps);
	}
	return 0;
}

