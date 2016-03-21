#include "SelectionSort.h"
#include <vector>
using namespace std;

SelectionSort::SelectionSort()
{
}
SelectionSort::~SelectionSort()
{
}

void SelectionSort::Sort(vector<int> &arr)
{
	const int n = (arr.size() - 1);
	int i, j;
	int min;

	for (j = 0; j < n; j++) 
	{
		min = j;
		for (i = j + 1; i < n; i++) 
		{
			if (arr[i] < arr[min]) 
			{
				min = i;
			}
		}

		if (min != j) {
			int temp = arr[j];
			arr[j] = arr[min];
			arr[min] = temp;
		}

	}
}