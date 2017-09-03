#define _CRT_SECURE_NO_WARNINGS

#define mod 10007
#define maxJunctions 100015

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int					junctionsN;
vector<vector<int>> treeOf;

bool	visitedInCurrentPath[maxJunctions];
int		lookup[maxJunctions][2];
int		ways[maxJunctions][2];
int		computeMinLights(int currentJunction, bool shouldLightJunction);

inline void computeWays(int nextJunction, int currentJunction, bool shouldLightJunction)
{
	if(shouldLightJunction) 
	{
		if (computeMinLights(nextJunction, false) == computeMinLights(nextJunction, true))
			ways[currentJunction][shouldLightJunction] = (ways[currentJunction][shouldLightJunction] * (ways[nextJunction][false] + ways[nextJunction][true])) % mod;
		else if (computeMinLights(nextJunction, false) < computeMinLights(nextJunction, true))
			ways[currentJunction][shouldLightJunction] = (ways[currentJunction][shouldLightJunction] * (ways[nextJunction][false])) % mod;
		else
			ways[currentJunction][shouldLightJunction] = (ways[currentJunction][shouldLightJunction] * (ways[nextJunction][true])) % mod;
	}
	else
		ways[currentJunction][shouldLightJunction] = (ways[currentJunction][shouldLightJunction] * ways[nextJunction][true]) % mod;

}
int computeMinLights(int currentJunction, bool shouldLightJunction)
{
	if (lookup[currentJunction][shouldLightJunction] != -1)
		return lookup[currentJunction][shouldLightJunction];

	visitedInCurrentPath[currentJunction]		= true;
	ways[currentJunction][shouldLightJunction]  = 1;

	if (shouldLightJunction)
	{
		auto minNumberOfLights = 1;
		for (auto nextJunction : treeOf[currentJunction])
		{
			if (visitedInCurrentPath[nextJunction])
				continue;

			visitedInCurrentPath[nextJunction] = true;
			minNumberOfLights				  += min(
				computeMinLights(nextJunction, false),
				computeMinLights(nextJunction, true)
			);
			computeWays(nextJunction, currentJunction, shouldLightJunction);	
			visitedInCurrentPath[nextJunction] = false;
		}

		return lookup[currentJunction][shouldLightJunction] = minNumberOfLights;
	}

	auto minNumberOfLights = 0;
	for (auto nextJunction : treeOf[currentJunction])
	{
		if (visitedInCurrentPath[nextJunction])
			continue;

		visitedInCurrentPath[nextJunction] = true;
		minNumberOfLights += computeMinLights(nextJunction, true);
		computeWays(nextJunction, currentJunction, shouldLightJunction);
		visitedInCurrentPath[nextJunction] = false;
	}

	visitedInCurrentPath[currentJunction] = false;
	return lookup[currentJunction][shouldLightJunction] = minNumberOfLights;
}

int main()
{
	int tests, source, destination;
	
	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%d", &junctionsN);
		treeOf = vector<vector<int>>(junctionsN + 1, vector<int>());

		memset(visitedInCurrentPath, false, sizeof visitedInCurrentPath);
		memset(lookup, -1, sizeof lookup);
		memset(ways, -1, sizeof ways);

		for (auto edge = 0; edge < junctionsN - 1; edge++)
		{
			scanf("%d %d", &source, &destination);
			treeOf[source].push_back(destination);
			treeOf[destination].push_back(source);
		}

		auto minimalNumberOfLights = min(
			computeMinLights(1, true),
			computeMinLights(1, false)
		);

		auto waysWithMinLightsCount = 1;

		if (computeMinLights(1, false) == computeMinLights(1, true))
			waysWithMinLightsCount = (waysWithMinLightsCount* (ways[1][false] + ways[1][true])) % mod;
		else if (computeMinLights(1, false) < computeMinLights(1, true))
			waysWithMinLightsCount = (waysWithMinLightsCount * (ways[1][false])) % mod;
		else
			waysWithMinLightsCount = (waysWithMinLightsCount * (ways[1][true])) % mod;

		printf("%d %d\n", minimalNumberOfLights, waysWithMinLightsCount);
	}
	return 0;
}