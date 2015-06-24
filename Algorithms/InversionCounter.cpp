#include "InversionCounter.h"
#include <vector>

using namespace std;


InversionCounter::InversionCounter()
{
}
InversionCounter::~InversionCounter()
{
}


int InversionCounter::PerformMergeAndCount(vector<int> &arr, int lhs, int pivotIndex, int rhs)
{
	int i, j, key, count;

	const int firstPart = pivotIndex - lhs + 1;
	const int rightPart = rhs - pivotIndex;

	vector<int> leftSide;
	vector<int> rightSide;

	for (i = 0; i < firstPart; i++)
	{
		leftSide.push_back(arr.at(lhs + i));
	}
	for (j = 0; j < rightPart; j++)
	{
		rightSide.push_back(arr.at((pivotIndex + 1) + j));
	}


	i = 0;
	j = 0;
	key = lhs;
	count = 0;

	while (i < firstPart && j < rightPart)
	{
		if (leftSide[i] <= rightSide[j])
		{
			arr[key] = leftSide[i];
			i++;
		}
		else
		{
			arr[key] = rightSide[j];
			count += leftSide.size() - i; 
			j++;
		}
		key++;
	}
	return count;

}
int InversionCounter::CalculateInversions(vector<int> &arr, int lhs, int rhs)
{
	if (lhs < rhs)
	{
		const int pivotIndex = lhs + (rhs - lhs) / 2;
		return CalculateInversions(arr, lhs, pivotIndex) + CalculateInversions(arr, (pivotIndex + 1), rhs) + PerformMergeAndCount(arr, lhs, pivotIndex, rhs);
	}
}
