#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, bool> edge;

#define planet      first
#define isUsed      second
#define maxPlanetsN 30012

#define naboo       1
#define tattoine    2
#define coruscant   3

int             planetsN, connectionsN;
vector<edge>    graph[maxPlanetsN];
bool            visitedPlanet[maxPlanetsN];

bool canReachDestination(int currentPlanet, int destinationPlanet)
{
	if (currentPlanet == destinationPlanet)
		return true;
	if (visitedPlanet[currentPlanet])
		return false;

	visitedPlanet[currentPlanet] = true;

	for (int i = 0; i < graph[currentPlanet].size(); i++)
	{
		if (graph[currentPlanet][i].isUsed)
			continue;

		graph[currentPlanet][i].isUsed = true;
		bool canReachDestinationFromNext = canReachDestination(graph[currentPlanet][i].planet, destinationPlanet);

		if (canReachDestinationFromNext)
			return true;
		else
			graph[currentPlanet][i].isUsed = false;
	}
	return false;
}

inline bool canReachDestinationFromSourcePlanet(int source, int destination) {
	memset(visitedPlanet, false, sizeof visitedPlanet);
	return canReachDestination(source, destination);
}

int main()
{
	int tests, source, destination;

	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &planetsN, &connectionsN);
		for (int planet = 1; planet <= planetsN; planet++)
			graph[planet].clear();

		for (int connection = 0; connection < connectionsN; connection++)
		{
			scanf("%d %d", &source, &destination);
			if (source <= 0 || destination <= 0 || source > planetsN || destination > planetsN)
				continue;

			graph[source].push_back(make_pair(destination, false));
			graph[destination].push_back(make_pair(source, false));
		}

		if (canReachDestinationFromSourcePlanet(tattoine, naboo) && canReachDestinationFromSourcePlanet(tattoine, coruscant))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}