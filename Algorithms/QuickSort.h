#pragma once
#include <vector>
using namespace std;
class QuickSort
{
public:
	QuickSort();
	~QuickSort();
	void Sort(vector<int> &arr, int lhs, int rhs);
private:
	int Partition(vector<int> &arr, int lhs, int rhs);
};

