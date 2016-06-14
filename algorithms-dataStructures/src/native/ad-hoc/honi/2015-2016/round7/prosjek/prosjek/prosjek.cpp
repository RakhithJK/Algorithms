#include<iostream>	
#include<vector>
using namespace std;

int numberOfElements;
int minimalSubarraySize;
int maxAverage;

int calculateMaxSubarrayIndex(const vector<int>& numbers)
{
	int sum = 0, maxSum, maxSumIndex;
	for (int i = 0; i < numberOfElements; i++)
	{
		sum += numbers[i];
	}
	maxSum = sum;
	maxSum = 0;

	for (int i = minimalSubarraySize; i < numberOfElements - 1; i++)
	{
		sum = sum - numbers[i - minimalSubarraySize] + numbers[i];
		if (sum > maxSum)
		{
			maxSum = sum;
			maxSumIndex = i - minimalSubarraySize;
		}
	}

	return maxSumIndex + 2;
}

double calculateAverageForArray(const vector<int>& numbers)
{
	int sum = 0;
	int index = calculateMaxSubarrayIndex(numbers);
	for (int i = 0; i < minimalSubarraySize; i++) {
		sum += numbers[index++];
	}
	return double(sum) / minimalSubarraySize;
}

int main()
{
	vector<int> numbers;
	cin >> numberOfElements >> minimalSubarraySize;
	for (int i = 0; i < numberOfElements; i++)
	{
		int temp;
		cin >> temp;
		numbers.push_back(temp);
	}
	cout << endl << calculateAverageForArray(numbers) << endl;
}