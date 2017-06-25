#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

typedef unsigned long long bigint;
map<bigint, bigint> profitOfBytelandianCoin;

bigint computeMaxProfitOfBytelandianCoin(bigint amount)
{
	if (profitOfBytelandianCoin[amount] != 0)
		return profitOfBytelandianCoin[amount];

	if (amount == 0)
		return profitOfBytelandianCoin[0] = 0;
	if (amount == 1)
		return profitOfBytelandianCoin[1] = 1;

	return profitOfBytelandianCoin[amount] = max(
		amount,
		computeMaxProfitOfBytelandianCoin(amount / 2) + computeMaxProfitOfBytelandianCoin(amount / 3) + computeMaxProfitOfBytelandianCoin(amount / 4)
	);
}

int main()
{
	bigint amount;
	while(scanf("%lld", &amount) == 1)	
		printf("%lld\n", computeMaxProfitOfBytelandianCoin(amount));

	return 0;
}