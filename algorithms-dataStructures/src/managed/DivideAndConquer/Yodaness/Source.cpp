#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<unordered_map>

using namespace std;

unordered_map<string, int> givenOrder;
vector<int> positionsToBeSorted;

long calculateSplitYodaness(int lhs, int mid, int rhs)
{
	queue<int> left;
	queue<int> right;
	queue<int> sorted;

	long inversions = 0;

	for (int i = lhs; i <= mid; i++)
		left.push(positionsToBeSorted[i]);
	for (int i = mid + 1; i <= rhs; i++)
		right.push(positionsToBeSorted[i]);

	int k = lhs;

	while(!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			positionsToBeSorted[k++] = left.front();
			left.pop();
		}
		else
		{
			positionsToBeSorted[k++] = right.front();
			right.pop();
			inversions += left.size();
		}
	}

	while(!left.empty())
	{
		positionsToBeSorted[k++] = left.front();
		left.pop();
	}
	while(!right.empty())
	{
		positionsToBeSorted[k++] = right.front();
		right.pop();
	}

	return inversions;
}

long calculateYodaness(int lhs, int rhs)
{
	if(lhs < rhs)
	{
		int mid = lhs + (rhs - lhs) / 2;
		return calculateYodaness(lhs, mid) + calculateYodaness(mid + 1, rhs) + calculateSplitYodaness(lhs, mid, rhs);
	}
	return 0;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int tests, words;
	string word;

	cin >> tests;
	while (tests)
	{
		givenOrder.clear();
		positionsToBeSorted.clear();

		cin >> words;
		positionsToBeSorted.resize(words);
		for (int i = 0; i < words; i++)
		{
			cin >> word;
			givenOrder[word] = i;
		}

		for(int i = 0; i < words; i++)
		{
			cin >> word;
			positionsToBeSorted[i] = givenOrder[word];
		}
		cout << calculateYodaness(0, words - 1) << '\n';
		tests--;
	}
	return 0;
}