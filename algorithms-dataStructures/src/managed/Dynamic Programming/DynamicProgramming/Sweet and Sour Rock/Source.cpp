#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int		rockLength;
char	producedRock[205];
int		maxLengthOfInterval[205][205];

typedef pair<int, int> quality;
#define sweet	first
#define sour	second

quality getQuality(int startIx, int endIx) {
	auto sweet = 0, sour = 0;
	for (auto i = startIx; i <= endIx; i++)
	{
		if (producedRock[i] == '1')
			sweet++;
		if (producedRock[i] == '0')
			sour++;
	}
	return { sweet, sour };
}

int computeMaxSweetSplitForInterval(int intervalStart = 0, int intervalEnd = rockLength - 1)
{
	if (intervalStart == intervalEnd)
		return producedRock[intervalStart] == '1';
	if (maxLengthOfInterval[intervalStart][intervalEnd] != -1)
		return maxLengthOfInterval[intervalStart][intervalEnd];

	auto wholeTakenIntervalQuality = getQuality(intervalStart, intervalEnd);

	maxLengthOfInterval[intervalStart][intervalEnd] =
		wholeTakenIntervalQuality.sweet > wholeTakenIntervalQuality.sour ?
		intervalEnd - intervalStart + 1 :
		0;

	for (auto splitIx = intervalStart; splitIx < intervalEnd; splitIx++)
	{
		auto leftLength  = computeMaxSweetSplitForInterval(intervalStart, splitIx);
		auto rightLength = computeMaxSweetSplitForInterval(splitIx + 1, intervalEnd);

		maxLengthOfInterval[intervalStart][intervalEnd] = max(
			maxLengthOfInterval[intervalStart][intervalEnd],
			leftLength + rightLength
		);
	}

	return maxLengthOfInterval[intervalStart][intervalEnd];
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d", &rockLength);
		scanf("%s", &producedRock);
		memset(maxLengthOfInterval, -1, sizeof maxLengthOfInterval);
		printf("%d\n", computeMaxSweetSplitForInterval());
	}
	return 0;
}