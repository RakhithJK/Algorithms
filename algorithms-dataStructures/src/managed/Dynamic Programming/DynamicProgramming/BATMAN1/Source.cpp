#define _CRT_SECURE_NO_WARNINGS

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif

#define undefined 1 << 20

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

int batchesN, weaponsN, moneyToSpend;
int batchOpeningCost[25];

int batchWeaponCost[25][25];
int batchWeaponPower[25][25];

int dp[1001][25][2];

int maximumPowerOf(int availableMoney, int batchToConsider, bool isConsideringBatchOpened)
{
	if (batchToConsider >= batchesN)
		return 0;

	if (availableMoney <= 0)
		return 0;

	if (dp[availableMoney][batchToConsider][isConsideringBatchOpened] != -1)
		return dp[availableMoney][batchToConsider][isConsideringBatchOpened];


	auto maximumPowerIfSkippingCurrent = maximumPowerOf(availableMoney, batchToConsider + 1, 0);
	auto maximumPowerIfUsingCurrent = 0;

	if (!isConsideringBatchOpened && availableMoney > batchOpeningCost[batchToConsider])
	{
		auto availableMoneyAfterOpening = availableMoney - batchOpeningCost[batchToConsider];

		for (auto weapon = 0; weapon < weaponsN; weapon++)
		{
			if (availableMoneyAfterOpening < batchWeaponCost[batchToConsider][weapon])
				continue;

			maximumPowerIfUsingCurrent = std::max(
				maximumPowerIfUsingCurrent,
				batchWeaponPower[batchToConsider][weapon] + maximumPowerOf(
					availableMoneyAfterOpening - batchWeaponCost[batchToConsider][weapon],
					batchToConsider,
					true
				)
			);
		}
	}

	if(isConsideringBatchOpened)
	{
		for (auto weapon = 0; weapon < weaponsN; weapon++)
		{
			if (availableMoney < batchWeaponCost[batchToConsider][weapon])
				continue;

			maximumPowerIfUsingCurrent = std::max(
				maximumPowerIfUsingCurrent,
				batchWeaponPower[batchToConsider][weapon] + maximumPowerOf(
					availableMoney - batchWeaponCost[batchToConsider][weapon],
					batchToConsider,
					true
				)
			);
		}
	}

	return dp[availableMoney][batchToConsider][isConsideringBatchOpened] = std::max(
		maximumPowerIfSkippingCurrent, 
		maximumPowerIfUsingCurrent
	);
}


int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests)
	{
		tests--;

		scanf("%d %d  %d", &batchesN, &weaponsN, &moneyToSpend);
		memset(dp, -1, sizeof dp);

		for (auto i = 0; i < batchesN; i++)
			scanf("%d", &batchOpeningCost[i]);

		for (auto batch = 0; batch < batchesN; batch++)
			for (auto weapon = 0; weapon < weaponsN; weapon++)
				scanf("%d", &batchWeaponCost[batch][weapon]);

		for (auto batch = 0; batch < batchesN; batch++)
			for (auto weapon = 0; weapon < weaponsN; weapon++)
				scanf("%d", &batchWeaponPower[batch][weapon]);

		printf("%d\n", maximumPowerOf(moneyToSpend, 0, 0));
	}

	return 0;
}
