#include "QuickSort.h"
#include <vector>
using namespace std;

QuickSort::QuickSort()
{
}
QuickSort::~QuickSort()
{
}


int QuickSort::Partition(vector<int> &arr, int lhs, int rhs)
{
	int pivotIndex = rhs;
	int i = lhs;
	for (int j = lhs; j < rhs; j++)
	{
		if (arr[j] < arr[pivotIndex])
		{
			i++;

			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i];
	arr[i] = arr[rhs];
	arr[rhs] = temp;
	return i;
}

void QuickSort::Sort(vector<int> &arr, int lhs, int rhs)
{
	if (lhs < rhs)
	{
		int partitionIndex = Partition(arr, lhs, rhs);
		Sort(arr, lhs, partitionIndex);
		Sort(arr, (partitionIndex + 1), rhs);
	}
}