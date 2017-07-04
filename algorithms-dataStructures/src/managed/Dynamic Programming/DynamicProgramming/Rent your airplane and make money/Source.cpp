#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

#define maxOrdersN 1000005
#define infinity INT_MAX -1

struct order {
	int startingTime;
	int finishingTime;
	int profit;

	order() {}
	order(int startingTime, int duration, int profit) {
		this->startingTime = startingTime;
		this->finishingTime = startingTime + duration;
		this->profit = profit;
	}
};

int ordersN;
vector<order> orders;
array<int, maxOrdersN> maxProfitScheduleFrom;

int getNextOrderBefore(int currentOrderIx)
{
	auto lo = 0;
	auto hi = currentOrderIx - 1;
	auto nextOrderIx = -1;
	while (lo <= hi)
	{
		auto mid = (lo + hi) / 2;
		if (orders[mid].finishingTime < orders[currentOrderIx].startingTime)
		{
			nextOrderIx = mid;
			lo = mid + 1;
		}
		else
			hi = mid - 1;
	}

	return nextOrderIx;
}

int computeMaxProfitStartingFrom(int currentOrderIx)
{
	if (currentOrderIx < 0)
		return 0;
	if (maxProfitScheduleFrom[currentOrderIx] != infinity)
		return maxProfitScheduleFrom[currentOrderIx];
	if (currentOrderIx == 0)
		return maxProfitScheduleFrom[0] = orders[0].profit;

	auto nextOrderBeforeCurrent = getNextOrderBefore(currentOrderIx);
	auto profitIncludingCurrentJob = orders[currentOrderIx].profit + computeMaxProfitStartingFrom(nextOrderBeforeCurrent);
	auto profitExcludingCurrentJob = computeMaxProfitStartingFrom(currentOrderIx - 1);

	return maxProfitScheduleFrom[currentOrderIx] = max(profitIncludingCurrentJob, profitExcludingCurrentJob);
}

int calculateMaxProfit() {
	maxProfitScheduleFrom.fill(infinity);
	sort(orders.begin(), orders.end(), [](const order& lhs, const order& rhs) {
		if (lhs.finishingTime == rhs.finishingTime)
			return lhs.profit < rhs.profit;
		return lhs.finishingTime < rhs.finishingTime;
	});
	return computeMaxProfitStartingFrom(ordersN - 1);
}

int main()
{
	int tests;
	int startingTime, duration, profit;
	scanf("%d", &tests);

	while (tests--) {
		scanf("%d", &ordersN);
		orders.clear();
		orders.resize(ordersN);
		for (auto i = 0; i < ordersN; i++)
		{
			scanf("%d %d %d", &startingTime, &duration, &profit);
			orders[i] = order(startingTime, duration, profit);
		}
		printf("%d\n", calculateMaxProfit());
	}
	return 0;
}