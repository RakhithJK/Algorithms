#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<queue>
#include<climits>
#include<cstdio>
#include<algorithm>

using namespace std;
typedef pair<int, long> street;
#define building first
#define cost second
#define infinity LONG_MAX / 2

int mainBuildingsN, streetsN;
int mstRoot;
vector<vector<street>> graph;

long calculateMstCost()
{
	auto smallestCostFirst = [&](const street&lhs, const street&rhs) { return lhs.cost > rhs.cost; };
	long mstCost = 0;

	priority_queue<street, vector<street>, decltype(smallestCostFirst)> pq(smallestCostFirst);
	vector<long>	costToBuilding(mainBuildingsN + 1, infinity);
	vector<bool>	inMst(mainBuildingsN + 1, false);
	costToBuilding[mstRoot] = 0;
	pq.push({ mstRoot, 0 });
	while(!pq.empty())
	{
		auto currentBuilding = pq.top().building;
		auto costToCurrentBuilding = pq.top().cost;
		pq.pop();
		if(inMst[currentBuilding])
			continue;
		inMst[currentBuilding] = true;
		mstCost += costToCurrentBuilding;
		for(auto adjacent : graph[currentBuilding])
		{
			if(!inMst[adjacent.building] && adjacent.cost < costToBuilding[adjacent.building])
			{
				costToBuilding[adjacent.building] = adjacent.cost;
				pq.push({ adjacent.building, adjacent.cost });
			}
		}
	}
	return mstCost;
}

int main()
{
	int tests, costPerFurlong, building1, building2, distanceInFurlongs;

	scanf("%d", &tests);
	while(tests)
	{
		scanf("%d", &costPerFurlong);
		scanf("%d", &mainBuildingsN);
		scanf("%d", &streetsN);
		graph = vector<vector<street>>(mainBuildingsN + 1);
		mstRoot = INT_MAX / 2;

		for(auto s = 0; s < streetsN; s++)
		{
			scanf("%d %d %ld", &building1, &building2, &distanceInFurlongs);
			graph[building1].push_back({ building2, distanceInFurlongs * costPerFurlong });
			graph[building2].push_back({ building1, distanceInFurlongs * costPerFurlong });
			mstRoot = min(mstRoot, min(building1, building2));
		}
		printf("%ld\n", calculateMstCost());
		tests--;
	}
	return 0;
}