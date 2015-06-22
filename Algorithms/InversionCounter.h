#pragma once
#include <vector>
using namespace std;

class InversionCounter
{


public:
	InversionCounter();
	~InversionCounter();
	int CalculateInversions(vector<int> &arr, int lhs, int rhs);
private:
	int PerformMergeAndCount(vector<int> &arr, int lhs, int pivotIndex, int rhs);
};

