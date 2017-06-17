#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>

using namespace std;
typedef unsigned long long bigint;

int		numbersToPermute[] = { 0,1,2,3,4,5,6,7,8,9 };
int		multipliers[10];
int		permutation[10];
bool	isAvailable[11];
bigint	maxSum;
bigint  currentSum;

bool canPermuteDeeper(int placeIndex) {
	if (placeIndex == 10) 
		return true;
	
	for (auto availableNumber : numbersToPermute) {
		if (!isAvailable[availableNumber])
			continue;
		if (currentSum + availableNumber * multipliers[placeIndex] > maxSum)
			continue;

		permutation[placeIndex] = availableNumber;
		currentSum += availableNumber * multipliers[placeIndex];
		isAvailable[availableNumber] = false;
		if (canPermuteDeeper(placeIndex + 1))
			return true;

		isAvailable[availableNumber] = true;
		currentSum -= availableNumber * multipliers[placeIndex];
	}
	return false;
}

bool canConstructPermutation() { 
	memset(isAvailable, true, sizeof isAvailable);
	currentSum = 0; 
	return canPermuteDeeper(0); 
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		for (auto i = 0; i < 10; i++)
			scanf("%d", &multipliers[i]);

		scanf("%lld", &maxSum);
		if (canConstructPermutation())
		{
			for (auto i = 0; i < 10; i++)
				printf("%d ", permutation[i]);
			printf("\n");
		}
		else
			printf("-1\n");
	}
	return 0;
}