#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<map>
#include<vector>

using namespace std;

vector<int>					emptyAdjacencies;
vector<pair<int, int>>		adjacencies;
map<int, vector<int>>		graph;

int numberOfNodes;
int longestDistanceNode;
int longestDistance = -1;

set<int> nodes;
set<int> visited;

void dfs(int currentNode, int nodeDistance)
{
	if(nodeDistance >= longestDistance)
	{
		longestDistanceNode = currentNode;
		longestDistance		= nodeDistance;
	}

	visited.insert(currentNode);

	for(auto adjacentNode : graph[currentNode])
	{
		if(visited.find(adjacentNode) == visited.end())
		{
			dfs(adjacentNode, nodeDistance + 1);
		}
	}
}

int calculateLongestPathInTree()
{
	for(auto node : graph)
	{
		if (visited.find(node.first) == visited.end())
			dfs(node.first, 0);
	}

	visited.clear();
	longestDistance = -1;
	dfs(longestDistanceNode, 0);

	return longestDistance;
}

int main()
{
	scanf("%d", &numberOfNodes);

	for(int i = 0 ; i < numberOfNodes - 1; i++)
	{
		int lhs, rhs;
		scanf("%d %d", &lhs, &rhs);
		nodes.insert(lhs);
		nodes.insert(rhs);
		adjacencies.push_back({ lhs, rhs });
	}

	for(auto node : nodes)
		graph.insert({ node, emptyAdjacencies });
	
	for(auto adjacency : adjacencies)
	{
		graph[adjacency.first].push_back(adjacency.second);
		graph[adjacency.second].push_back(adjacency.first);
	}

	printf("%d", calculateLongestPathInTree());
	return 0;
}