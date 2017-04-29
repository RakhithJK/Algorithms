#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
using namespace std;
typedef long long int bigint;

vector<bigint>	trees;
bigint			treesN, desiredWoodCount;

void binarySearchHeights(bigint lo, bigint hi, bigint* optimalHeight, function<bool(bigint)> canCollectDesiredWoodCountWithHeight)
{
	if (lo > hi)
		return;
	bigint mid = (lo + hi) / 2;
	if (canCollectDesiredWoodCountWithHeight(mid)) {
		*optimalHeight = max(*optimalHeight, mid);
		return binarySearchHeights(mid + 1, hi, optimalHeight, canCollectDesiredWoodCountWithHeight);
	}
	return binarySearchHeights(lo, mid - 1, optimalHeight, canCollectDesiredWoodCountWithHeight);
}

bigint findMaxHeight()
{
	auto canCollectDesiredWoodCountWithHeight = [&](const bigint sawHeight)
	{
		bigint woodCount = accumulate(trees.begin(), trees.end(), bigint(0), [&](bigint accumulatedWood, const bigint tree)
		{
			return tree > sawHeight ? (accumulatedWood + tree - sawHeight) : accumulatedWood;
		});
		return woodCount >= desiredWoodCount;
	};
	bigint lo		= *min_element(trees.begin(), trees.end());
	bigint hi		= *max_element(trees.begin(), trees.end());
	bigint optimum	= lo;
	binarySearchHeights(lo, hi, &optimum, canCollectDesiredWoodCountWithHeight);
	return optimum;
}
int main()
{
	scanf("%lld %lld", &treesN, &desiredWoodCount);
	trees.resize(treesN);
	for (bigint i = 0; i < treesN; i++)
		scanf("%lld", &trees[i]);
	printf("%lld\n", findMaxHeight());
	return 0;
}