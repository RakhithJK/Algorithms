#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<array>
#include<climits>
#include<cmath>
using namespace std;

typedef pair<int, int>	state;
#define computer		first
#define distance		second
#define computersMaxN	100000

const int					infinity = INT_MIN;
array<bool, computersMaxN>	visited;
array<int, computersMaxN>	distances;
map<int, vector<int>>		computersNetwork;

void dfs(int current, int currentDistance)
{
	if (visited[current])
		return;

	visited[current]	= true;
	distances[current]	= currentDistance;

	for (auto adjacentComputer : computersNetwork[current])
	{
		if (!visited[adjacentComputer])
			dfs(adjacentComputer, currentDistance + 1);
	}
}

int calculateNumberOfPacketsDfs(map<int, vector<int>> graph)
{
	fill(visited.begin(), visited.end(), false);
	fill(distances.begin(), distances.end(), infinity);
	computersNetwork = graph;

	const int root = 0;
	dfs(root, 0);

	auto longestDistance		= root;
	auto longestDistanceNode	= root;

	for (int i = 0; i < distances.size(); i++)
	{
		if (distances[i] > longestDistance)
		{
			longestDistance		= distances[i];
			longestDistanceNode = i;
		}
	}

	fill(visited.begin(), visited.end(), false);
	fill(distances.begin(), distances.end(), infinity);
	dfs(longestDistanceNode, 0);

	longestDistance = *max_element(distances.begin(), distances.end());
	return (longestDistance % 2 == 0) ? (longestDistance / 2) : ((longestDistance + 1) / 2);
}

int main()
{
	int tests;
	cin >> tests;

	while (tests)
	{
		int computersN;
		cin >> computersN;
		map<int, vector<int>> graph;
		for (int i = 0; i < computersN - 1; i++)
		{
			int lhs, rhs;
			cin >> lhs >> rhs;
			graph[lhs].push_back(rhs);
			graph[rhs].push_back(lhs);
		}
		cout << calculateNumberOfPacketsDfs(graph) << endl;
		graph.clear();
		tests--;
	}
	return 0;
}