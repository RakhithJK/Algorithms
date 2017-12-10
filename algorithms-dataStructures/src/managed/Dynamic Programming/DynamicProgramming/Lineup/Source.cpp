#define _CRT_SECURE_NO_WARNINGS
#define maxPlayers 11
#define maxMask (1 << 12)

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif

#include <cstdio>
#include <vector>
#include <cmath>
#include <array>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long bigint;
const int infinity = 0x3f3f3f3f;

array<int, maxMask> dp;
int profficiencyOfPlayer[maxPlayers][maxPlayers];

inline int isPositionAlreadyTaken(int mask, int position) { return mask & (1 << position); }
inline int markPositionInMaskAsTaken(int mask, int position) { return mask | (1 << position); }

int getStrongestLineupPower(int currentLineupMask, int player = 0)
{
	auto currentPlayer = __builtin_popcount(currentLineupMask);

	if (currentPlayer == maxPlayers)
		return 0;

	if (dp[currentLineupMask] != -infinity)
		return dp[currentLineupMask];

	auto currentSubLineupMaxPower = -infinity;

	for (auto position = 0; position < maxPlayers; position++)
	{
		if(profficiencyOfPlayer[currentPlayer][position] == 0)
			continue;
		if(isPositionAlreadyTaken(currentLineupMask, position))
			continue;
		
		currentSubLineupMaxPower = max(
			currentSubLineupMaxPower,
			profficiencyOfPlayer[currentPlayer][position] + getStrongestLineupPower(
				markPositionInMaskAsTaken(currentLineupMask, position),
				player + 1
			)
		);
	}

	return dp[currentLineupMask] = currentSubLineupMaxPower;
}

int main() {
	int tests;
	scanf("%d", &tests);

	while (tests--) {
		for (auto player = 0; player < maxPlayers; player++)
			for (auto position = 0; position < maxPlayers; position++)
				scanf("%lld", &profficiencyOfPlayer[player][position]);

		dp.fill(-infinity);

		printf("%d\n", getStrongestLineupPower(0));
	}

	return 0;
}