#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#define maxItemsCount 2005
#define infinity INT_MAX - 1

struct item
{
	int weight;
	int value;
};

int bagCapacity;
int itemsCount;

vector<item> items;
int maxValueForWeight[maxItemsCount][maxItemsCount];

int calculateMaximumValueStartingFrom(int itemPosition, int availableWeight) {
	if (maxValueForWeight[availableWeight][itemPosition] != -1)
		return maxValueForWeight[availableWeight][itemPosition];

	if (availableWeight == 0 || itemPosition == -1)
		return 0;

	auto valueIncludingCurrent = items[itemPosition].weight > availableWeight ?
		calculateMaximumValueStartingFrom(itemPosition - 1, availableWeight) :
		items[itemPosition].value + calculateMaximumValueStartingFrom(itemPosition - 1, availableWeight - items[itemPosition].weight);

	auto valueExcludingCurrent = calculateMaximumValueStartingFrom(itemPosition - 1, availableWeight);

	return maxValueForWeight[availableWeight][itemPosition] = max(valueIncludingCurrent, valueExcludingCurrent);
}

int calculateMaximumValueForCapacity()
{
	memset(maxValueForWeight, -1, sizeof maxValueForWeight);
	return calculateMaximumValueStartingFrom(itemsCount - 1, bagCapacity);
}

int main() {
	scanf("%d %d", &bagCapacity, &itemsCount);
	items.resize(itemsCount);
	for (auto i = 0; i < itemsCount; i++)
		scanf("%d %d", &items[i].weight, &items[i].value);

	auto sol = calculateMaximumValueForCapacity();
	printf("%d", sol);
	return 0;
}