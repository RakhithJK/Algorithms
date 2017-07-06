#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define maxWeight 1005
#define maxBagsCount 55

struct bag
{
	bag() { }
	bag(int weight, int profit) { this->weight = weight; this->profit = profit; }
	int weight;
	int profit;
};

int maximumWeight, amountOfBags;
vector<bag> bags;

int maxValueForWeightAndBags[maxWeight][maxBagsCount];

int getMaxProfitForWeight(int bagPosition, int availableWeight)
{
	if (availableWeight == 0 || bagPosition == -1)
		return maxValueForWeightAndBags[availableWeight][bagPosition] = 0;
	if (maxValueForWeightAndBags[availableWeight][bagPosition] != 0)
		return maxValueForWeightAndBags[availableWeight][bagPosition];

	auto maxProfitExcludingCurrentBag = getMaxProfitForWeight(bagPosition - 1, availableWeight);
	auto maxProfitIncludingCurrentBag = (bags[bagPosition].weight > availableWeight) ?
		maxProfitExcludingCurrentBag :
		getMaxProfitForWeight(bagPosition - 1, availableWeight - bags[bagPosition].weight) + bags[bagPosition].profit;

	return maxValueForWeightAndBags[availableWeight][bagPosition] = max(maxProfitIncludingCurrentBag, maxProfitExcludingCurrentBag);
}

int calculateMaxProfitForWeight() {
	memset(maxValueForWeightAndBags, 0, sizeof maxValueForWeightAndBags);
	return getMaxProfitForWeight(amountOfBags - 1, maximumWeight);
}

int main() {
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &maximumWeight, &amountOfBags);
		bags = vector<bag>(amountOfBags);

		for (auto i = 0; i < amountOfBags; i++)
			scanf("%d %d", &bags[i].weight, &bags[i].profit);

		printf("Hey stupid robber, you can get %d.\n", calculateMaxProfitForWeight());
	}
	return 0;
}