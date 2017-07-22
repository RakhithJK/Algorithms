#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define mixturesN		105
#define infinity		LONG_MAX / 2
#define generatedSmoke	second
#define color			first

typedef unsigned long long bigint;

bigint			generatedSmokeOfMixingMixtures[mixturesN][mixturesN];
bigint			generatedColorOfMixingMixtures[mixturesN][mixturesN];

int				mixturesCount;
vector<bigint>	mixtures;

int calculateColorForRange(int intervalStart, int intervalEnd)
{
	auto resultingColor = 0;
	for(auto i = intervalStart; i <= intervalEnd; i++)
	{
		resultingColor = (resultingColor + mixtures[i]) % 100;
	}
	return resultingColor;
}

bigint calculateCostOfMixing(int mixtureIntervalStart = 0, int mixtureIntervalEnd = mixturesCount -1)
{
	if (mixtureIntervalStart == mixtureIntervalEnd)
		return 0;

	if (generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd] != 0)
		return generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd];

	generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd] = infinity;

	for (auto intervalSplit = mixtureIntervalStart; intervalSplit < mixtureIntervalEnd; intervalSplit++)
	{
		auto leftMixtureCost   = calculateCostOfMixing(mixtureIntervalStart, intervalSplit);
		auto rightMixtureCost  = calculateCostOfMixing(intervalSplit + 1, mixtureIntervalEnd);
		auto leftMixtureColor  = calculateColorForRange(mixtureIntervalStart, intervalSplit);
		auto rightMixtureColor = calculateColorForRange(intervalSplit + 1, mixtureIntervalEnd);

		generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd] = min(
			generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd],
			leftMixtureCost + rightMixtureCost + leftMixtureColor * rightMixtureColor
		);	
	} 

	return generatedSmokeOfMixingMixtures[mixtureIntervalStart][mixtureIntervalEnd];
}

int main()
{
	while (scanf("%d", &mixturesCount) > 0)
	{
		mixtures = vector<bigint>(mixturesCount);
		for (auto i = 0; i < mixturesCount; i++)
			scanf("%lld", &mixtures[i]);

		memset(generatedSmokeOfMixingMixtures, 0, sizeof generatedSmokeOfMixingMixtures);
		printf("%lld\n", calculateCostOfMixing());
	}

	return 0;
}