#include<iostream> 
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;
typedef unsigned long long bigint;

struct cow
{
	size_t profit;
	size_t deadline;
};

int numberOfCows;
vector<cow> cows;

bool cows_stable_comparer(const cow& lhs, const cow& rhs)
{
	return lhs.profit > rhs.profit;
}

bigint maxGallons()
{
	stable_sort(cows.begin(), cows.end(), cows_stable_comparer);

	bigint gallons = 0;

	auto maxDeadline = 0;
	for(auto &cow : cows)
	{
		if(cow.deadline > maxDeadline)
			maxDeadline = cow.deadline;
	}

	unordered_map<int, bool> timeSlots;
	for (auto i = 1; i <= maxDeadline; i++)
	{
		timeSlots.insert({ i , false });
	}
	
	for (auto &cow : cows)
	{
		auto placeDeadline = cow.deadline;
		auto placed		   = false;
		while (placeDeadline && !placed)
		{
			if (!timeSlots[placeDeadline]) {
				timeSlots[placeDeadline] = true;
				gallons += cow.profit;
				placed = true;
			}
			else
				placeDeadline--;
		}
	}
	return gallons;
}

int main()
{
	cin >> numberOfCows;
	for (int i = 0; i < numberOfCows; i++)
	{
		cow cow;
		cin >> cow.profit >> cow.deadline;
		cows.push_back(cow);
	}
	
	cout << maxGallons() << endl;
	system("pause");
	return 0;
}