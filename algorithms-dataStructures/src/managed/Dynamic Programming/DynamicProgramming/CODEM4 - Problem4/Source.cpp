#define _CRT_SECURE_NO_WARNINGS
#define maxNumbers 31

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int numbers[maxNumbers];
int numbersN;
int maxScoreOfInterval[maxNumbers][maxNumbers];
 
int maxScoreIfOnlyFirstIsSmart(int intervalStart, int intervalEnd)
{
	if (intervalStart > intervalEnd)
		return 0;

	if (maxScoreOfInterval[intervalStart][intervalEnd] != -1)
		return maxScoreOfInterval[intervalStart][intervalEnd];

	auto maxScoreIfTakeLeftmost = numbers[intervalStart] + max(
		maxScoreIfOnlyFirstIsSmart(intervalStart + 2, intervalEnd),
		maxScoreIfOnlyFirstIsSmart(intervalStart + 1, intervalEnd - 1)
	);

	auto maxScoreIfTakeRightmost = numbers[intervalEnd] + max(
		maxScoreIfOnlyFirstIsSmart(intervalStart, intervalEnd - 2),
		maxScoreIfOnlyFirstIsSmart(intervalStart + 1, intervalEnd - 1)
	);

	return maxScoreOfInterval[intervalStart][intervalEnd] = max(maxScoreIfTakeLeftmost, maxScoreIfTakeRightmost);
}

int maxScoreIfBothAreSmart(int intervalStart, int intervalEnd) 
{
	if (intervalStart > intervalEnd)
		return 0;

	if (maxScoreOfInterval[intervalStart][intervalEnd] != -1)
		return maxScoreOfInterval[intervalStart][intervalEnd];

	auto maxScoreIfTakeLeftmost = numbers[intervalStart] + min(
		maxScoreIfBothAreSmart(intervalStart + 2, intervalEnd),
		maxScoreIfBothAreSmart(intervalStart + 1, intervalEnd - 1)
	);

	auto maxScoreIfTakeRightmost = numbers[intervalEnd] + min(
		maxScoreIfBothAreSmart(intervalStart, intervalEnd - 2),
		maxScoreIfBothAreSmart(intervalStart + 1, intervalEnd - 1)
	);

	return maxScoreOfInterval[intervalStart][intervalEnd] = max(maxScoreIfTakeLeftmost, maxScoreIfTakeRightmost);
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%d", &numbersN);
		for(auto i = 0; i < numbersN; i++)
			scanf("%d", &numbers[i]);

		memset(maxScoreOfInterval, -1, sizeof maxScoreOfInterval);
		auto maxScoreIfOnlyFirstIsSmart = maxScoreIfOnlyFirstIsSmart(0, numbersN - 1);
		memset(maxScoreOfInterval, -1, sizeof maxScoreOfInterval);
		auto maxScoreBothAreSmart = maxScoreIfBothAreSmart(0, numbersN - 1);
		printf("%d %d\n", maxScoreIfOnlyFirstIsSmart, maxScoreBothAreSmart);
	}
	return 0;
}