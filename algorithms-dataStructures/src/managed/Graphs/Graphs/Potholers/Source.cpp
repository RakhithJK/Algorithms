#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
#define maxChambers 210

int					chambersN;
vector<vector<int>> tree;
int					residualCapacityOfEdge[maxChambers][maxChambers];
bool				visitedInCurrentPath[maxChambers];
int					parent[maxChambers];
const auto			sourceChamber = 1;

bool canReachBottomChamber() 
{
	memset(visitedInCurrentPath, false, sizeof visitedInCurrentPath);
	queue<int> queue;
	queue.push(sourceChamber);

	while (!queue.empty())
	{
		auto currentChamber = queue.front();
		queue.pop();

		if (currentChamber == chambersN)
			return true;
		if(visitedInCurrentPath[currentChamber])
			continue;

		visitedInCurrentPath[currentChamber] = true;
		for (auto deeperChamber = 1; deeperChamber <= chambersN; deeperChamber++)
		{
			if (visitedInCurrentPath[deeperChamber] || residualCapacityOfEdge[currentChamber][deeperChamber] == 0)
				continue;

			queue.push(deeperChamber);
			parent[deeperChamber] = currentChamber;
		}
	}
	return false;
}

int getAugmentedPathCost()
{
	for (auto currentChamber = chambersN; currentChamber > 1; currentChamber = parent[currentChamber])
	{
		auto previousChamber = parent[currentChamber];
		residualCapacityOfEdge[previousChamber][currentChamber]--;
		residualCapacityOfEdge[currentChamber][previousChamber]++;
	}

	return 1;
}

int maxFlow()
{
	auto maxFlow = 0;
	while(canReachBottomChamber())
		maxFlow += getAugmentedPathCost();
	return maxFlow;
}

int main()
{
	int tests, corridorsN, adjacentChamber;
	scanf("%d", &tests);
	
	while(tests--)
	{
		scanf("%d", &chambersN);
		tree = vector<vector<int>>(chambersN + 1, vector<int>());
		memset(residualCapacityOfEdge, 0, sizeof residualCapacityOfEdge);

		for(auto i = 0; i < chambersN - 1; i++)
		{
			scanf("%d", &corridorsN);
			auto chamber = i + 1;
			while(corridorsN--)
			{
				scanf("%d", &adjacentChamber);
				tree[chamber].push_back(adjacentChamber);
				residualCapacityOfEdge[chamber][adjacentChamber] = i == 0 || adjacentChamber == chambersN ? 1 : maxChambers * maxChambers;
			}
		}
		printf("%d\n", maxFlow());
	}
	return 0;
}