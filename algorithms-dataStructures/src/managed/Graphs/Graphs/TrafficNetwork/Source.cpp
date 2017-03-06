#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<algorithm>
#include<cstdio>
#include<unordered_map>
#include<queue>
#include<functional>

using namespace std;

int const infinity = 0x3f3f3f3f;
int const maxNodes = 10000 + 5;

typedef pair<int, int> node_state;

enum discovered_type
{
	directed = 0,
	proposed = 1
};

struct edgeOrState
{
	edgeOrState() {}
	edgeOrState(int destination, int cost, discovered_type type = directed)
	{
		this->destination = destination;
		this->cost = cost;
		this->type = type;
	}
	int destination;
	discovered_type type;
	int cost;

	bool operator < (const edgeOrState& other) const {
		return cost > other.cost;
	}
};

unordered_map<int, vector<edgeOrState>> graph;
int distances[maxNodes][2];
bool visited[maxNodes][2];

int tests;
int citiesN;
int oneWayRoadsN;
int proposedN;
int source;
int destination;

bool dijkstra()
{
	for(int i = 0; i < 10002; i++)
	{
		distances[i][0] = infinity;
		distances[i][1] = infinity;
	}
	
	priority_queue<edgeOrState, vector<edgeOrState>> q;
	distances[source][directed] = 0;
	distances[source][proposed] = 0;

	q.push(edgeOrState(source, 0, directed));
	q.push(edgeOrState(source, 0, proposed));

	bool isReachable = false;
	while (!q.empty())
	{
		auto currentState = q.top();
		int currentVertex = currentState.destination;
		int currentType = currentState.type;
		q.pop();

		visited[currentState.destination][currentType] = true;

		if (currentState.destination == destination)
			isReachable = true;

		for(auto edge : graph[currentState.destination])
		{
			if(visited[edge.destination][edge.type])
				continue;

			auto newCost = edge.cost + distances[currentVertex][currentType];
			auto nextNode = edge.destination;
			auto nextType = edge.type;
			if (newCost < distances[nextNode][nextType]) {
				distances[nextNode][nextType] = newCost;
				q.push(edgeOrState(nextNode, newCost, nextType));
			}
		}
		
	}
	return isReachable;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> tests;
	for(int t = 0; t < tests; t++)
	{
		graph.clear();
		cin >> citiesN >> oneWayRoadsN >> proposedN >> source >> destination;

		for(int road = 0; road < oneWayRoadsN; road ++)
		{
			int lhs, rhs, cost;
			cin >> lhs >> rhs >> cost;
			graph[lhs].push_back(edgeOrState(rhs, cost, directed));
		}
		for (int road = 0; road < proposedN; road++)
		{
			int lhs, rhs, cost;
			cin >> lhs >> rhs >> cost;
			graph[lhs].push_back(edgeOrState(rhs, cost, proposed));
			graph[rhs].push_back(edgeOrState(lhs, cost, proposed));
		}

		auto reachable = dijkstra();
		cout << (reachable ? min(distances[destination][0], distances[destination][1]) : -1) << endl;
	}
	return 0;
}