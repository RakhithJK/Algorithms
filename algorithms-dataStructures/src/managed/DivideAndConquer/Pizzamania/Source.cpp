#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<vector>
#include<cstdio>
#include<set>
#include<map>

using namespace std;

int calculateNumberOfPairsWhoCanBuyPizza(vector<int>& friendsMoney, int pizzaCost)
{
	set<pair<int, int>> pairsWhoCanBuy;
	auto didFindPairAlready = [&](pair<int, int> pair)
	{
		return  pairsWhoCanBuy.find(pair) != pairsWhoCanBuy.end() ||
				pairsWhoCanBuy.find({ pair.second, pair.first }) != pairsWhoCanBuy.end();
	};
	sort(friendsMoney.begin(), friendsMoney.end());
	for (auto money : friendsMoney)
	{
		if (
			pizzaCost - money != money &&
			!didFindPairAlready({ money, pizzaCost - money }) &&
			binary_search(friendsMoney.begin(), friendsMoney.end(), pizzaCost - money)
		)
		{
			pairsWhoCanBuy.insert({ money , pizzaCost - money });
		}
	}
	return pairsWhoCanBuy.size();
}

int main()
{
	int tests, friendsN, money, pizzaCost;
	scanf("%d", &tests);
	while (tests--)
	{
		vector<int> friendsMoney;
		scanf("%d %d", &friendsN, &pizzaCost);
		while (friendsN--)
		{
			scanf("%d", &money);
			friendsMoney.push_back(money);
		}
		printf("%d\n", calculateNumberOfPairsWhoCanBuyPizza(friendsMoney, pizzaCost));
	}
	return 0;
}