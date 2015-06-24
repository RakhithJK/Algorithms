#include "BubbleSort.h"
#include <vector>
using namespace std;


BubbleSort::BubbleSort()
{
}
BubbleSort::~BubbleSort()
{
}

void BubbleSort::Sort(vector<int> &arr)
{
	int n = arr.size() - 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i] < arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void BubbleSort::Sort(int * arr)
{
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i] < arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

