#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

#define maxActivitiesN 1000005
#define infinity INT_MAX -1
#define modValue 100000000

typedef unsigned long long bigint;

struct activity {
	int startingTime;
	int finishingTime;

	activity() {}
	activity(int startingTime, int finishingTime) {
		this->startingTime = startingTime;
		this->finishingTime = finishingTime;
	}
};

int activitiesN;
vector<activity> activities;
array<bigint, maxActivitiesN> nonOverlappingSchedulesFrom;

int getNextActivityBefore(int currentOrderIx)
{
	auto lo = 0;
	auto hi = currentOrderIx - 1;
	auto nextOrderIx = -1;

	while (lo <= hi)
	{
		auto mid = (lo + hi) / 2;
		if (activities[mid].finishingTime <= activities[currentOrderIx].startingTime)
		{
			nextOrderIx = mid;
			lo = mid + 1;
		}
		else
			hi = mid - 1;
	}

	return nextOrderIx;
}

bigint computeMaxNonOverlappingSchedules(int currentOrderIx)
{
	if (currentOrderIx < 0)
		return 0;
	if (nonOverlappingSchedulesFrom[currentOrderIx] != infinity)
		return nonOverlappingSchedulesFrom[currentOrderIx];
	if (currentOrderIx == 0)
		return nonOverlappingSchedulesFrom[0] = 1;

	auto nextOrderBeforeCurrent = getNextActivityBefore(currentOrderIx);
	auto profitIncludingCurrentJob = 1 + computeMaxNonOverlappingSchedules(nextOrderBeforeCurrent);
	auto profitExcludingCurrentJob = computeMaxNonOverlappingSchedules(currentOrderIx - 1);

	return nonOverlappingSchedulesFrom[currentOrderIx] = (profitIncludingCurrentJob + profitExcludingCurrentJob) % modValue;
}

bigint computeMaxNonOverlappingSchedules() {
	nonOverlappingSchedulesFrom.fill(infinity);
	sort(activities.begin(), activities.end(), [](const activity& lhs, const activity& rhs) {
		return lhs.finishingTime < rhs.finishingTime;
	});
	return computeMaxNonOverlappingSchedules(activitiesN - 1);
}

int main()
{
	int startingTime, finishingTime;
	while (scanf("%d", &activitiesN) == 1 && activitiesN != -1)
	{
		activities.clear();
		activities.resize(activitiesN);
		for (auto i = 0; i < activitiesN; i++)
		{
			scanf("%d %d", &startingTime, &finishingTime);
			activities[i] = activity(startingTime, finishingTime);
		}
		auto sol = computeMaxNonOverlappingSchedules() % modValue;
		printf("%08d\n", sol);
	}
	return 0;
}