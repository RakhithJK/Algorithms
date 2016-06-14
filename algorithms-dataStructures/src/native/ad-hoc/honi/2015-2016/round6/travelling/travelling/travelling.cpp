#include<iostream>	
#include<vector>
#include<algorithm>
using namespace std;


int		    selectBestCombination(vector<int>& allCombinations)
{
	return *max_element(allCombinations.begin(), allCombinations.end());
}

vector<int> calculateAllCombinations(const vector<int>& fruitWeights, int capacity)
{
	vector<int> combinations;
	int capacityCopy = capacity;
	int currentWeight = 0;

	for (int i = 0; i < fruitWeights.size() - 1; i++)
	{
		int currentFruit = fruitWeights[i];
		int fruitsCount = 0;
		for (int j = i + 1; j < fruitWeights.size() && currentWeight <= capacityCopy; j++)
		{
			fruitsCount++;
			int nextFruit = fruitWeights[j];
			currentWeight += nextFruit; 
		}
		combinations.push_back(fruitsCount);
		currentWeight = 0;
	}
	return combinations;
}

int main()
{
	vector<int> fruitWeights;

	int capacity, numberOfFruits;
	cin >> numberOfFruits >> capacity;
	
	for (auto i = 0; i < numberOfFruits; i++)
	{
		int currentFruitWeight;
		cin >> currentFruitWeight;
		fruitWeights.push_back(currentFruitWeight);
	}

	auto allCombinations = calculateAllCombinations(fruitWeights, capacity);
	cout << selectBestCombination(allCombinations) << endl;
}