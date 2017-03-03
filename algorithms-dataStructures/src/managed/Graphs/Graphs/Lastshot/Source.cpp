#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>

using namespace std;

typedef long long bigint;

int n, m;
unordered_set<int> 				bombs;
unordered_set<int> 				visited;
unordered_map<int, vector<int>> graph;
vector<int> 					emptyRelations;

bigint chainLength;
void dfs(int currentBomb) {
	visited.insert(currentBomb);
	chainLength++;

	for(auto nextBomb : graph[currentBomb])
	{
		if (visited.find(nextBomb) == visited.end())
			dfs(nextBomb);
	}
}

bigint calculateBombChain() {
	auto maxChainLength = -1;
	for(auto bomb : bombs)
	{
		visited.clear();
		chainLength = -1;
		dfs(bomb);
		if (chainLength > maxChainLength)
			maxChainLength = chainLength;
	}
	return maxChainLength + 1;
}

int main ()
{
	cin >> n >> m;
	vector<pair<int, int>> adjacencies;
	for(int i = 0; i < m; i++)
	{
		int lhs, rhs;
		cin >> lhs >> rhs;
		adjacencies.push_back({ lhs, rhs });
		bombs.insert(lhs);
		bombs.insert(rhs);
	}

	for (auto bomb : bombs)
		graph.insert({ bomb, emptyRelations });

	for (auto a : adjacencies)
		graph[a.first].push_back(a.second);

	cout << calculateBombChain();
	return 0;
}