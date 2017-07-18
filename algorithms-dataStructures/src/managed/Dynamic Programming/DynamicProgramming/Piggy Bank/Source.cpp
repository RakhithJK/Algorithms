#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef unsigned long long bigint;

#define infinity INT_MAX / 2

struct coin
{
	int weight;
	int value;

	coin() {}
};

int tests;
int emptyWeight, fullWeight, coinsN;

vector<coin> coinTypes;

int dp[10100];

int calculateMinSizeForWeight_topDown(int availableWeight)
{
	if (availableWeight <= 0)
		return 0;
	
	if (dp[availableWeight] != 0)
		return dp[availableWeight];

	dp[availableWeight] = infinity;
	for (auto coin : coinTypes)
	{
 		if (availableWeight - coin.weight < 0)
			continue;
		dp[availableWeight] = min(dp[availableWeight], calculateMinSizeForWeight_topDown(availableWeight - coin.weight) + coin.value);
	}
	return dp[availableWeight];
}


int main() {
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%d %d", &emptyWeight, &fullWeight);
		scanf("%d", &coinsN);

		coinTypes.clear();
		coinTypes.resize(coinsN);
		for(auto i = 0; i < coinsN; i++)
			scanf("%d %d", &coinTypes[i].value, &coinTypes[i].weight);

		if (emptyWeight > fullWeight)
			printf("This is impossible.\n");
		memset(dp, false, sizeof dp);

		auto sol = calculateMinSizeForWeight_topDown(fullWeight - emptyWeight);
		if(sol == infinity)
			printf("This is impossible.\n");
		else
			printf("The minimum amount of money in the piggy-bank is %d.\n", sol);
	}
}