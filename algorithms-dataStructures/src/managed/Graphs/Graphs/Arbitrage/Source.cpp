#define _CRT_SECURE_NO_WARNINGS

#include<unordered_map>
#include<iostream>
#include<string>
#include<algorithm>

#define currenciesMaxN 50

using namespace std;
typedef long double precise_double;

int							currenciesN, relationsN;
precise_double				currenciesGraph[currenciesMaxN][currenciesMaxN];
unordered_map<string, int>	currencies;

void floyd_warshall()
{
	for (int k = 1; k <= currenciesN; k++)
		for (int i = 1; i <= currenciesN; i++)
			for (int j = 1; j <= currenciesN; j++)
				currenciesGraph[i][j] = max(currenciesGraph[i][j], currenciesGraph[i][k] * currenciesGraph[k][j]);

}

bool isArbitragePossible()
{
	floyd_warshall();

	for (int i = 1; i <= currenciesN; i++)
		if (currenciesGraph[i][i] > 1.0)
			return true;

	return false;
}

int main()
{
	int test = 0;

	cin >> currenciesN;
	while (currenciesN)
	{
		test++;
		currencies.clear();
		for (int i = 1; i <= currenciesN; i++)
			for (int j = 1; j <= currenciesN; j++)
				currenciesGraph[i][j] = i == j ? 1.0 : 0.0;

		for (int i = 1; i <= currenciesN; i++)
		{
			string currency;
			cin >> currency;
			currencies[currency] = i;
		}

		cin >> relationsN;
		while (relationsN)
		{
			string lhs, rhs;
			precise_double ratio;
			cin >> lhs >> ratio >> rhs;
			currenciesGraph[currencies[lhs]][currencies[rhs]] = ratio;
			relationsN--;
		}
		string isPossible = isArbitragePossible() ? "Yes" : "No";
		printf("Case %d: %s\n", test, isPossible.c_str());
		cin >> currenciesN;
	}
	return 0;
}