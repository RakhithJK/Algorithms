#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <climits>
#include <array>

using namespace std;

typedef long long bigint;
#define infinity INT_MAX - 1
#define maxSize 10001
array<bigint, maxSize> coinsOfMonster;
array<bigint, maxSize> maxCoinsFromIndex;

bigint calculateMaxSumFrom(int index)
{
	if (index == -1)
		return 0;
	if (index == 0)
		return maxCoinsFromIndex[0] = coinsOfMonster[0];
	if (maxCoinsFromIndex[index] != infinity)
		return maxCoinsFromIndex[index];

	return maxCoinsFromIndex[index] = max(
		coinsOfMonster[index] + calculateMaxSumFrom(index - 2),
		calculateMaxSumFrom(index - 1)
	);
}

int main()
{
	int tests, monstersN, currentTest = 0;
	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%d", &monstersN);
		for (auto i = 0; i < monstersN; i++)
			scanf("%d", &coinsOfMonster[i]);

		maxCoinsFromIndex.fill(infinity);
		printf("Case %d: %lld\n", ++currentTest, calculateMaxSumFrom(monstersN - 1));
	}
	return 0;
}