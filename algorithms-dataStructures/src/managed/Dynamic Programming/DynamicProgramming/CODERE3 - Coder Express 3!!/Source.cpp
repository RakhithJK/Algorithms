#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int			buildingsN;
vector<int> buildings;

int computeLongestBitonicLength()
{
	vector<int> ldsLengthUpto(buildingsN, 1);
	vector<int> lisLengthUpto(buildingsN, 1);

	for (auto i = 1; i < buildingsN; i++)	
		for (auto j = 0; j < i; j++)
			if (buildings[i] > buildings[j])
				lisLengthUpto[i] = max(lisLengthUpto[i], lisLengthUpto[j] + 1);
			
	reverse(buildings.begin(), buildings.end());

	for (auto i = 1; i < buildingsN; i++)
		for (auto j = 0; j < i; j++)
			if (buildings[i] > buildings[j])
				ldsLengthUpto[i] = max(ldsLengthUpto[i], ldsLengthUpto[j] + 1);
		
	reverse(ldsLengthUpto.begin(), ldsLengthUpto.end());

	auto bitonicSequenceLength = 0;
	for (auto i = 0; i < buildingsN; i++)
		bitonicSequenceLength = max(bitonicSequenceLength, lisLengthUpto[i] + ldsLengthUpto[i] - 1);

	return bitonicSequenceLength;
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d", &buildingsN);
		buildings = vector<int>(buildingsN);

		for (auto i = 0; i < buildingsN; i++)
			scanf("%d", &buildings[i]);

		printf("%d\n", computeLongestBitonicLength());
	}
	return 0;
}