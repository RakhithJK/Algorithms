#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<algorithm>
#include<climits>
#include<cstdio>
using namespace std;
#define infinity INT_MAX / 2

vector<vector<int>> islandsGraph;
vector<int>			lowLinkOf;
vector<int>			discoveryTimeOf;
vector<int>			parentOf;
vector<bool>		isArticulationPoint;
vector<bool>		visited;

int islandsN, bridgesN;
int currentTime;

int computeLowlink(int island)
{
	lowLinkOf[island]		= discoveryTimeOf[island] = ++currentTime;
	visited[island]			= true;
	auto disconnectedChildrenCount	= 0;

	for(auto adjacent : islandsGraph[island])
	{
		if(!visited[adjacent])
		{
			disconnectedChildrenCount++;
			parentOf[adjacent] = island;
			lowLinkOf[island] = min(lowLinkOf[island], computeLowlink(adjacent));

			if (parentOf[island] == infinity && disconnectedChildrenCount > 1)
				isArticulationPoint[island] = true;

			if (parentOf[island] != infinity && discoveryTimeOf[island] <= lowLinkOf[adjacent])
				isArticulationPoint[island] = true;
		}
		else if (adjacent != parentOf[island])
			lowLinkOf[island] = min(lowLinkOf[island], discoveryTimeOf[adjacent]);
	}
	return lowLinkOf[island];
}

auto computeArticulationPoints()
{
	currentTime			= 0;
	visited				= vector<bool>	(islandsN + 1, false);
	lowLinkOf  			= vector<int>	(islandsN + 1, infinity);
	discoveryTimeOf		= vector<int>	(islandsN + 1, infinity);
	parentOf			= vector<int>	(islandsN + 1, infinity);
	isArticulationPoint = vector<bool>	(islandsN + 1, false);

	for (auto island = 1; island <= islandsN; island++)
		if (!visited[island])
			computeLowlink(island);
	
	return count(isArticulationPoint.begin(), isArticulationPoint.end(), true);
}

int main()
{
	scanf("%d %d", &islandsN, &bridgesN);
	while(islandsN != 0 && bridgesN != 0)
	{
		islandsGraph		= vector<vector<int>>(islandsN + 1);
		for (int b = 0; b < bridgesN; b++)
		{
			int sourceIsland, destinationIsland;
			scanf("%d %d", &sourceIsland, &destinationIsland);
			islandsGraph[sourceIsland].push_back(destinationIsland);
			islandsGraph[destinationIsland].push_back(sourceIsland);
		}
		printf("%d \n", computeArticulationPoints());
		scanf("%d %d", &islandsN, &bridgesN);
	}
	return 0;
}