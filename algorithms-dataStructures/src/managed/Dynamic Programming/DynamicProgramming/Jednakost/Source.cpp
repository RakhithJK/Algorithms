#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define infinity INT_MAX / 2
#define maxDimension 5001
string			equation;
vector<char>	leftPart;
int				targetSum;
int				minNumberOfAdditions[maxDimension][maxDimension];

inline int asInt(char character) { return character - '0'; }

int computeMinNumberOfAdditions(int currentIndex, int targetSum)
{
	if (targetSum < 0 || targetSum > 5000)
		return infinity;
	if (currentIndex == leftPart.size() && targetSum == 0)
		return 0;
	if (currentIndex == leftPart.size() && targetSum != 0)
		return infinity;

	if (minNumberOfAdditions[currentIndex][targetSum] != -1)
		return minNumberOfAdditions[currentIndex][targetSum];

	auto currentSum = asInt(leftPart[currentIndex]);

	if (currentSum > targetSum)
		return minNumberOfAdditions[currentIndex][targetSum] = infinity;
	
	auto optimum = 1 + computeMinNumberOfAdditions(currentIndex + 1, targetSum - currentSum);

	for(auto groupIndex = currentIndex + 1; currentSum <= targetSum, groupIndex < leftPart.size(); groupIndex++)
	{
		currentSum = currentSum * 10 + asInt(leftPart[groupIndex]);
		optimum = min(
			optimum,
			1 + computeMinNumberOfAdditions(groupIndex + 1, targetSum - currentSum)
		);
	}
	return minNumberOfAdditions[currentIndex][targetSum] = optimum;
}

inline void splitEquationPartsAndClearAdjacentZeros()
{
	auto equalsIndex = 0;
	auto adjacentZerosCount = 0;

	for (auto i = 0; i < equation.size(); i++)
	{
		if (equation[i] == '=')
		{
			equalsIndex = i;
			break;
		}
		if (equation[i] != '0')
		{
			leftPart.push_back(equation[i]);
			adjacentZerosCount = 0;
		}
		else if (equation[i] == '0' && adjacentZerosCount <= 3)
		{
			leftPart.push_back(equation[i]);
			++adjacentZerosCount;
		}
	}

	targetSum = stoi(equation.substr(equalsIndex + 1));
}

int main()
{
	memset(minNumberOfAdditions, -1, sizeof minNumberOfAdditions);
	cin >> equation;

	splitEquationPartsAndClearAdjacentZeros();

	auto minNumberOfAdditions = computeMinNumberOfAdditions(0, targetSum) - 1;
	printf("%d", minNumberOfAdditions);
	return 0;
}