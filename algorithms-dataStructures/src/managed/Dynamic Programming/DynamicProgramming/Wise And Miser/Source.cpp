#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

#define maxDimensions 101
#define infinity INT_MAX / 2

int	cityBusses[maxDimensions][maxDimensions];
int lookup[maxDimensions][maxDimensions];
int cities, busses;

int calculateMinimumCost(int currentCityIx, int currentBusIx)
{
	if (currentCityIx == cities - 1)
		return lookup[currentCityIx][currentBusIx] = cityBusses[currentCityIx][currentBusIx];

	if (lookup[currentCityIx][currentBusIx])
		return lookup[currentCityIx][currentBusIx];

	auto isTakingBusPossible = [&](int cityIx, int busIx)
	{
		return (cityIx >= 0 && cityIx < cities) && 
			   (busIx >= 0 && busIx < busses);
	};

	auto possibleNextPathsCost = {
		isTakingBusPossible(currentCityIx + 1, currentBusIx)		?	calculateMinimumCost(currentCityIx + 1, currentBusIx)		: infinity,
		isTakingBusPossible(currentCityIx + 1, currentBusIx - 1)	?	calculateMinimumCost(currentCityIx + 1, currentBusIx - 1)	: infinity,
		isTakingBusPossible(currentCityIx + 1, currentBusIx + 1)	?	calculateMinimumCost(currentCityIx + 1, currentBusIx + 1)	: infinity,
	};

	return lookup[currentCityIx][currentBusIx] = cityBusses[currentCityIx][currentBusIx] + min(possibleNextPathsCost);
}

int main()
{
	scanf("%d %d", &cities, &busses);

	for (auto city = 0; city < cities; city++)
		for (auto bus = 0; bus < busses; bus++)
			scanf("%d", &cityBusses[city][bus]);

	auto minimumCost = infinity;
	for (auto startingBus = 0; startingBus < busses; startingBus++)
		minimumCost = min(minimumCost, calculateMinimumCost(0, startingBus));

	printf("%d", minimumCost);
	return 0;
}