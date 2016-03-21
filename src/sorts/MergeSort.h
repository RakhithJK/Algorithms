#pragma once
#include <vector>
using namespace std;

class MergeSort
{
public:
	MergeSort();
	~MergeSort();
	void SortArray(int arr[], int l, int r);
	void SortVector(vector<int> &arr, int lhs, int rhs);



private:
	void PerformArrayMerge(int arr[], int l, int m, int r);
	void PerformVectorMerge(vector<int> &arr, int lhs, int pivotIndex, int rhs);
};


