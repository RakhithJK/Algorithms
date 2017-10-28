#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

using namespace std;

#define maxCoinValues	6
#define maxAmount		100001

int amountToExchange, numberOfCoins = 0;
int coinValues[maxCoinValues];
int coinValueUpto[maxCoinValues];
int canExchangeAmount[maxAmount];

bool canExchange(const int remainingAmount)
{
	if (remainingAmount == 0)
		return canExchangeAmount[remainingAmount] = true;

	if (canExchangeAmount[remainingAmount] != -1)
		return canExchangeAmount[remainingAmount];
	
	for(auto coinsTake = numberOfCoins - 1; coinsTake >= 0; coinsTake--)
	{
		if (
			remainingAmount - coinValueUpto[coinsTake] >= 0 && 
			canExchange(remainingAmount - coinValueUpto[coinsTake])
		)
			return canExchangeAmount[remainingAmount] = true;
	}

	return canExchangeAmount[remainingAmount] = false;
}

int main()
{
	while(scanf("%d %d", &amountToExchange, &numberOfCoins) != EOF)
	{
		for(auto i = 0; i < numberOfCoins; i++)
			scanf("%d", &coinValues[i]);

		for(auto i = 0; i < numberOfCoins; i++)
		{
			coinValueUpto[i] = 0;
			for(auto j = 0; j<=i; j++)
				coinValueUpto[i] += coinValues[j];
		}

		memset(canExchangeAmount, -1, sizeof canExchangeAmount);
		if (canExchange(amountToExchange))
			printf("YES\n");
		else
			printf("NO\n");
	}
	
	return 0;
}