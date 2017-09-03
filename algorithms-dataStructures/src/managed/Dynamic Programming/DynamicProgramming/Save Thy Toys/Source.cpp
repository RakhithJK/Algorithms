#define _CRT_SECURE_NO_WARNINGS
#define maxToysN 100001

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long bigint;

int		toysN;
bigint	maxSavedValueFrom[maxToysN];
bigint	toyValue[maxToysN];

inline bigint toyValueAt(int toyIx) { return toyIx < toysN ? toyValue[toyIx] : 0; }

bigint computeMaxSavedValueFrom(int currentToyIndex)
{
	if (currentToyIndex >= toysN)
		return bigint(0);
	if (maxSavedValueFrom[currentToyIndex] != -1)
		return maxSavedValueFrom[currentToyIndex];

	auto possibleStrategiesSavedValues = {
		toyValueAt(currentToyIndex) + computeMaxSavedValueFrom(currentToyIndex + 2),
		toyValueAt(currentToyIndex) + toyValueAt(currentToyIndex + 1) + computeMaxSavedValueFrom(currentToyIndex + 4),
		toyValueAt(currentToyIndex) + toyValueAt(currentToyIndex + 1) + toyValueAt(currentToyIndex + 2) + computeMaxSavedValueFrom(currentToyIndex + 6)
	};

	return maxSavedValueFrom[currentToyIndex] = *max_element(possibleStrategiesSavedValues.begin(), possibleStrategiesSavedValues.end());
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%d", &toysN);
		for(auto i = 0; i < toysN; i++)
			scanf("%d", &toyValue[i]);
		memset(maxSavedValueFrom, -1, sizeof maxSavedValueFrom);
		printf("%lld\n", computeMaxSavedValueFrom(0));
	}
	return 0;
}