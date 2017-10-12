#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

#define turtleStatesN 4
#define maxTurtlesN   21

enum turtle_state
{
	active  = 0, 
	dormant = 1, 
	bruised = 2
};

using namespace std;

int turtlesN = 1;
int turtleTransitionCost[maxTurtlesN][turtleStatesN];
int minimumCrossingCost[maxTurtlesN][turtleStatesN];

map<turtle_state, vector<turtle_state>> possibleStates = {
	{ active,  { dormant, bruised } },
	{ dormant, { active,  bruised } },
	{ bruised, { dormant, active  } }
};

int min(const int a, const int b, const int c)
{
	return min(a, min(b, c));
}

int computeMinimumCrossingCost(const int currentTurtleIx, const turtle_state currentTurtleState)
{
	if (currentTurtleIx == turtlesN)
		return minimumCrossingCost[currentTurtleIx][currentTurtleState] = 0;
	if (currentTurtleIx == turtlesN - 1)
		return minimumCrossingCost[currentTurtleIx][currentTurtleState] = min(
			turtleTransitionCost[currentTurtleIx][active],
			turtleTransitionCost[currentTurtleIx][dormant],
			turtleTransitionCost[currentTurtleIx][bruised]
		);

	if (minimumCrossingCost[currentTurtleIx][currentTurtleState] != -1)
		return minimumCrossingCost[currentTurtleIx][currentTurtleState];

	return minimumCrossingCost[currentTurtleIx][currentTurtleState] = turtleTransitionCost[currentTurtleIx][currentTurtleState] + min(
		computeMinimumCrossingCost(currentTurtleIx + 1, possibleStates[currentTurtleState][0]),
		computeMinimumCrossingCost(currentTurtleIx + 1, possibleStates[currentTurtleState][1])
	);
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%d", &turtlesN);

		for(auto turtle = 0; turtle < turtlesN; turtle++)
			for(int state = active; state <= bruised; state++)		
				scanf("%d", &turtleTransitionCost[turtle][state]);		

		memset(minimumCrossingCost, -1, sizeof minimumCrossingCost);

		 const auto minimumCrossingCost = min(
			computeMinimumCrossingCost(0, active),
			computeMinimumCrossingCost(0, dormant),
			computeMinimumCrossingCost(0, bruised)
		);

		printf("%d\n", minimumCrossingCost);
	}
	return 0;
}