#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef unsigned long long bigint;
bigint hotelsCount, maxSum;
vector<bigint> hotels;

int solve()
{
	bigint currentMax = 0;
	bigint solution = currentMax;
	for(auto hotel : hotels)
	{
		currentMax = max(hotel, currentMax + hotel);
		if(currentMax > maxSum)
		{
			currentMax = 0;
			continue;
		}
		if (currentMax >= solution)
			solution = currentMax;
	}
	return solution;
}


int main() {
	scanf("%d %lld", &hotelsCount, &maxSum);
	hotels.resize(hotelsCount);

	for (auto i = 0; i < hotelsCount; i++)
		scanf("%lld", &hotels[i]);

	auto sol = solve();

	printf("%d", sol);
}