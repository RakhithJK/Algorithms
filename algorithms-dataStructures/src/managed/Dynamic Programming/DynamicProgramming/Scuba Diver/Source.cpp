#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define infinity INT_MAX / 2
#define maxCylinders 1024
#define maxGasVolume 100

struct cylinder
{
	int oxygenVolume;
	int nitrogenVolume;
	int weight;

	cylinder() {}
};

int					oxygenDemand, 
					nitrogenDemand, 
					cylindersN;

vector<cylinder>	cylinders;
int					minimumWeightForState[maxCylinders][maxGasVolume][maxGasVolume];

int computeMinimumWeightForDemandsUpto_topDown(
	int currentIx		= 0, 
	int currentOxygen	= 0,
    int currentNytrogen = 0
) 
{
	if (currentOxygen >= oxygenDemand && currentNytrogen >= nitrogenDemand)
		return 0;
	if (currentIx == cylindersN)
		return infinity;

	if (currentOxygen >= oxygenDemand)
		currentOxygen = oxygenDemand;
	if (currentNytrogen >= nitrogenDemand)
		currentNytrogen = nitrogenDemand;

	if (minimumWeightForState[currentIx][currentOxygen][currentNytrogen] != 0)
		return minimumWeightForState[currentIx][currentOxygen][currentNytrogen];

	auto currentCylinder = cylinders[currentIx];

	auto weightIncludingCurrent = computeMinimumWeightForDemandsUpto_topDown(
		currentIx + 1, 
		currentOxygen + currentCylinder.oxygenVolume, 
		currentNytrogen + currentCylinder.nitrogenVolume
	) + currentCylinder.weight;

	auto weightExcludingCurrent = computeMinimumWeightForDemandsUpto_topDown(
		currentIx + 1,
		currentOxygen,
		currentNytrogen
	);

	return minimumWeightForState[currentIx][currentOxygen][currentNytrogen] = min(weightIncludingCurrent, weightExcludingCurrent);
}


int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &oxygenDemand, &nitrogenDemand);
		scanf("%d", &cylindersN);
		cylinders = vector<cylinder>(cylindersN);
		for (auto i = 0; i < cylindersN; i++)
			scanf("%d %d %d", &cylinders[i].oxygenVolume, &cylinders[i].nitrogenVolume, &cylinders[i].weight);

		memset(minimumWeightForState, false, sizeof minimumWeightForState);
		printf("%d\n", computeMinimumWeightForDemandsUpto_topDown());
	}
	return 0;
}