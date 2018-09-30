#define _CRT_SECURE_NO_WARNINGS

#define undefined 1 << 20
#define maxLength 205

#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int sequenceLength;
int sequence[maxLength];
int cache[maxLength][maxLength][maxLength];

int minimalNumberOfUnpainted(int lastIncreasingIx, int lastDecreasingIx, int currentIx)
{
	if (currentIx == sequenceLength)
		return 0;
	if (cache[lastIncreasingIx][lastDecreasingIx][currentIx] != -1)
		return cache[lastIncreasingIx][lastDecreasingIx][currentIx];

	int optimum = 1 + minimalNumberOfUnpainted(lastIncreasingIx, lastDecreasingIx, currentIx + 1);

	if (sequence[currentIx] > sequence[lastIncreasingIx])
	{
		optimum = min(
			optimum,
			minimalNumberOfUnpainted(currentIx, lastDecreasingIx, currentIx + 1)
		);
	}

	if (sequence[currentIx] < sequence[lastDecreasingIx])
	{
		optimum = min(
			optimum,
			minimalNumberOfUnpainted(lastIncreasingIx, currentIx, currentIx + 1)
		);
	}

	return cache[lastIncreasingIx][lastDecreasingIx][currentIx] = optimum;
}


int main()
{
	while (scanf("%d", &sequenceLength) && sequenceLength != -1)
	{
		sequence[0] = undefined;
		sequence[1] = -undefined;
		sequenceLength += 2;

		for (auto i = 2; i < sequenceLength; i++)
			scanf("%d", &sequence[i]);

		memset(cache, -1, sizeof cache);
		auto optimum = minimalNumberOfUnpainted(1, 0, 2);

		printf("%d\n", optimum);
	}

	return 0;
}
