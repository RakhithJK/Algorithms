#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<array>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<climits>
#include<iostream>

using namespace std;

#define infinity INT_MAX / 2
#define maxLocationsN 501

int					graph[maxLocationsN][maxLocationsN];
queue<int>			carsToPickup;
map<string, int>	locationId;
int					locationsN, brokenCarsN, streetsN;
string				garageLocationName;

inline auto nextString()
{
	string s;
	cin >> s;
	return s;
}
inline auto nextInt()
{
	int i;
	cin >> i;
	return i;
}
inline void floyd_warshall()
{
	for (int k = 1; k <= locationsN + 1; k++)
		for (int i = 1; i <= locationsN + 1; i++)
			for (int j = 1; j <= locationsN + 1; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}
inline auto getLocationId_assignIfNeeded(string location)
{
	return locationId.find(location) == locationId.end() ? 
		locationId[location] = locationId.size() + 1	 : 
	    locationId[location];
}
inline auto solve()
{
	auto sum	= 0;
	auto garage = locationId[garageLocationName];
	while (!carsToPickup.empty())
	{
		auto pickupLocationId = carsToPickup.front();
		carsToPickup.pop();
		sum += graph[pickupLocationId][garage] + graph[garage][pickupLocationId];
	}
	return sum;
}
inline void edgify(string lhs, string relationType, string rhs) {
	auto lhsNodeId = getLocationId_assignIfNeeded(lhs);
	auto rhsNodeId = getLocationId_assignIfNeeded(rhs);
	auto cost = 0;
	if(relationType[0] == '<' && relationType[relationType.size() - 1] == '>')
	{
		sscanf(relationType.c_str(), "<-%d->", &cost);
		graph[lhsNodeId][rhsNodeId] = min(graph[lhsNodeId][rhsNodeId], cost);
		graph[rhsNodeId][lhsNodeId] = min(graph[rhsNodeId][lhsNodeId], cost);
	}
	if (relationType[0] == '-') {
		sscanf(relationType.c_str(), "--%d->", &cost);
		graph[lhsNodeId][rhsNodeId] = min(graph[lhsNodeId][rhsNodeId], cost);
	}
	if (relationType[relationType.size() - 1] == '-') {
		sscanf(relationType.c_str(), "<-%d--", &cost);
		graph[rhsNodeId][lhsNodeId] = min(graph[rhsNodeId][lhsNodeId], cost);
	}
}

int main()
{
	locationsN = nextInt(), brokenCarsN = nextInt(), streetsN = nextInt();
	auto testN = 0;
	while (true)
	{
		if(locationsN == 0 && brokenCarsN == 0 && streetsN == 0)
			break;

		testN++;
		for (int i = 1; i <= locationsN + 1; i++)
			for (int j = 1; j <= locationsN + 1; j++)
				graph[i][j] = infinity;

		locationId.clear();
		carsToPickup	   = queue<int>();
		garageLocationName = nextString();

		for (int i = 1; i <= brokenCarsN; i++) 
			carsToPickup.push(getLocationId_assignIfNeeded(nextString()));
		for (int s = 0; s < streetsN; s++)
			edgify(nextString(), nextString(), nextString());
		
		floyd_warshall();
		printf("%d. %d\n", testN, solve());
		locationsN = nextInt(), brokenCarsN = nextInt(), streetsN = nextInt();
	}
	return 0;
}