#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include <set>
#include <map>
using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;
	vector<int> numbers(n);
	queue<pair<int, int> > questions;

	for (auto i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		numbers[i] = temp;
	}
	
	for (auto i = 0; i < q; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		questions.push({ temp1 - 1, temp2 - 1 });
	}

	map<int, int> pojavljeni;
	vector<int> results;
	const int one = 1;
	while(!questions.empty())
	{
		auto question = questions.front();
		for (auto i = question.first; i <= question.second; i++)
		{
			if (pojavljeni.find(numbers[i]) == pojavljeni.end()) {
				pojavljeni.insert({ numbers[i], one });
			}
			else
			{
				auto prev = pojavljeni.at(numbers[i]);
				pojavljeni[numbers[i]] = prev + 1;
			}
		}

		for_each(pojavljeni.begin(), pojavljeni.end(), [&](pair<int,int> o)
		{
			if(o.second == 2)
			{
				results.push_back(o.first);
			}
		});
		
	
		cout << results.size() << endl;

		pojavljeni.clear();
		results.clear();
		questions.pop();
	}

	return 0;
}