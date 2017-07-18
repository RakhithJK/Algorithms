#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int numberOfRacks, unitsOfFood;

#define maxRacksN 105
#define maxAvaiableFoodN  1005

struct rack
{
	int dishesN;
	int dishesSum = 0;

	rack() {}
};

vector<rack> racks;

int dishesOfRackWithAvailableFood[maxAvaiableFoodN][maxRacksN];

int computeMaxDishesToEat(int currentRackPosition, int availableFood)
{
	if (currentRackPosition == -1 || availableFood <= 0)
		return 0;

	if (dishesOfRackWithAvailableFood[availableFood][currentRackPosition] != -1)
		return dishesOfRackWithAvailableFood[availableFood][currentRackPosition];

	auto maxDishesIncludingCurrentRack = availableFood - racks[currentRackPosition].dishesSum >= 0 ?
		racks[currentRackPosition].dishesSum + computeMaxDishesToEat(currentRackPosition - 1, availableFood - racks[currentRackPosition].dishesSum) :
		computeMaxDishesToEat(currentRackPosition - 1, availableFood);

	auto maxDishesExcludingCurrentRack = computeMaxDishesToEat(currentRackPosition - 1, availableFood);

	return dishesOfRackWithAvailableFood[availableFood][currentRackPosition] = max(maxDishesIncludingCurrentRack, maxDishesExcludingCurrentRack);
}

int calculateMaxDishes()
{
	memset(dishesOfRackWithAvailableFood, -1, sizeof dishesOfRackWithAvailableFood);
	return computeMaxDishesToEat(numberOfRacks - 1, unitsOfFood);
}

int main()
{
	int tests, currentDishFood;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &numberOfRacks, &unitsOfFood);
		racks.clear();
		racks.resize(numberOfRacks);

		for (auto i = 0; i < numberOfRacks; i++)
		{
			scanf("%d", &racks[i].dishesN);
			for (auto j = 0; j < racks[i].dishesN; j++)
			{
				scanf("%d", currentDishFood);
				racks[i].dishesSum += currentDishFood;
			}
		}
		printf("%d\n", calculateMaxDishes());
	}
	return 0;
}