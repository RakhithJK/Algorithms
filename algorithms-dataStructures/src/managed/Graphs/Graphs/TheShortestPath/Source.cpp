#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<climits>
#include<array>
#include<cstring>
#include<queue>
#include <functional>
using namespace std;

struct way
{
	int destination;
	int cost;
};
struct city
{
	string name;
	vector<way> adjacent;
};
typedef pair<int, int> vertex_distance;
struct vertex_distance_comparer
{
	bool operator()(const vertex_distance& lhs, const vertex_distance& rhs) const
	{
		return lhs.second > rhs.second;
	}
};

array<bool, 10001> visited;
array<int, 10001> distances;
array<int, 10001> emptyDistances;

const int infinity = INT_MAX / 2;

unordered_map<string, int> cityId;
unordered_map<int, city> graph;

void dijkstra(int source, int destination)
{
	priority_queue<vertex_distance, vector <vertex_distance>, vertex_distance_comparer> verticesToVisit;
	verticesToVisit.push({ source , 0 });
	distances[source] = 0;
	while (!verticesToVisit.empty())
	{
		auto currentVertex = verticesToVisit.top().first;
		visited[currentVertex] = true;
		verticesToVisit.pop();

		if(currentVertex == destination)
			return;

		for (auto adjacency : graph[currentVertex].adjacent)
		{
			if (!visited[adjacency.destination] && distances[currentVertex] + adjacency.cost < distances[adjacency.destination])
			{
				distances[adjacency.destination] = distances[currentVertex] + adjacency.cost;
				verticesToVisit.push({ adjacency.destination, distances[adjacency.destination] });
			}
		}
	}
}
int main()
{
	int tests;
	int citiesN;
	int relationsN;
	int paths;
	string name;
	cin >> tests;

	for (int t = 0; t < tests; t++)
	{
		cityId.clear();
		graph.clear();
		cin >> citiesN;
		for(int c = 1; c <= citiesN; c++)
		{
			distances[c] = infinity;
			emptyDistances[c] = infinity;

			city city;
			cin >> city.name;
			graph[c] = city;
			cityId[city.name] = c;
			cin >> relationsN;

			for(int r = 0; r < relationsN; r++)
			{
				way way1;
				cin >> way1.destination >> way1.cost;
				graph[c].adjacent.push_back(way1);
				way way2 = way1;
				way2.destination = c;
				graph[way2.destination].adjacent.push_back(way2);
			}

		}

		cin >> paths;

		for (int p = 0; p < paths; p++)
		{
			string source, destination;
			cin >> source >> destination;
			distances = emptyDistances;
			fill(visited.begin(), visited.end(), false);
			dijkstra(cityId[source], cityId[destination]);
			cout << distances[cityId[destination]] << endl;
		}
	}
	
	return 0;
}