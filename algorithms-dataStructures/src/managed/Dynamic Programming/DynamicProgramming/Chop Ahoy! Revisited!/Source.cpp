#include <iostream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

#define maxNumberDigits 30

int		number[maxNumberDigits];
int		maxDecompositionsForPosition[maxNumberDigits][300];
string	numberAsString;

int computeNumberOfDecompositions(int decompositionStart = 0, int previousSum = 0)
{
	if (decompositionStart == numberAsString.size())
		return 1;

	if (maxDecompositionsForPosition[decompositionStart][previousSum] != 0)
		return maxDecompositionsForPosition[decompositionStart][previousSum];

	auto decompositions = 0;
	auto forwardSum		= 0;

	for (auto i = decompositionStart; i < numberAsString.size(); i++) {
		forwardSum += number[i];

		if (forwardSum >= previousSum) 
			decompositions += computeNumberOfDecompositions(i + 1, forwardSum);
	}

	return maxDecompositionsForPosition[decompositionStart][previousSum] = decompositions;
}

int main()
{
	auto currentTest = 0;
	while(cin >> numberAsString && numberAsString != "bye")
	{
		currentTest++;
		memset(maxDecompositionsForPosition, 0, sizeof maxDecompositionsForPosition);

		for (auto i = 0; i < numberAsString.size(); i++)
			number[i] = numberAsString[i] - '0';

		printf("%d. %d\n", currentTest, computeNumberOfDecompositions());
	}
	return 0;
}