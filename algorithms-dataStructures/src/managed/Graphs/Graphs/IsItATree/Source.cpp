#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<numeric>

using namespace std;

enum color
{
	white,
	grey,
	black
};

typedef pair<int, int> adjacency;
unordered_map<int, vector<int>> graph;
unordered_map<int, color>		state;
unordered_set<int>				nodes;
vector<adjacency>				edges;
vector<int>						emptyAdjs;
int								blackCount = 0;
int								nodesN, edgesN;

bool isTreeFlag = true;
void dfs(int currentNode)
{
	state[currentNode] = grey;
	for(int i = 0; i< graph[currentNode].size() && isTreeFlag; i++)
	{
		if (state[graph[currentNode].at(i)] == black)
		{
			isTreeFlag = false;
			return;
		}
		if(state[graph[currentNode].at(i)] == white)
			dfs(graph[currentNode].at(i));
	}
	blackCount++;
	state[currentNode] = black;
}

bool isTree()
{
	if(nodesN == 1)
		return true;
	dfs(*nodes.begin());
	if(!isTreeFlag)
		return false;
	return blackCount == nodesN;
}

int main()
{
	cin >> nodesN >> edgesN;
	int lhs, rhs;

	for(int i = 0; i < edgesN; i++)
	{
		cin >> lhs >> rhs;
		nodes.insert(lhs);
		nodes.insert(rhs);
		edges.push_back({ lhs, rhs });
	}

	for (auto node : nodes)
	{
		graph.insert({ node, emptyAdjs });
		state.insert({ node, white });
	}

	for(auto adjacency : edges)
	{
		graph[adjacency.first].push_back(adjacency.second);
		graph[adjacency.second].push_back(adjacency.first);
	}
	cout << (isTree() ? "YES" : "NO");
	return 0;
}