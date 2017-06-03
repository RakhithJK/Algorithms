#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <array>
#include <vector>
#include <numeric>

using namespace std;

vector<int> sticks;
typedef unsigned long long bigint;

bigint findAllGreaterOrEqualThan(int twoSidesSum)
{
	auto smallestGreaterSide = upper_bound(sticks.begin(), sticks.end(), twoSidesSum);
	if (smallestGreaterSide == sticks.end())
		return 0;
	return sticks.end() - smallestGreaterSide;
}

bigint calculateTrianglesCount()
{
	vector<int> twoSidesSums;
	sort(sticks.begin(), sticks.end());

	for(auto i = 0; i < sticks.size(); i++)	
		for(auto j = i + 1; j < sticks.size(); j++)		
			twoSidesSums.push_back(sticks[i] + sticks[j]);

	return accumulate(twoSidesSums.begin(), twoSidesSums.end(), bigint(0), [](bigint result, int current) { return result + findAllGreaterOrEqualThan(current); });
}

int main()
{
	int sticksN, stick;
	scanf("%d", &sticksN);
	while(sticksN)
	{
		for(auto i = 0; i < sticksN; i++)
		{
			scanf("%d", &stick);
			sticks.push_back(stick);
		}
		printf("%lld\n", calculateTrianglesCount());
		sticks.clear();
		scanf("%d", &sticksN);
	}
	return 0;
}