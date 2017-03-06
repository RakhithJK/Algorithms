#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<array>
#include<unordered_map>
#include<cstring>

using namespace std;
#define nodesCount			10002
#define discovered_byCount	2
#define infinity			1061109567

enum   discovered_by
{
	direct = 0,
	proposed = 1
};
struct path_state
{
	int destination;
	int cost;
	discovered_by discoveredBy;

	path_state() {}
	path_state(int destination, int cost, discovered_by discBy)
	{
		this->destination = destination;
		this->cost = cost;
		this->discoveredBy = discBy;
	}

	bool operator < (path_state& other) const {
		return cost > other.cost;
	}
};
struct path_state_comparer
{
	bool operator () (path_state& lhs, path_state& rhs) const {
		return lhs.cost > rhs.cost;
	}
};
struct adjacency
{
	adjacency() {}
	adjacency(int adjacent, int cost, discovered_by adjacencyType)
	{
		this->adjacent = adjacent;
		this->cost = cost;
		this->adjacencyType = adjacencyType;
	}

	int adjacent;
	int cost;
	discovered_by adjacencyType;

	bool operator < (const adjacency& other) const {
		return cost < other.cost;
	}
	bool operator == (const adjacency& other) const {
		return adjacent == other.adjacent && cost == other.cost && adjacencyType == other.adjacencyType;
	}
};

unordered_map<int, vector<adjacency>> graph;

int dijkstra(int source, int destination) {
	priority_queue<path_state, vector<path_state>, path_state_comparer> q;
	int dist[nodesCount][discovered_byCount];

	for(int i = 0; i < nodesCount; i++)
	{
		dist[i][direct]   = infinity;
		dist[i][proposed] = infinity;
	}

	bool reachable = false;
	dist[source][direct] = 0;
	q.push(path_state(source, 0, direct));
	
	while(!q.empty())
	{
		auto current = q.top();
		q.pop();

		if(current.destination == destination)
		{
			reachable = true;
			continue;
		}

		for (auto edge : graph[current.destination])
		{
			if (!(current.discoveredBy == proposed && edge.adjacencyType == proposed))
			{
				auto edgeType = static_cast<discovered_by>(current.discoveredBy || edge.adjacencyType);

				if(dist[current.destination][current.discoveredBy] + edge.cost < dist[edge.adjacent][edgeType]) //relax
				{
					dist[edge.adjacent][edgeType] = dist[current.destination][current.discoveredBy] + edge.cost;
					q.push(path_state(edge.adjacent, edge.cost, edgeType));
				}
			}
		}
	}

	return reachable ? min(dist[destination][direct], dist[destination][proposed]) : -1;
}

int main() {
	int tests, nodesN, directRoadsN, proposedRoadsN, source, destination, lhs, rhs, cost;
	scanf("%d", &tests);
	while (tests--) {
		graph.clear();
		scanf("%d %d %d %d %d", &nodesN, &directRoadsN, &proposedRoadsN, &source, &destination);
		for (int i = 0; i < directRoadsN; i++) {
			scanf("%d %d %d", &lhs, &rhs, &cost);
			graph[lhs].push_back(adjacency(rhs, cost, direct));
		}
		for (int i = 0; i < proposedRoadsN; i++) {
			scanf("%d %d %d", &lhs, &rhs, &cost);
			graph[lhs].push_back(adjacency(rhs, cost, proposed));
			graph[rhs].push_back(adjacency(lhs, cost, proposed));
		}
		printf("%d\n", dijkstra(source, destination));
	}
	return 0;
}