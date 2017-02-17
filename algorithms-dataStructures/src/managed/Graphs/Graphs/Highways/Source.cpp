#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include <string>

using namespace std;

struct highway
{
	int source;
	int destination;
	int cost;
};

typedef pair<int, int> vertex_distance;
struct vertex_distance_comparer
{
	bool operator()(const vertex_distance& lhs, const vertex_distance& rhs) const
	{
		return lhs.second > rhs.second;
	}
};


const int infinity = numeric_limits<int>::max() / 2;

int numberOfTests, 
	numberOfCities,
	numberOfHighways, 
	startingCity, 
	destinationCity;

map<int, vector<highway>> graph;
vector<highway> highways;
set<int> cities;

string computeShortestPathBetweenSourceAndDestination()
{
	priority_queue<vertex_distance, vector <vertex_distance>, vertex_distance_comparer> verticesToVisit;
	vector<int> distance(numberOfCities + 1, infinity);
	verticesToVisit.push({ startingCity , 0 });
	distance[startingCity] = 0;

	while(!verticesToVisit.empty())
	{
		auto currentVertex = verticesToVisit.top().first;
		verticesToVisit.pop();

		for(auto adjacency : graph[currentVertex])
		{
			if(distance[currentVertex] + adjacency.cost < distance[adjacency.destination])
			{
				distance[adjacency.destination] = distance[currentVertex] + adjacency.cost;
				verticesToVisit.push({ adjacency.destination, adjacency.cost });
			}
		}
	}
	return distance[destinationCity] != infinity ? to_string(distance[destinationCity]) : "NONE";
}

int main()
{
	scanf("%d", &numberOfTests);
	vector<highway> emptyConnections;
	vector<string> results;

	for(int t = 0; t < numberOfTests; t++)
	{
		graph.clear();
		highways.clear();
		cities.clear();

		scanf("%d %d %d %d%", &numberOfCities, &numberOfHighways, &startingCity, &destinationCity);
		
		for(int a = 0; a < numberOfHighways; a++)
		{
			int lhs, rhs, cost;
			scanf("%d %d %d", &lhs, &rhs, &cost);

			cities.insert(lhs);
			cities.insert(rhs);

			highway highway1;
			highway1.source = lhs;
			highway1.destination = rhs;
			highway1.cost = cost;

			highway highway2;
			highway2.source = rhs;
			highway2.destination = lhs;
			highway2.cost = cost;

			highways.push_back(highway1);
			highways.push_back(highway2);
		}

		for (auto city : cities)
			graph.insert({ city, emptyConnections });

		for (auto highway : highways)
			graph[highway.source].push_back(highway);

		results.push_back(computeShortestPathBetweenSourceAndDestination());
	}

	for (auto result : results)
		printf("%s \n", result.c_str());

	return 0;
}