#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<set>
#include<map>
#include<vector>

using namespace std;

set<pair<int,int>>					emptyAdjacencies;
vector<pair<pair<int,int>, int>>	adjacencies;
map<int, set<pair<int,int>>>		graph;

int  numberOfTests;
int  numberOfAdjacencies;
int  longestDistanceNode;
long longestDistance = -1;

set<int> nodes;
set<int> visited;

void dfs(int currentNode, int nodeDistance)
{
	if (nodeDistance >= longestDistance)
	{
		longestDistanceNode = currentNode;
		longestDistance = nodeDistance;
	}

	visited.insert(currentNode);

	for (auto adjacentNode : graph[currentNode])
	{
		if (visited.find(adjacentNode.first) == visited.end())
		{
			dfs(adjacentNode.first, nodeDistance + adjacentNode.second);
		}
	}
}

long calculateLongestPath()
{
	for(auto node : nodes)
	{
		if (visited.find(node) == visited.end())
			dfs(node, 0);
	}

	visited.clear();
	longestDistance = -1;

	dfs(longestDistanceNode, 0);
	return longestDistance;
}

int main ()
{
	vector<long> lengths;

	scanf("%d", &numberOfTests);

	for(int t = 0; t < numberOfTests; t++)
	{
		scanf("%d", &numberOfAdjacencies);

		longestDistance = -1;
		nodes.clear();
		visited.clear();
		graph.clear();
		adjacencies.clear();

		for (int i = 0; i < numberOfAdjacencies - 1; i++)
		{
			int lhs, rhs, weight;
			scanf("%d %d %d", &lhs, &rhs, &weight);
			adjacencies.push_back({ { lhs, rhs }, weight });
			adjacencies.push_back({ { rhs, lhs }, weight });
			nodes.insert(lhs);
			nodes.insert(rhs);
		}

		for (auto node : nodes)
		{
			graph.insert({ node, emptyAdjacencies });
		}

		for (auto adjacency : adjacencies)
		{
			graph[adjacency.first.first].insert({ adjacency.first.second, adjacency.second });
			graph[adjacency.first.second].insert({ adjacency.first.first, adjacency.second });
		}

		calculateLongestPath();
		lengths.push_back(longestDistance);
	}


	for(auto length : lengths)
	{
		printf("%d \n", length);
	}
	return 0;
}