#define _CRT_SECURE_NO_WARNINGS
#define maxCoins 1000001
typedef unsigned long long bigint;

#include <cstring>
#include <string>

using namespace std;
int		firstChoice, secondChoice, games, amount;
bool	isPlayerAWinning[maxCoins];

int main()
{
	scanf("%d %d %d", &firstChoice, &secondChoice, &games);
	memset(isPlayerAWinning, false, sizeof isPlayerAWinning);

	isPlayerAWinning[0] = false;
	isPlayerAWinning[1] = true;

	for (auto coinsAmount = 2; coinsAmount <= maxCoins; coinsAmount++)
	{
		if (coinsAmount - 1 >= 0 && !isPlayerAWinning[coinsAmount - 1])
			isPlayerAWinning[coinsAmount] = true;
	    if (coinsAmount - firstChoice >= 0 && !isPlayerAWinning[coinsAmount - firstChoice])
			isPlayerAWinning[coinsAmount] = true;
	    if (coinsAmount - secondChoice >= 0 && !isPlayerAWinning[coinsAmount - secondChoice])
			isPlayerAWinning[coinsAmount] = true;
	}

	while(games--)
	{
		scanf("%d", &amount);
		string winner = isPlayerAWinning[amount] ? "A" : "B";
		printf("%s", winner.c_str());
	}
	return 0;
}