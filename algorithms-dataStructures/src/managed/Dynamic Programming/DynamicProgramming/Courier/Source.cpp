#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define infinity 1 << 28
#define maxCities 101
#define maxOrdersN 20
#define maxMask 1 << 12
#define from first
#define to second

typedef pair<int, int> order;
vector<order> orders;

int allCompletedOrdersMask = 0, roadsN, citiesN, ordersN, packetsN, startingCity;
int graph[maxCities][maxCities], dp[maxMask][maxCities];

void computeAllPairsShortestPath()
{
	for (auto k = 0; k < citiesN; k++)
		for (auto i = 0; i < citiesN; i++)
			for (auto j = 0; j < citiesN; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

void clear()
{
	ordersN = 0;
	orders.clear();

	for (auto i = 0; i < maxCities; i++)
		for (auto j = 0; j < maxCities; j++)
			graph[i][j] = i == j ? 0 : infinity;

	memset(dp, -1, sizeof dp);
}

inline int isOrderCompleted(int mask, int order) { return mask & (1 << order); }
inline int markOrderAsCompleted(int mask, int order) { return mask | (1 << order); }

int minCostFromCity(int completedOrdersMask, int currentCity)
{
	if (dp[completedOrdersMask][currentCity] != -1) 
		return dp[completedOrdersMask][currentCity];

	if (completedOrdersMask == allCompletedOrdersMask)
		return dp[completedOrdersMask][currentCity] = graph[currentCity][startingCity];

	int minCostFromCurrentCity = infinity;

	for (auto order = 0; order < orders.size(); order++)
	{
		if (!isOrderCompleted(completedOrdersMask, order))
		{
			auto completedOrderMask = markOrderAsCompleted(completedOrdersMask, order);
			auto orderFrom = orders[order].from;
			auto orderTo = orders[order].to;

			auto cost = 
				graph[currentCity][orderFrom] +
				graph[orderFrom][orderTo] +
				minCostFromCity(completedOrderMask, orderTo);

			minCostFromCurrentCity = min(minCostFromCurrentCity, cost);
		}
	}

	return dp[completedOrdersMask][currentCity] = minCostFromCurrentCity;
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		clear();

		int leftCity, rightCity, cost;

		scanf("%d %d %d", &citiesN, &roadsN, &startingCity);
		startingCity--;

		while(roadsN--)
		{
			scanf("%d %d %d", &leftCity, &rightCity, &cost);
			graph[leftCity - 1][rightCity - 1] = cost;
			graph[rightCity - 1][leftCity - 1] = cost;
		}

		int orderInputsN;
		scanf("%d", &orderInputsN);

		while(orderInputsN--)
		{
			scanf("%d %d %d", &leftCity, &rightCity, &packetsN);
			ordersN += packetsN;

			while (packetsN--)
				orders.push_back({ leftCity - 1, rightCity - 1 });
		}

		allCompletedOrdersMask = (1 << ordersN) - 1;
		computeAllPairsShortestPath();
		minCostFromCity(0, startingCity);

		cout << minCostFromCity(0, startingCity) << endl;
	}
}