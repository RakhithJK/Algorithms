#define _CRT_SECURE_NO_WARNINGS
#define maxCardsN 1001

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int cardsN;
int cards[maxCardsN];
int maxCardsSumInInterval[maxCardsN][maxCardsN];
 
int compute_max_cards_sum_in_interval(int intervalStartIx = 0, int intervalEndIx = cardsN - 1)
{
	if (intervalStartIx >= intervalEndIx)
		return 0;	
	if (intervalEndIx == 0)
		return cards[0];
	if (intervalStartIx == cardsN - 1)
		return cards[cardsN - 1];

	if (maxCardsSumInInterval[intervalStartIx][intervalEndIx] != -1)
		return maxCardsSumInInterval[intervalStartIx][intervalEndIx];

	auto optimum = -1;

	if(cards[intervalStartIx + 1] >= cards[intervalEndIx])
		optimum = max(optimum, cards[intervalStartIx] + compute_max_cards_sum_in_interval(intervalStartIx + 2, intervalEndIx));
	else
		optimum = max(optimum, cards[intervalStartIx] + compute_max_cards_sum_in_interval(intervalStartIx + 1, intervalEndIx - 1));

	if(cards[intervalStartIx] >= cards[intervalEndIx - 1])
		optimum = max(optimum, cards[intervalEndIx] + compute_max_cards_sum_in_interval(intervalStartIx + 1, intervalEndIx - 1));
	else
		optimum = max(optimum, cards[intervalEndIx] + compute_max_cards_sum_in_interval(intervalStartIx, intervalEndIx - 2));

	return maxCardsSumInInterval[intervalStartIx][intervalEndIx] = optimum;
}


int main()
{
	auto currentTest = 0;
	while(scanf("%d", &cardsN) && cardsN != 0) 
	{
		auto maxPoints = 0;
		for (auto i = 0; i < cardsN; i++)
		{
			scanf("%d", &cards[i]);
			maxPoints += cards[i];
		}
		memset(maxCardsSumInInterval, -1, sizeof maxCardsSumInInterval);
		auto dp		= compute_max_cards_sum_in_interval();
		auto greedy = maxPoints - dp;
		auto loss	= abs(dp - greedy);

		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++currentTest, loss);
	}
	return 0;
} 