#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<algorithm>
#include<numeric>

using namespace std;

vector<vector<int> > solutions;
	
void permute(vector<int> coins, vector<int> counts, int startIndex, int totalAmount, int desiredValue)
{
	if (startIndex >= coins.size())
	{
		vector<int> solution;
		for (int i = 0; i < coins.size(); i++) {
			if (counts[i] > 0)
			{
				solution.push_back(coins[i]);
			}
		}
		auto sum = accumulate(solution.begin(), solution.end(), 0);
		if (sum == desiredValue && solution.size() > 1)
			solutions.push_back(solution);
		return;
	}

	if (startIndex == coins.size() - 1)
	{
		if (totalAmount%coins[startIndex] == 0)
		{
			counts[startIndex] = totalAmount / coins[startIndex];
			permute(coins, counts, startIndex + 1, 0, desiredValue);
		}
	}
	else
	{
		for (int i = 0; i <= totalAmount / coins[startIndex]; i++)
		{
			counts[startIndex] = i;
			permute(coins, counts, startIndex + 1, totalAmount - coins[startIndex] * i, desiredValue);
		}
	}
}

int main() {
	int N;
	cin >> N;
	int counter = 0;
	vector<int> input(N);
	for (int i = 0; i < N; i++)
	{
		cin >> input[i];
	}
	vector<int> counts;

	for (int i = 0; i < 10000; i++)
	{
		counts.push_back(0);
	}

	for (int i = input.size() - 1; i > -1; i--)
	{
		permute(input, counts, 0, input[i], input[i]);

		sort(solutions.begin(), solutions.end(), [](vector<int>& lhs, vector<int> & rhs) { return lhs.size() < rhs.size(); });
		if (solutions.size() > 0)
		{
			auto solution = solutions[0];
			counter += input[i];
			input.erase(find(input.begin(), input.end(), input[i]));
			i--;
			for (int z = 0; z < solution.size(); z++)
			{
				input.erase(find(input.begin(), input.end(), solution[z]));
				i--;
			}

		}
		counts.clear();
		for (int i = 0; i < 10000; i++)
		{
			counts.push_back(0);
		}
		solutions.clear();
	}

	cout << counter + accumulate(input.begin(),input.end(),0);
}