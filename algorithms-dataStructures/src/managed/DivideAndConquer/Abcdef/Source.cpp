#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

#define maxNumbersCount 101

vector<int> leftEquationParts;
vector<int> rightEquationParts;
vector<int> numbers;

long long numberOfSolutions(int setSize) {
	long long solutionsCount = 0;

	// a * b + c = d (e + f)
	for (int i = 0; i< setSize; i++)
	{
		for (int j = 0; j<setSize; j++)
		{
			for (int k = 0; k<setSize; k++)
			{
				leftEquationParts.push_back(numbers[i] * numbers[j] + numbers[k]);
			}
		}
	}
	for (int i = 0; i<setSize; i++)
	{
		for (int j = 0; j<setSize; j++)
		{
			for (int k = 0; k<setSize; k++)
			{
				if (numbers[i] == 0) continue;

				rightEquationParts.push_back(numbers[i] * (numbers[j] + numbers[k]));
			}
		}
	}

	sort(leftEquationParts.begin(), leftEquationParts.end());
	sort(rightEquationParts.begin(), rightEquationParts.end());

	for (auto leftEquationPart : leftEquationParts) {
		auto rightEqualInterval = equal_range(rightEquationParts.begin(), rightEquationParts.end(), leftEquationPart);
		if (rightEqualInterval.first != rightEqualInterval.second) {
			solutionsCount += abs(rightEqualInterval.second - rightEqualInterval.first);
		}
	}

	return solutionsCount;
}

int main() {

	int number, setSize;
	scanf("%d", &setSize);

	for (auto i = 0; i < setSize; i++)
	{
		scanf("%d", &number);
		numbers.push_back(number);
	}
	printf("%lld\n", numberOfSolutions(setSize));
	return 0;
}