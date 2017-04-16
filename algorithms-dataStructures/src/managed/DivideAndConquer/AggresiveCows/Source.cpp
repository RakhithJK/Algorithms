#define _CRT_SECURE_NO_WARNINGS

#include<algorithm>
#include<vector>
#include<functional>

using namespace std;

vector<long> positions;
int positionsCount, cowsCount;

bool canPlaceAllCowsWithMinimumDistance(long minDistance)
{
	auto currentPosition = positions.begin();
	auto cowsToPlace = cowsCount;
	while (cowsToPlace != 0 && currentPosition != positions.end())
	{
		cowsToPlace--;
		auto maybeFoundPosition = upper_bound(positions.begin(), positions.end(), *currentPosition + minDistance - 1);
		currentPosition = maybeFoundPosition;
	}
	return !cowsToPlace;
}

void findMaximumMinimalDistanceRecursively(long lo, long hi, long* maxMinimumDistance)
{
	if (lo > hi)
		return;
	auto mid = (lo + hi) / 2;
	if (canPlaceAllCowsWithMinimumDistance(mid))
	{
		*maxMinimumDistance = max(*maxMinimumDistance, mid);
		lo = mid + 1;
	}
	else
		hi = mid - 1;
	return findMaximumMinimalDistanceRecursively(lo, hi, maxMinimumDistance);
}

long solve()
{
	long maxMinimumDistance = 0;
	sort(positions.begin(), positions.end());
	findMaximumMinimalDistanceRecursively(1, positions[positionsCount - 1] - positions[0], &maxMinimumDistance);
	return maxMinimumDistance;
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests)
	{
		scanf("%d%d", &positionsCount, &cowsCount);
		positions.clear();
		positions.resize(positionsCount);
		for (auto c = 0; c < positionsCount; c++)
			scanf("%ld", &positions[c]);
		printf("%ld\n", solve());
		tests--;
	}
	return 0;
} 