#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxTreatsN 2001

using namespace std;

int treatValue			[maxTreatsN];
int maxProfitForInterval[maxTreatsN][maxTreatsN];
int treatsN;

int computeMaxProfitForInterval(int intervalStart, int intervalEnd, int elapsedTime)
{
	if (elapsedTime > treatsN)
		return 0;
	if (intervalEnd == 0)
		return elapsedTime * treatValue[0];
	if (intervalStart == treatsN - 1)
		return elapsedTime * treatValue[treatsN - 1];

	if (maxProfitForInterval[intervalStart][intervalEnd] != -1)
		return maxProfitForInterval[intervalStart][intervalEnd];

	return maxProfitForInterval[intervalStart][intervalEnd] = max(
		computeMaxProfitForInterval(intervalStart, intervalEnd - 1, elapsedTime + 1) + elapsedTime * treatValue[intervalEnd],
		computeMaxProfitForInterval(intervalStart + 1, intervalEnd, elapsedTime + 1) + elapsedTime * treatValue[intervalStart]
	);
}

int main()
{
	scanf("%d", &treatsN);
	memset(maxProfitForInterval, -1, sizeof maxProfitForInterval);

	for (auto i = 0; i < treatsN; i++)
		scanf("%d", &treatValue[i]);

	printf("%d",computeMaxProfitForInterval(0, treatsN - 1, 1));
	return 0;
}