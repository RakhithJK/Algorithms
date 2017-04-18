#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

long calculate(vector<int> coinTypes)
{
	sort(coinTypes.begin(), coinTypes.end(), [](int lhs, int rhs) { return lhs > rhs; });
	return 0;
}

int main()
{
	int tests;
	cin >> tests;

	while(tests)
	{
		int coinsN;
		cin >> coinsN;
		vector<int> coinTypes(coinsN);
		for (int i = 0; i < coinsN; i++)
			cin >> coinTypes[i];

		cout << calculate(coinTypes) << '\n';
		tests--;
	}
	return 0;
}