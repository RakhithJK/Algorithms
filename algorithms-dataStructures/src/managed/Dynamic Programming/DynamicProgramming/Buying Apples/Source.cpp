#define _CRT_SECURE_NO_WARNINGS

#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define infinity INT_MAX / 2
#define maxCost  1005
#define maxPackages  105

struct package {
	int applesWeight;
	int cost;

	package() {}
	package(int applesWeight, int cost) { this->applesWeight = applesWeight; this->cost = cost; }
};


vector<package> packages;
int numberOfFriends, applesWeight;


int minCostForApplesWeightOf[maxPackages];

int calculateMinCost_topDown(int availableWeight)
{
	if (availableWeight == 0)
		return minCostForApplesWeightOf[availableWeight] = 0;

	if (minCostForApplesWeightOf[availableWeight] != -1)
		return minCostForApplesWeightOf[availableWeight];

	minCostForApplesWeightOf[availableWeight] = infinity;

	for(auto package: packages)
	{
		if (package.applesWeight <= availableWeight)
			minCostForApplesWeightOf[availableWeight] = min(minCostForApplesWeightOf[availableWeight], calculateMinCost_topDown(availableWeight - package.applesWeight) + package.cost);
	}
	return minCostForApplesWeightOf[availableWeight];
}

int main()
{
	int tests, packageCost;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &numberOfFriends, &applesWeight);
		packages.clear();
		for (auto weight = 1; weight <= applesWeight; weight++)
		{
			scanf("%d", &packageCost);
			if (packageCost == -1)
				continue;

			packages.push_back(package(weight, packageCost));
		}

		memset(minCostForApplesWeightOf, -1, sizeof minCostForApplesWeightOf);
		auto solution = calculateMinCost_topDown(applesWeight);
		printf("%d\n", ((solution == infinity || solution == 0) ? - 1 : solution));
	}
	return 0;
}