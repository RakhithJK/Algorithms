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

using namespace std;

struct position
{
	position() {}
	position(int row, int col) { this->row = row; this->col = col; }
	bool operator<(const position& rhs) const
	{
		if (row == rhs.row)
			return col < rhs.col;

		return row < rhs.row;
	}
	int row;
	int col;
};
typedef pair<position, int> positionDistancePair;


int			tests;
int			rowsN, colsN;
string		grid[55];
int			xOff[] = { -1, 0, 0, 1 };
int			yOff[] = { 0, -1, 1, 0 };

position			restaurant;
vector<position>	deliveryPlaces;
map<position, int>	distanceTo;
vector<int>			deliveries;


void findRestaurantAndDeliveries()
{
	deliveryPlaces.clear();
	deliveries.clear();
	int positionId = -1;

	for (auto row = 0; row < rowsN; row++)
	{
		for (auto col = 0; col < colsN; col++)
		{
			distanceTo[{row, col}] = undefined;
			switch (grid[row][col])
			{
				case '$':
					deliveryPlaces.push_back(position(row, col));
					break;
				case 'X':
					restaurant = position(row, col);
					break;
				default:
					break;
			}
		}
	}
}

inline bool isInMap(position& position)
{
	return position.row >= 0 && position.col >= 0 && position.row < rowsN && position.col < colsN;
}

inline bool isBuilding(position& position) {
	return grid[position.row][position.col] == 'X' || grid[position.row][position.col] == '$';
}

inline int getCostFromTo(int height1, int height2)
{
	auto difference = abs(height1 - height2);

	switch (difference)
	{
	case 0:
		return 1;
	case 1:
		return 3;
	default:
		return undefined;
	}
}

void computeShortestPathsFromRestaurant()
{
	auto orderByDistanceAscending = [](positionDistancePair lhs, positionDistancePair rhs) { return lhs.second > rhs.second; };
	priority_queue<positionDistancePair, vector<positionDistancePair>, decltype(orderByDistanceAscending)> pq(orderByDistanceAscending);

	pq.push({ restaurant, 0 });
	distanceTo[restaurant] = 0;

	while (!pq.empty())
	{
		auto currentPosition = pq.top().first;
		auto currentDistance = pq.top().second;
		pq.pop();

		for (auto offset = 0; offset < 4; offset++)
		{
			auto nextPosition = position(
				currentPosition.row + yOff[offset],
				currentPosition.col + xOff[offset]
			);

			if (!isInMap(nextPosition))
				continue;

			auto cost = (isBuilding(nextPosition) || isBuilding(currentPosition)) ? 2 : getCostFromTo(
				grid[nextPosition.row][nextPosition.col] - '0',
				grid[currentPosition.row][currentPosition.col] - '0'
			);

			if (currentDistance + cost < distanceTo[nextPosition])
			{
				distanceTo[nextPosition] = currentDistance + cost;
				pq.push({ nextPosition, distanceTo[nextPosition] });
			}
		}
	}

	for (auto place : deliveryPlaces)
	{
		deliveries.push_back(distanceTo[place]);
	}
}

inline bool isDeliveryCompleted(int mask, int deliveryIx) {
	return mask & (1 << deliveryIx); 
}

inline int markDeliveryCompleted(int mask, int deliveryIx) {
	return mask | (1 << deliveryIx);
}

int getMinimalTimeForDeliveries(int assignedDeliveriesMask, int deliveriesInMask) 
{
	if (deliveriesInMask < deliveries.size())
	{
		return min(
			getMinimalTimeForDeliveries(markDeliveryCompleted(assignedDeliveriesMask, deliveriesInMask), deliveriesInMask + 1), 
			// carrier 1 does current delivery
			getMinimalTimeForDeliveries(assignedDeliveriesMask, deliveriesInMask + 1) 
			// carrier 2 does current delivery
		);
	}

	int carrier1Cost = 0, carrier2Cost = 0;
	int carrier1LastDeliveryCost = 0, carrier2LastDeliveryCost = 0;

	for (int delivery = 0; delivery < deliveries.size(); delivery++)
	{
		if (isDeliveryCompleted(assignedDeliveriesMask, delivery)) // 1 means first carrier
		{
			carrier1Cost += (deliveries[delivery] * 2);
			carrier1LastDeliveryCost = deliveries[delivery];
		}
		else // 0 means second carrier
		{
			carrier2Cost += (deliveries[delivery] * 2);
			carrier2LastDeliveryCost = deliveries[delivery];
		}
	}

	return max(
		carrier1Cost - carrier1LastDeliveryCost,
		carrier2Cost - carrier2LastDeliveryCost
	);
}

int getMinimalTimeForDeliveries() {

	for (int delivery = 0; delivery < deliveries.size(); delivery++)
		if (deliveries[delivery] == undefined)
			return -1;

	sort(deliveries.begin(), deliveries.end());
	return getMinimalTimeForDeliveries(0, 0);
}

int main()
{
	scanf("%d", &tests);
	string currentRow;
	while (tests--)
	{
		scanf("%d %d", &rowsN, &colsN);
		for (int row = 0; row < rowsN; row++)
			cin >> grid[row];

		findRestaurantAndDeliveries();
		computeShortestPathsFromRestaurant();
		auto solution = getMinimalTimeForDeliveries();
		printf("%d\n", solution);
	}
	return 0;
}
