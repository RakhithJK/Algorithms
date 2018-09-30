#define _CRT_SECURE_NO_WARNINGS

#define undefined 1 << 20
#define maxLength 110

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

int maxNumberOfPainted(int lastIncreasingIx, int lastDecreasingIx, int currentIx)
{
	if (currentIx == sequenceLength)
		return 0;

	if (cache[lastIncreasingIx][lastDecreasingIx][currentIx] != -1)
		return cache[lastIncreasingIx][lastDecreasingIx][currentIx];

	int optimum = maxNumberOfPainted(lastIncreasingIx, lastDecreasingIx, currentIx + 1);

	if (sequence[currentIx] > sequence[lastIncreasingIx])
	{
		optimum = max(
			optimum,
			1 + maxNumberOfPainted(currentIx, lastDecreasingIx, currentIx + 1)
		);
	}

	if (sequence[currentIx] < sequence[lastDecreasingIx])
	{
		optimum = max(
			optimum,
			1 + maxNumberOfPainted(lastIncreasingIx, currentIx, currentIx + 1)
		);
	}

	return cache[lastIncreasingIx][lastDecreasingIx][currentIx] = optimum;
}


int main()
{
	int tests;
	scanf("%d", &tests);

	while (tests--)
	{
		scanf("%d", &sequenceLength);

		sequence[0] = undefined;
		sequence[1] = -undefined;
		sequenceLength += 2;

		for (auto i = 2; i < sequenceLength; i++)
			scanf("%d", &sequence[i]);

		memset(cache, -1, sizeof cache);
		auto optimum = maxNumberOfPainted(1, 0, 2);

		printf("%d\n", optimum);
	}

	return 0;
}
