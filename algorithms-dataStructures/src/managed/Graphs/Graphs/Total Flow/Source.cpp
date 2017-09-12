#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <climits>

using namespace std;

#define maxPipes	701
#define infinity	INT_MAX / 2

int					residualCapacity[maxPipes][maxPipes];
bool				visitedInCurrentPath[maxPipes];
int					parent[maxPipes];
const auto			source = 'A';
const auto			sink   = 'Z';

unordered_map<char, vector<char>> network;

bool canReachBottomChamber()
{
	memset(visitedInCurrentPath, false, sizeof visitedInCurrentPath);
	memset(parent, 0, sizeof parent);
	queue<char> queue;
	queue.push(source);

	while (!queue.empty())
	{
		auto currentEndpoint = queue.front();

		queue.pop();

		if (currentEndpoint == sink)
			return true;
		
		if (visitedInCurrentPath[currentEndpoint])
			continue;

		visitedInCurrentPath[currentEndpoint] = true;
		for (auto nextEndpoint : network[currentEndpoint])
		{
			if (visitedInCurrentPath[nextEndpoint] || residualCapacity[currentEndpoint][nextEndpoint] <= 0)
				continue;

			queue.push(nextEndpoint);
			parent[nextEndpoint] = currentEndpoint;
		}
	}
	return false;
}

int getAugmentedPathCost()
{
	auto currentNode		= sink;
	auto bottleneckCapacity = infinity;
	while (currentNode != 0)
	{
		bottleneckCapacity	= currentNode != source ? min(bottleneckCapacity, residualCapacity[parent[currentNode]][currentNode]) : bottleneckCapacity;
		currentNode			= parent[currentNode];
	}

	currentNode = sink;
	while (currentNode != 0)
	{
		residualCapacity[parent[currentNode]][currentNode] -= bottleneckCapacity;
		residualCapacity[currentNode][parent[currentNode]] += bottleneckCapacity;
		currentNode											= parent[currentNode];
	}
	return bottleneckCapacity;
}

int maxFlow()
{
	auto maxFlow = 0;
	while (canReachBottomChamber())
		maxFlow += getAugmentedPathCost();
	return maxFlow;
}

int main()
{
	char source, destination;
	int capacity;

	int pipesN;
	cin >> pipesN;

	for(auto i = 0; i < pipesN; i++)
	{
		cin >> source >> destination >> capacity;
		residualCapacity[source][destination] += capacity;
		network[source].push_back(destination);
		network[destination].push_back(source);
	}

	cout << maxFlow();
	return 0;
}