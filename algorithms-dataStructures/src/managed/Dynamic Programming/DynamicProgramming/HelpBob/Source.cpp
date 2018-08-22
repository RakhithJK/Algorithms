#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline bool isPizzaBought(int mask, int pizzaIx) { return mask & (1 << pizzaIx); }
inline int markPizzaAsBought(int mask, int pizzaIx) { return mask | (1 << pizzaIx); }

#define maxPizzasNumber 16

int		pizzasNumber, allBoughtPizzasState;
double	discountFromTo[maxPizzasNumber][maxPizzasNumber];
int		priceOfPizza[maxPizzasNumber];
int		areaOfPizza[maxPizzasNumber];

double minimalPriceOfState[1 << maxPizzasNumber];
int accumulatedAreaOfState[1 << maxPizzasNumber];

inline int areaOfState(int stateMask) {
	double area = 0;
	for (auto maybeBoughtPizza = 0; maybeBoughtPizza < pizzasNumber; maybeBoughtPizza++)
	{
		if (isPizzaBought(stateMask, maybeBoughtPizza))
			area += areaOfPizza[maybeBoughtPizza];
	}
	return area;
}

inline double discountFactorForPizza(int pizzasStateMask, int targetPizza, int discountSourcePizza)
{
	double discountFactor = isPizzaBought(pizzasStateMask, discountSourcePizza) ? 
		(100 - discountFromTo[discountSourcePizza][targetPizza]) / 100.0 :
		1.0;

	return discountFactor;
}

double getOptimalRatio()
{
	double minimalRatio = 1e9;

	for (int currentBoughtPizzasState = 0; currentBoughtPizzasState < allBoughtPizzasState; currentBoughtPizzasState++)
	{
		int currentStateArea = areaOfState(currentBoughtPizzasState);

		if (currentBoughtPizzasState)
			minimalRatio = min(
				minimalRatio,
				minimalPriceOfState[currentBoughtPizzasState] / currentStateArea
			);

		for (int nextNotBoughtPizza = 0; nextNotBoughtPizza < pizzasNumber; nextNotBoughtPizza++)
		{
			if (isPizzaBought(currentBoughtPizzasState, nextNotBoughtPizza))
				continue;

			double nextNotBoughtPizzaPrice = priceOfPizza[nextNotBoughtPizza];

			for (int discountSourcePizza = 0; discountSourcePizza < pizzasNumber; discountSourcePizza++)
				nextNotBoughtPizzaPrice *= discountFactorForPizza(currentBoughtPizzasState, nextNotBoughtPizza, discountSourcePizza);

			auto nextBoughtPizzaState = markPizzaAsBought(currentBoughtPizzasState, nextNotBoughtPizza);

			minimalPriceOfState[nextBoughtPizzaState] = min(
				minimalPriceOfState[nextBoughtPizzaState],
				minimalPriceOfState[currentBoughtPizzasState] + nextNotBoughtPizzaPrice
			);
		}
	}

	return minimalRatio;
}

int main() {
	while (scanf("%d", &pizzasNumber) && pizzasNumber) {
		int discountsN, targetPizza, discount;

		memset(discountFromTo, 1, sizeof(discountFromTo));

		for(auto i = 0; i < pizzasNumber; i++) {
			scanf("%d %d %d", &priceOfPizza[i], &areaOfPizza[i], &discountsN);
			while (discountsN--) {
				scanf("%d %d", &targetPizza, &discount);
				targetPizza--;
				discountFromTo[i][targetPizza] = discount;
			}
		}

		allBoughtPizzasState = (1 << pizzasNumber);

		for (int i = 1; i < allBoughtPizzasState; i++)
			minimalPriceOfState[i] = 1e9;

		double minimalRatio = getOptimalRatio();

		printf("%.4lf\n", minimalRatio);
	}

	return 0;
}