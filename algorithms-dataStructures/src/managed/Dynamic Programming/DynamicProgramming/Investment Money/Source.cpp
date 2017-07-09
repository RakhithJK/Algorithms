#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define maxStartingMoney 1000000

struct bond
{
	int cost;
	int profit;

	bond(int cost, int profit)	{ this->cost = cost; this->profit = profit; }
	bond()						{ this->cost = 0; this->profit = 0; }
};

int startingAmount, years, bondsCount;
vector<bond> bonds;

int maxProfitForInvestedMoney[maxStartingMoney];

int computeMaxBoundsProfitForYear_bottomUp(int availableMoney)
{
	memset(maxProfitForInvestedMoney, 0, sizeof maxProfitForInvestedMoney);
	maxProfitForInvestedMoney[0] = 0;

	for (auto currentMoneyAmount = 1; currentMoneyAmount <= availableMoney; currentMoneyAmount++) {
		maxProfitForInvestedMoney[currentMoneyAmount] = maxProfitForInvestedMoney[currentMoneyAmount - 1]; // previous

		for(auto bond : bonds)
		{
			auto availableMoney_afterBuy = currentMoneyAmount - bond.cost;

			if (availableMoney_afterBuy >= 0) {
				maxProfitForInvestedMoney[currentMoneyAmount] = max(
					maxProfitForInvestedMoney[currentMoneyAmount],
					maxProfitForInvestedMoney[availableMoney_afterBuy] + bond.profit
				);
			}
		}
	}
	return maxProfitForInvestedMoney[availableMoney];
}

int computeMaxBoundsProfitForYear_topDown(int availableMoney)
{
	if (availableMoney < 0)
		return 0;
	if (maxProfitForInvestedMoney[availableMoney] != 0)
		return maxProfitForInvestedMoney[availableMoney];

	for (auto bond : bonds)
	{
		if (bond.cost <= availableMoney)
			maxProfitForInvestedMoney[availableMoney] = max(
				maxProfitForInvestedMoney[availableMoney],
				(bond.profit + computeMaxBoundsProfitForYear_topDown(availableMoney - bond.cost))
			);
	}
	return maxProfitForInvestedMoney[availableMoney];
}

int computeMaxProfitForYears(bool topDown = true)
{
	auto trimmedAmount		= startingAmount / 1000;
	auto restAfterTrimming	= startingAmount % 1000;

	while (years--)
	{
		memset(maxProfitForInvestedMoney, 0, sizeof maxProfitForInvestedMoney);
		auto maxProfitAfterYear = topDown ? computeMaxBoundsProfitForYear_topDown(trimmedAmount) : computeMaxBoundsProfitForYear_bottomUp(trimmedAmount);
		trimmedAmount			= trimmedAmount + (maxProfitAfterYear + restAfterTrimming) / 1000;
		restAfterTrimming		= (maxProfitAfterYear + restAfterTrimming) % 1000;
	}

	return trimmedAmount * 1000 + restAfterTrimming;
}

int main() {
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d %d", &startingAmount, &years, &bondsCount);
		bonds = vector<bond>(bondsCount);
		for (auto i = 0; i < bondsCount; i++)
		{
			scanf("%d %d", &bonds[i].cost, &bonds[i].profit);
			bonds[i].cost /= 1000;
		}

		printf("%d\n", computeMaxProfitForYears());
	}
	return 0;
}