#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#include <climits>

using namespace std;

typedef unsigned long long bigint;

#define maxStringLength 2500
#define infinity INT_MAX - 1
int minimumEditDistance[maxStringLength][maxStringLength];


inline int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

// bottom-up
int calculateMinimumEditDistance(string& lhs, string& rhs)
{
	auto lhsLength = lhs.size();
	auto rhsLength = rhs.size();

	for (auto i = 0; i <= rhsLength; i++)
		for (auto j = 0; j <= lhsLength; j++)
			minimumEditDistance[i][j] = infinity;

	for (auto i = 0; i <= rhsLength; i++)
	{
		for (auto j = 0; j <= lhsLength; j++)
		{
			if (i == 0)
				minimumEditDistance[i][j] = j; 
			else if (j == 0)
				minimumEditDistance[i][j] = i; 

			else if (lhs[i - 1] == rhs[j - 1])
				minimumEditDistance[i][j] = minimumEditDistance[i - 1][j - 1];
			else
			{
				minimumEditDistance[i][j] = 1 + min(minimumEditDistance[i][j - 1],
					minimumEditDistance[i - 1][j],
					minimumEditDistance[i - 1][j - 1]);
			}
		}
	}

	return minimumEditDistance[lhsLength][rhsLength];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string lhs, rhs;
	int tests;
	cin >> tests;
	while (tests--)
	{
		memset(minimumEditDistance, 0, sizeof minimumEditDistance);
		cin >> lhs >> rhs;
		cout << calculateMinimumEditDistance(lhs, rhs) << endl;
	}
	return 0;
}