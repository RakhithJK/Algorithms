#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <climits>
using namespace std;
typedef pair<int, int> edge;
typedef pair<int, int> state;
#define city first
#define cost second
#define infinity INT_MAX
vector<vector<edge>> graph;
unordered_set<int >mst;
int citiesN;

int calculateNetworkCost() {
	auto smallestCostFirst = [&](const edge&lhs, const edge&rhs) { return lhs.cost > rhs.cost; };
	auto isInMst = [&](const int city) { return mst.find(city) != mst.end(); };
	auto networkCost = 0;

	priority_queue<edge, vector< edge>, decltype(smallestCostFirst)> pq(smallestCostFirst);
	vector<int> pathToCity(citiesN + 1, infinity);
	pq.push(make_pair(1, 0));
	pathToCity[1] = 0;
	while (mst.size() < citiesN) {
		auto currentCity = pq.top().city;
		auto currentCityCost = pq.top().cost;
		pq.pop();
		if(isInMst(currentCity))
			continue;
		mst.insert(currentCity);
		networkCost += currentCityCost;
		for(auto edge : graph[currentCity])
		{
			if (!isInMst(edge.city) && edge.cost < pathToCity[edge.city])
			{
				pathToCity[edge.city] = edge.cost;
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
		mst.clear();
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