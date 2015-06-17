#include "MergeSort.h"
#include <vector>
using namespace std;

MergeSort::MergeSort()
{
}
MergeSort::~MergeSort()
{
}


//ALGORITHM IMPLEMENTATION

void MergeSort::PerformArrayMerge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[100], R[100];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void MergeSort::SortArray(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2; 
		SortArray(arr, l, m);
		SortArray(arr, m + 1, r);
		PerformArrayMerge(arr, l, m, r);
	}
}

void MergeSort::PerformVectorMerge(vector<int> &arr, int lhs, int pivotIndex, int rhs)
{
	int i, j, key;

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
			j++;
		}
		key++;
	}


	while (i < firstPart)
	{
		arr[key] = leftSide[i];
		i++;
		key++;
	}

	while (j < rightPart)
	{
		arr[key] = rightSide[j];
		j++;
		key++;
	}
}
void MergeSort::SortVector(vector<int> &arr, int lhs, int rhs)
{
	if (lhs < rhs)
	{
		const int pivotIndex = lhs + (rhs - lhs) / 2;
		SortVector(arr, lhs, pivotIndex);
		SortVector(arr, (pivotIndex + 1), rhs);
		PerformVectorMerge(arr, lhs, pivotIndex, rhs);
	}
}

