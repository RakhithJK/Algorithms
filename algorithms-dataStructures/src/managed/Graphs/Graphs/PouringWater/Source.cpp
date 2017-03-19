#include<set>
#include<map>
#include<iostream>
#include<array>
#include<queue>

using namespace std;

typedef pair<int, int>			jugStates;
typedef pair<jugStates, int>	state;

#define firstJug	first.first
#define secondJug	first.second
#define steps		second

int testsN, leftCapacity, rightCapacity, desiredCapacity;

int solve()
{
	queue<state> q;
	q.push({ {0,0}, 0 });
	set<jugStates> visited;

	while (!q.empty())
	{
		auto currentState = q.front();
		q.pop();

		if(currentState.firstJug == desiredCapacity || currentState.secondJug == desiredCapacity)
		{
			visited.insert({ currentState.firstJug, currentState.secondJug });
			return currentState.steps;
		}
	
		visited.insert({ currentState.firstJug, currentState.secondJug });
		vector<state> nextPossibleStates;

		if(currentState.firstJug < leftCapacity)
		{
			state nextStateWithSteps = { 
				{ leftCapacity, currentState.secondJug }, 
				currentState.steps + 1 
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}
		if (currentState.secondJug < leftCapacity)
		{
			state nextStateWithSteps = { 
				{ currentState.firstJug, rightCapacity }, 
				currentState.steps + 1
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}
		if (currentState.firstJug > 0)
		{
			state nextStateWithSteps = { 
				{ 0, currentState.secondJug },
				currentState.steps + 1
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}
		if (currentState.secondJug > 0)
		{
			state nextStateWithSteps = { 
				{ currentState.firstJug, 0 },
				currentState.steps + 1
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}
		if(currentState.secondJug > 0)
		{
			state nextStateWithSteps = {
				{
					min(currentState.firstJug + currentState.secondJug, leftCapacity),
					max(0, currentState.firstJug + currentState.secondJug - leftCapacity)
				}, 
				currentState.steps + 1 
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}
		if (currentState.firstJug > 0)
		{
			state nextStateWithSteps = {
				{
					max(0, currentState.firstJug + currentState.secondJug - rightCapacity),
					min(currentState.firstJug + currentState.secondJug, rightCapacity)
				}, 
				currentState.steps + 1 
			};
			nextPossibleStates.push_back(nextStateWithSteps);
		}

		for(auto state : nextPossibleStates)
		{
			if (visited.find({ state.firstJug, state.secondJug }) == visited.end())
				q.push(state);
		}
	}

	return -1;
}

int main()
{
	cin >> testsN;
	for (int t = 0; t < testsN; t++)
	{
		cin >> leftCapacity >> rightCapacity >> desiredCapacity;
		cout << solve() << "\n";
	}
	return 0;
}