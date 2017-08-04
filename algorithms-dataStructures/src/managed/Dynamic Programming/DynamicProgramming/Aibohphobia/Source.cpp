#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

#define maxLength 6500

int		maxCommonSubSequenceLengthOf[maxLength][maxLength];
string	source, sourceReversed;

int lcs(int leftSuffixEndIndex = 0, int rightSuffixEndIndex = 0)
{
	if (leftSuffixEndIndex == source.size() || rightSuffixEndIndex == sourceReversed.size())
		return maxCommonSubSequenceLengthOf[leftSuffixEndIndex][rightSuffixEndIndex] = 0;

	if (maxCommonSubSequenceLengthOf[leftSuffixEndIndex][rightSuffixEndIndex] != -1)
		return maxCommonSubSequenceLengthOf[leftSuffixEndIndex][rightSuffixEndIndex];

	if (source[leftSuffixEndIndex] == sourceReversed[rightSuffixEndIndex])
		return maxCommonSubSequenceLengthOf[leftSuffixEndIndex][rightSuffixEndIndex] = 1 + lcs(leftSuffixEndIndex + 1, rightSuffixEndIndex + 1);

	return maxCommonSubSequenceLengthOf[leftSuffixEndIndex][rightSuffixEndIndex] = max(
		lcs(leftSuffixEndIndex, rightSuffixEndIndex + 1),
		lcs(leftSuffixEndIndex + 1, rightSuffixEndIndex)
	);
}

int main()
{
	int tests;
	cin >> tests;
	while(tests--)
	{
		cin >> source;
		sourceReversed = source;
		reverse(sourceReversed.begin(), sourceReversed.end());
		memset(maxCommonSubSequenceLengthOf, -1, sizeof maxCommonSubSequenceLengthOf);
		cout << source.size() - lcs() << endl;
	}
	return 0;
}