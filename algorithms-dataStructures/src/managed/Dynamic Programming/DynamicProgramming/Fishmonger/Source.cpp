#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, pair<int, int>> currentState;

#define maxStations 55
#define maxTime		1500
#define infinity	INT_MAX - 1
#define destination first
#define time		second.first
#define tols		second.second

int travellingTimeFromTo[maxStations][maxStations];
int tollFromTo[maxStations][maxStations];
int stationsN, availableTime;

pair<int,int> calculateMaxTollFromTo_dijkstra()
{
	auto stateComparer = [](const currentState lhs, const currentState rhs)
	{
		if (lhs.time == rhs.time)
			return lhs.tols > rhs.tols;
		return lhs.time > rhs.time;
	};
	priority_queue<currentState, vector<currentState>, decltype(stateComparer)> pq(stateComparer);

	int visitedStates[maxStations][maxTime];
	memset(visitedStates, false, sizeof visitedStates);
	pq.push({ 0,{0,0} });
	auto minimumToll = infinity;
	auto minimumTime = infinity;

	while(!pq.empty())
	{
		auto currentStation = pq.top().destination;
		auto elapsedTime = pq.top().time;
		auto currentTols = pq.top().tols;

		pq.pop();

		if(currentStation == stationsN -1)
		{
			if(currentTols < minimumToll)
			{
				minimumToll = currentTols;
				minimumTime = elapsedTime;
			}
			continue;
		}

		if(visitedStates[currentStation][elapsedTime])
			continue;

		for (auto adjacentStation = 0; adjacentStation < stationsN; adjacentStation++)
		{
			if(currentStation == adjacentStation)
				continue;

			currentState nextState = { 
				adjacentStation, 
				{ 
					elapsedTime + travellingTimeFromTo[currentStation][adjacentStation], 
					currentTols + tollFromTo[currentStation][adjacentStation]
				}
			};

			if (visitedStates[nextState.destination][nextState.time])
				continue;
			if (nextState.time <= availableTime)
				pq.push(nextState);
		}	

		visitedStates[currentStation][elapsedTime] = true;
	}
	return { minimumToll, minimumTime };
}

int minAmountOfTolsForStationAtTime[maxStations][maxTime];
int visitedStates[maxStations][maxTime];

void calculateMaxTollFromTo_recursively(int currentStation, int elapsedTime, int tolsCost)
{
	if (elapsedTime > availableTime || visitedStates[currentStation][elapsedTime])
		return;

	visitedStates[currentStation][elapsedTime] = true;

	if (currentStation == stationsN - 1)
	{		
		minAmountOfTolsForStationAtTime[currentStation][elapsedTime] = 
			minAmountOfTolsForStationAtTime[currentStation][elapsedTime] != -1 ?
			min(minAmountOfTolsForStationAtTime[currentStation][elapsedTime], tolsCost) :
			tolsCost;

		visitedStates[currentStation][elapsedTime] = false;
	}

	for (auto adjacentStation = 0; adjacentStation < stationsN; adjacentStation++)
	{
		if (currentStation == adjacentStation)
			continue;

		currentState nextState = {
			adjacentStation,
			{
				elapsedTime + travellingTimeFromTo[currentStation][adjacentStation],
				tolsCost + tollFromTo[currentStation][adjacentStation]
			}
		};

		if (nextState.time <= availableTime)
			calculateMaxTollFromTo_recursively(nextState.destination, nextState.time, nextState.tols);
	}
}

pair<int,int> calculateMaxTollFromTo_recursively()
{
	memset(minAmountOfTolsForStationAtTime, -1, sizeof minAmountOfTolsForStationAtTime);
	memset(visitedStates, false, sizeof visitedStates);
	calculateMaxTollFromTo_recursively(0,0,0);

	auto minimumToll = infinity;
	auto minimumTime = infinity;

	for (auto elapsedTime = 0; elapsedTime <= availableTime; elapsedTime++)
	{
		if(minAmountOfTolsForStationAtTime[stationsN - 1][elapsedTime] == -1)
			continue;
		if(minAmountOfTolsForStationAtTime[stationsN - 1][elapsedTime] < minimumToll)
		{
			minimumToll = minAmountOfTolsForStationAtTime[stationsN - 1][elapsedTime];
			minimumTime = elapsedTime;
		}
	}
	return { minimumToll, minimumTime };
}
int main()
{
	while (scanf("%d %d", &stationsN, &availableTime) && stationsN && availableTime)
	{
		for (auto sourceStation = 0; sourceStation < stationsN; sourceStation++)
			for (auto destinationStation = 0; destinationStation < stationsN; destinationStation++)
				scanf("%d", &travellingTimeFromTo[sourceStation][destinationStation]);

		for (auto sourceStation = 0; sourceStation < stationsN; sourceStation++)
			for (auto destinationStation = 0; destinationStation < stationsN; destinationStation++)
				scanf("%d", &tollFromTo[sourceStation][destinationStation]);


		auto solution = calculateMaxTollFromTo_dijkstra();

		printf("%d %d\n", solution.first, solution.second);
	}
	return 0;
}