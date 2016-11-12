#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

stack<int> convertToBaseN(int N, int b)
{
	stack<int> decimals;
	while (N > 0)
	{
		decimals.push(N % b);
		N = N / b;
	}
	return decimals;
}

queue<int> findReplaceIndexesInEntry(string searchString)
{
	queue<int> replaceIndexes;

	for (int i = 0; i < searchString.size(); i++)
	{
		if (searchString[i] == '#')
			replaceIndexes.push(i);
	}

	return replaceIndexes;
}

int main()
{
	string			entry;
	vector<string>  subEntries;

	int n, m, k, x;
	cin >> n >> m >> k >> x;
	cin >> entry;

	for (int i = 0; i < m; i++)
	{
		string temp;
		cin >> temp;
		sort(temp.begin(), temp.end());	
		subEntries.push_back(temp);
	}

	queue<int> entryReplaceIndexes	  = findReplaceIndexesInEntry(entry);
	stack<int> subEntryReplaceIndexes = convertToBaseN(x - 1, k);

	int subEntryPosition = 0;
	while (!subEntryReplaceIndexes.empty() && !entryReplaceIndexes.empty())
	{
		int entryReplacePosition    = entryReplaceIndexes.front();
		int subEntryReplacePosition = subEntryReplaceIndexes.top();

		string subEntry = subEntries.at(subEntryPosition);

		entry[entryReplacePosition] = subEntry[subEntryReplacePosition];

		entryReplaceIndexes.pop();
		subEntryReplaceIndexes.pop();
		subEntryPosition++;
	}

	cout << entry << endl;
	return 0;
}