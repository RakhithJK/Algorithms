#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;
typedef pair<int, int> edge;
typedef pair<int, int> state;
#define city		first
#define cost		second
#define infinity	INT_MAX

vector<vector<edge>> graph;
int					 citiesN;

int calculateNetworkCost() {
	auto smallestCostFirst = [&](const edge&lhs, const edge&rhs) { return lhs.cost > rhs.cost; };
	auto networkCost       = 0;

	priority_queue<edge, vector<edge>, decltype(smallestCostFirst)> pq(smallestCostFirst);
	vector<int>		pathToCityCost(citiesN + 1, infinity);
	vector<bool>	inMst(citiesN + 1, false);
	auto source			   = 1;
	pathToCityCost[source] = 0;
	pq.push({ source, 0 });

	while(!pq.empty())
	{
		auto currentCity	 = pq.top().city;
		auto currentCityCost = pq.top().cost;
		pq.pop();
		if(inMst[currentCity])
			continue;
		inMst[currentCity] = true;
		networkCost		  += currentCityCost;
		for(auto edge : graph[currentCity])
		{
			if (!inMst[edge.city] && edge.cost < pathToCityCost[edge.city])
			{
				pathToCityCost[edge.city] = edge.cost;
				pq.push({ edge.city, edge.cost });
			}
		}
	}
	return networkCost;
}

int main() {

	int tests, neighbours, lhs, cost;
	char cityName[12];
	scanf("%d", &tests);
	while (tests)
	{
		scanf("%d", &citiesN);
		graph = vector<vector<edge>>(citiesN + 1);
		for (int city = 1; city <= citiesN; city++) {
			scanf("%s", cityName);
			scanf("%d", &neighbours);
			while(neighbours)
			{
				scanf("%d %d", &lhs, &cost);
				graph[city].push_back({ lhs, cost });
				neighbours--;
			}
		}
		printf("%d\n", calculateNetworkCost());
		tests--;
	}
	return 0;
}