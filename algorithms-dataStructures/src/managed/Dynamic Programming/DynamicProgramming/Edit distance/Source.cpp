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
int calculateMinimumEditDistance_bottomUp(string& lhs, string& rhs)
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

string source, target;
int calculateMinimumEditDistance_topDown(int sourcePrefixEnd, int targetPrefixEnd)
{
	if (!sourcePrefixEnd)
		return minimumEditDistance[sourcePrefixEnd][targetPrefixEnd] = targetPrefixEnd;
	if (!targetPrefixEnd)
		return minimumEditDistance[sourcePrefixEnd][targetPrefixEnd] = sourcePrefixEnd;

	if (minimumEditDistance[sourcePrefixEnd][targetPrefixEnd] != infinity)
		return minimumEditDistance[sourcePrefixEnd][targetPrefixEnd];

	auto delta = source[sourcePrefixEnd - 1] == target[targetPrefixEnd - 1] ? 0 : 1;

	return minimumEditDistance[sourcePrefixEnd][targetPrefixEnd] =
		min(
			calculateMinimumEditDistance_topDown(sourcePrefixEnd, targetPrefixEnd - 1) + 1,
			calculateMinimumEditDistance_topDown(sourcePrefixEnd - 1, targetPrefixEnd) + 1,
			calculateMinimumEditDistance_topDown(sourcePrefixEnd - 1, targetPrefixEnd - 1) + delta
		);
}

int calculateMinimumEditDistance_topDown_withStrings(string sourcePrefix, string targetPrefix)
{
	if (!sourcePrefix.length())
		return minimumEditDistance[sourcePrefix.length()][targetPrefix.length()] = targetPrefix.length();
	if (!targetPrefix.length())
		return minimumEditDistance[sourcePrefix.length()][targetPrefix.length()] = sourcePrefix.length();
	if (minimumEditDistance[sourcePrefix.length()][targetPrefix.length()] != infinity)
		return minimumEditDistance[sourcePrefix.length()][targetPrefix.length()];

	auto prefixOfSourcePrefix = sourcePrefix.substr(0, sourcePrefix.length() - 1);
	auto prefixOfTargetPrefix = targetPrefix.substr(0, targetPrefix.length() - 1);
	auto lastLetterChangeCost = *(sourcePrefix.end() - 1) == *(targetPrefix.end() - 1) ? 0 : 1;

	printf("source=%s target=%s \n", sourcePrefix.c_str(), targetPrefix.c_str());

	return minimumEditDistance[sourcePrefix.length()][targetPrefix.length()] =
		min(
			calculateMinimumEditDistance_topDown_withStrings(sourcePrefix, prefixOfTargetPrefix) + 1,
			calculateMinimumEditDistance_topDown_withStrings(prefixOfSourcePrefix, targetPrefix) + 1,
			calculateMinimumEditDistance_topDown_withStrings(prefixOfSourcePrefix, prefixOfTargetPrefix) + lastLetterChangeCost
		);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int tests;
	cin >> tests;
	while (tests--)
	{
		memset(minimumEditDistance, 0, sizeof minimumEditDistance);
		cin >> source >> target;

		for (auto i = 0; i <= source.size(); i++)
			for (auto j = 0; j <= target.size(); j++)
				minimumEditDistance[i][j] = infinity;

		cout << calculateMinimumEditDistance_topDown_withStrings(source, target) << endl;
	}
	return 0;
}