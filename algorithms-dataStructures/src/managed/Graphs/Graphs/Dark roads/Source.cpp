#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<queue>
#include<cstdio>
#include<climits>
#include <map>
using namespace std;

typedef pair<int, int> edge;
#define junction first
#define cost second
#define infinity INT_MAX/2
#define maxN 200001
vector<vector<edge>> graph;
int junctionsN, roadsN;
int roadsCost;
int source;

int calculateMstCost() {
	auto smallestCostEdgeFirst = [](const edge& lhs, const edge& rhs) { return lhs.cost > rhs.cost; };
	priority_queue<edge, vector<edge>, decltype(smallestCostEdgeFirst)> pq(smallestCostEdgeFirst);
	vector<bool>	inMst(maxN, false);
	vector<int>		pathToJunctionCost(maxN, infinity);
	auto			mstCost				  = 0;
	auto			currentJunctionsCount = 0;
	pathToJunctionCost[source]			  = 0;
	pq.push({ source, 0 });

	while(currentJunctionsCount < junctionsN && !pq.empty())
	{
		auto currentJunction = pq.top().junction;
		auto currentJunctionCost = pq.top().cost;
		pq.pop();
		if(inMst[currentJunction])
			continue;
		inMst[currentJunction]  = true;
		mstCost					+= currentJunctionCost;
		currentJunctionsCount++;
		for (auto adjacentEdge : graph[currentJunction]) {
			if(!inMst[adjacentEdge.junction] && adjacentEdge.cost < pathToJunctionCost[adjacentEdge.junction])
			{
				pathToJunctionCost[adjacentEdge.junction] = adjacentEdge.cost;
				pq.push({ adjacentEdge.junction, pathToJunctionCost[adjacentEdge.junction] });
			}
		}
	}
	return mstCost;
}
int main()
{
	scanf("%d %d", &junctionsN, &roadsN);
	int lhs, rhs, cost;
	while(junctionsN != 0 && roadsN != 0)
	{
		graph		= vector<vector<edge>>(maxN);
		roadsCost	= 0;
		source		= infinity;
		for(auto i = 0; i < roadsN; i++)
		{
			scanf("%d %d %d", &lhs, &rhs, &cost);
			graph[lhs].push_back({ rhs,cost });
			graph[rhs].push_back({ lhs,cost });
			source = min(source, min(lhs,rhs));
			roadsCost += cost;
		}
		printf("%d\n", roadsCost - calculateMstCost());
		scanf("%d %d", &junctionsN, &roadsN);
	}
	return 0;
}