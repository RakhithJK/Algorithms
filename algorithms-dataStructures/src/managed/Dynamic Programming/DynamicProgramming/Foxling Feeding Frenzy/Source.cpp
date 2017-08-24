#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

#define maxDimension 201

using namespace std;

typedef unsigned long long bigint;

struct foxlingPreference
{
	int atLeast;
	int atMost;
};

const int	mod = pow(10, 9) + 7;
int			foxlingsN, crackersN;

vector<foxlingPreference>	preferences;
bigint						waysToDistribute[maxDimension][maxDimension];

bigint computeWaysToDistribute(int currentFoxlingPreference, int remainingCrackers)
{
	if (currentFoxlingPreference == foxlingsN - 1 && 
		remainingCrackers >= preferences[currentFoxlingPreference].atLeast && 
		remainingCrackers <= preferences[currentFoxlingPreference].atMost
	)
		return 1;

	if (currentFoxlingPreference == foxlingsN)
		return 0;

	if (waysToDistribute[currentFoxlingPreference][remainingCrackers] != -1)
		return waysToDistribute[currentFoxlingPreference][remainingCrackers];

	auto currentPreference		  = preferences[currentFoxlingPreference];
	auto numberOfWaysToDistribute = bigint(0);

	for(
		auto crackersToGiveToCurrent = currentPreference.atLeast; 
		crackersToGiveToCurrent <= currentPreference.atMost && crackersToGiveToCurrent <= remainingCrackers; 
		crackersToGiveToCurrent++
	)
	{
		numberOfWaysToDistribute += computeWaysToDistribute(currentFoxlingPreference + 1, remainingCrackers - crackersToGiveToCurrent) % mod;
	}

	return waysToDistribute[currentFoxlingPreference][remainingCrackers] = numberOfWaysToDistribute;
}

int main()
{
	int tests;
	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%d %d", &foxlingsN, &crackersN);

		memset(waysToDistribute, -1, sizeof waysToDistribute);
		preferences = vector<foxlingPreference>(foxlingsN);

		for(auto foxling = 0; foxling < foxlingsN; foxling++)
			scanf("%d %d", &preferences[foxling].atLeast, &preferences[foxling].atMost);

		printf("%lld\n", computeWaysToDistribute(0, crackersN));
	}
	return 0;
}