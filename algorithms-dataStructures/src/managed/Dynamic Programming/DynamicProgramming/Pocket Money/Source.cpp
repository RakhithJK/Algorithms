#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int		expressionLength;
char	expression[105];
int		maximumMoneyOfInterval[105][105];
int		minimumMoneyOfInterval[105][105];

typedef pair<int, int> result;
#define maxAmount	first
#define minAmount	second
#define infinity	INT_MAX - 1

inline int asInt(char character) { return character - '0'; }

result calculateBestAmountForInterval(int intervalStart = 0, int intervalEnd = strlen(expression) - 1)
{
	if (intervalStart == intervalEnd)
		return { asInt(expression[intervalStart]), asInt(expression[intervalStart]) };

	if(maximumMoneyOfInterval[intervalStart][intervalEnd] != -1)
		return {
			maximumMoneyOfInterval[intervalStart][intervalEnd],
			minimumMoneyOfInterval[intervalStart][intervalEnd]
		};

	maximumMoneyOfInterval[intervalStart][intervalEnd] = 0;
	minimumMoneyOfInterval[intervalStart][intervalEnd] = infinity;

	for(auto splitIndex = intervalStart; splitIndex < intervalEnd; splitIndex++)
	{
		if(expression[splitIndex] != '+' && expression[splitIndex] != '*')
			continue;

		auto leftSubexpression  = calculateBestAmountForInterval(intervalStart, splitIndex - 1);
		auto rightSubexpression = calculateBestAmountForInterval(splitIndex + 1, intervalEnd);

		if(expression[splitIndex] == '+')
		{
			maximumMoneyOfInterval[intervalStart][intervalEnd] = max(
				maximumMoneyOfInterval[intervalStart][intervalEnd],
				leftSubexpression.maxAmount + rightSubexpression.maxAmount
			);

			minimumMoneyOfInterval[intervalStart][intervalEnd] = min(
				minimumMoneyOfInterval[intervalStart][intervalEnd],
				leftSubexpression.minAmount + rightSubexpression.minAmount
			);
		}
		if (expression[splitIndex] == '*')
		{
			maximumMoneyOfInterval[intervalStart][intervalEnd] = max(
				maximumMoneyOfInterval[intervalStart][intervalEnd],
				leftSubexpression.maxAmount * rightSubexpression.maxAmount
			);

			minimumMoneyOfInterval[intervalStart][intervalEnd] = min(
				minimumMoneyOfInterval[intervalStart][intervalEnd],
				leftSubexpression.minAmount * rightSubexpression.minAmount
			);
		}
	}

	return { 
		maximumMoneyOfInterval[intervalStart][intervalEnd], 
		minimumMoneyOfInterval[intervalStart][intervalEnd] 
	};
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		scanf("%s", &expression);
		memset(maximumMoneyOfInterval, -1, sizeof maximumMoneyOfInterval);
		memset(minimumMoneyOfInterval, -1, sizeof minimumMoneyOfInterval);
		auto result = calculateBestAmountForInterval();
		printf("%d %d\n", result.maxAmount, result.minAmount);
	}
	return 0;
}