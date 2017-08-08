#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define maxLength 5005
typedef long long bigint;

bigint dp[maxLength];
string sequence;

int asNumber(char character) { return character - '0'; }

bigint computeNumberOfDecodings(int currentIndex = sequence.size() - 1) {
	if (currentIndex == 0)
		return dp[currentIndex] = 1;

	if (currentIndex == 1 && sequence[currentIndex])
	{
		auto numberAsGroup = asNumber(sequence[0]) * 10 + asNumber(sequence[1]);
		if (numberAsGroup > 9 && numberAsGroup <= 26 && numberAsGroup % 10 != 0)
			 return dp[currentIndex] = 2;

		return dp[currentIndex] = 1;
	}

	if (dp[currentIndex] != -1)
		return dp[currentIndex];

	auto numberAsSelf  = asNumber(sequence[currentIndex]);
	auto numberAsGroup = asNumber(sequence[currentIndex - 1]) * 10 + numberAsSelf;

	bigint countOfAsSelf  = 0;
	bigint countOfAsGroup = 0;

	if (numberAsSelf)
		countOfAsSelf = computeNumberOfDecodings(currentIndex - 1);

	if (numberAsGroup > 9 && numberAsGroup <= 26)
		countOfAsGroup = (currentIndex - 2 < 0) ? 
			0 : 
			computeNumberOfDecodings(currentIndex - 2);
	
	return dp[currentIndex] = countOfAsSelf + countOfAsGroup;
}

int main()
{
	cin >> sequence;
	while(sequence[0] != '0')
	{
		memset(dp, -1, sizeof dp);
		cout << computeNumberOfDecodings() << endl;
		cin >> sequence;
	}
	return 0;
}