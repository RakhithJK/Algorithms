#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> party;
typedef pair<int, int> result;

result undefinedResult = { 0, 0 };

#define entraceFee		first
#define fun				second

#define infinity		INT_MAX - 1
#define money			501
#define partiesCount	100

int				 availableMoney, partiesN;
vector<party>	 parties;
result			 maxFunUptoPartyWithMoney[money][partiesCount];

result computeOptimalScheduleUptoParty(int currentParty = partiesN - 1, int availableMoney = ::availableMoney)
{
	if (currentParty == -1 || availableMoney < 0)
		return { 0, 0 };

	if (maxFunUptoPartyWithMoney[availableMoney][currentParty] != undefinedResult)
		return maxFunUptoPartyWithMoney[availableMoney][currentParty];

	result scheduleExcludingCurrent = computeOptimalScheduleUptoParty(currentParty - 1, availableMoney);
	result scheduleIncludingCurrent = { infinity, -1 };
	result optimum = scheduleExcludingCurrent;

	if (parties[currentParty].entraceFee <= availableMoney)
	{
		scheduleIncludingCurrent = computeOptimalScheduleUptoParty(currentParty - 1, availableMoney - parties[currentParty].entraceFee);
		scheduleIncludingCurrent.fun += parties[currentParty].fun;
		scheduleIncludingCurrent.entraceFee += parties[currentParty].entraceFee;
	}

	if (scheduleIncludingCurrent.fun > optimum.fun)
		optimum = scheduleIncludingCurrent;
	if (scheduleIncludingCurrent.fun == optimum.fun && scheduleIncludingCurrent.entraceFee < optimum.entraceFee)
		optimum = scheduleIncludingCurrent;
		
	return maxFunUptoPartyWithMoney[availableMoney][currentParty] = optimum;
}

int main()
{
	while (scanf("%d %d", &availableMoney, &partiesN) && availableMoney && partiesN)
	{
		parties = vector<party>(partiesN);
		memset(maxFunUptoPartyWithMoney, false, sizeof maxFunUptoPartyWithMoney);

		for (auto i = 0; i < partiesN; i++)
			scanf("%d %d", &parties[i].entraceFee, &parties[i].fun);

		auto solution = computeOptimalScheduleUptoParty();
		printf("%d %d\n", solution.entraceFee, solution.fun);
	}
	return 0;
}