#include<iostream>
#include<vector>
#include<queue>

using namespace std;
typedef long long bigint;

vector<int> arrayToBeSorted;

bigint merge(int lhs, int mid, int rhs)
{
	queue<int> left;
	queue<int> right;

	for (int i = lhs; i <= mid; i++)
		left.push(arrayToBeSorted[i]);
	for (int i = mid + 1; i <= rhs; i++)
		right.push(arrayToBeSorted[i]);

	int		k			= lhs;
	bigint	inversions	= 0;

	while (!left.empty() && !right.empty()) {
		if (left.front() < right.front()) {
			arrayToBeSorted[k] = left.front();
			left.pop();
		}
		else {
			arrayToBeSorted[k] = right.front();
			right.pop();
			inversions += left.size();
		}
		k++;
	}

	while (!left.empty()) { 
		arrayToBeSorted[k++] = left.front();
		left.pop();
	}
	while (!right.empty())
	{
		arrayToBeSorted[k++] = right.front();
		right.pop();
	}

	return inversions;
}
bigint merge_sort(int lhs, int rhs)
{
	int mid = lhs + (rhs - lhs) / 2;
	return (lhs < rhs) ?
		merge_sort(lhs, mid) + merge_sort(mid + 1, rhs) + merge(lhs, mid, rhs) :
		0;
}

int main()
{
	int tests, length;
	cin >> tests;
	while (tests)
	{
		cin >> length;
		arrayToBeSorted.clear();
		arrayToBeSorted.resize(length);

		for (int i = 0; i < length; i++)
			cin >> arrayToBeSorted[i];

		printf("%llu\n", merge_sort(0, arrayToBeSorted.size() - 1));
		tests--;
	}
	return 0;
}