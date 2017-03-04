#include<iostream>
#include<queue>
#include<string>
#include<cmath>
#include <functional>

using namespace std;

typedef long long bigint;
typedef pair<int, int> state;

bigint visited[1000001];

int floors, start, destination, upCount, downCount;

inline bool inBuilding(int nextLevel)
{
	return nextLevel >= 0 && nextLevel <= floors;
}

inline bool distanceFromDestination(int level)
{
	return abs(destination - level);
}

pair<bool, bigint> calculatePressesNeeded() {
	if (start == destination)
		return { true, 0 };

	if (destination > floors)
		return { false, -1 };

	priority_queue<state, vector<state>, greater<state>> q;
	visited[start] = 1;
	q.push({ start, distanceFromDestination(start) });

	while (!q.empty())
	{
		auto currentState = q.top();
		auto currentLevel = currentState.first;
		q.pop();

		if(currentLevel == destination)
		{
			return { true, visited[destination] - 1 };
		}
		
		auto nextAbove = currentLevel + upCount;
		auto nextBelow = currentLevel - downCount;

		if (inBuilding(nextAbove))
		{
			if (!visited[nextAbove])
			{
				visited[nextAbove] = visited[currentLevel] + 1;
				q.push({ nextAbove, distanceFromDestination(nextAbove) });
			}
		}

		if (inBuilding(nextBelow))
		{
			if (!visited[nextBelow])
			{
				visited[nextBelow] = visited[currentLevel] + 1;
				q.push({ nextBelow, distanceFromDestination(nextBelow) });
			}
		}
	}
	return { false, -1 };
}

int main()
{
	cin >> floors >> start >> destination >> upCount >> downCount;
	auto result = calculatePressesNeeded();
	cout << (result.first ? to_string(result.second) : "use the stairs");
	return 0;
}