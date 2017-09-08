#define _CRT_SECURE_NO_WARNINGS
#define healthCost first
#define armorCost second
#define maxHealthArmor 2001
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

enum position
{
	fire = 0,
	water = 1,
	air = 2
};

map<position, vector<position>> possiblePositionSwitches = {
	{ fire , { water, air  } },
	{ water, { fire, air   } },
	{ air,   { water, fire } }
};

map<position, pair<int,int>> switchCost = {
	{ air, { 3, 2 }},
	{ water, { -5, -10 }},
	{ fire, {-20, 5}}
};

int dp[maxHealthArmor][maxHealthArmor][3];

int computeMaxSurvivalTime(int health, int armor, position position)
{
	if (health <= 0 || armor <= 0)
		return 0;
	if (dp[health][armor][position] != -1)
		return dp[health][armor][position];

	auto nextPositions = possiblePositionSwitches[position];

	return dp[health][armor][position] = max(
		1 + computeMaxSurvivalTime(health + switchCost[nextPositions[0]].healthCost, armor + switchCost[nextPositions[0]].armorCost, nextPositions[0]),
		1 + computeMaxSurvivalTime(health + switchCost[nextPositions[1]].healthCost, armor + switchCost[nextPositions[1]].armorCost, nextPositions[1])
	);
}

int main()
{
	int tests, health, armor;
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%d %d", &health, &armor);
		memset(dp, -1, sizeof dp);

		auto possibleSurvivalTimes = {
			computeMaxSurvivalTime(health, armor, water),
			computeMaxSurvivalTime(health, armor, air),
			computeMaxSurvivalTime(health, armor, fire)
		};

		auto solution = *max_element(possibleSurvivalTimes.begin(), possibleSurvivalTimes.end()) - 1;
		printf("%d\n", solution);
	}
	return 0;
}