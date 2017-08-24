#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> preference;
typedef unsigned long long bigint;

#define atLeast first
#define atMost second
#define maxGirlsN 21
#define maxGiftsN 101

int girlsN, giftsN;

vector<preference> preferencesForGirl;
bigint waysToDistribute[maxGirlsN][maxGiftsN];

bigint computeWaysToDistribute(int currentGirl, int remainingGifts)
{
	if (currentGirl == girlsN - 1)
		return remainingGifts >= preferencesForGirl[currentGirl].atLeast &&
		remainingGifts <= preferencesForGirl[currentGirl].atMost;

	if (waysToDistribute[currentGirl][remainingGifts] != 0)
		return waysToDistribute[currentGirl][remainingGifts];

	for (auto gifts = preferencesForGirl[currentGirl].atLeast; gifts <= preferencesForGirl[currentGirl].atMost; gifts++)
	{
		if (gifts > remainingGifts)
			break;
		waysToDistribute[currentGirl][remainingGifts] += computeWaysToDistribute(currentGirl + 1, remainingGifts - gifts);
	}
	return waysToDistribute[currentGirl][remainingGifts];
}

int main() {
	while (scanf("%d %d", &girlsN, &giftsN) && girlsN && giftsN)
	{
		memset(waysToDistribute, false, sizeof waysToDistribute);
		preferencesForGirl = vector<preference>(girlsN);
		for (auto i = 0; i < girlsN; i++)
			scanf("%d %d", &preferencesForGirl[i].first, &preferencesForGirl[i].second);
		printf("%lld", computeWaysToDistribute(0, giftsN));
	}
	return 0;
}