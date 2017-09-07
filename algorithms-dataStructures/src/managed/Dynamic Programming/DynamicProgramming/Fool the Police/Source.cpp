#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

int stationsN, deadlineTime;

#define infinity INT_MAX / 2
#define maxStations 105

struct state
{
	int currentStation;
	int currentTime;
	int currentRisk;

	state() { currentTime = infinity; currentRisk = infinity; }
	state(int station, int time, int risk) { this->currentStation = station; this->currentTime = time; this->currentRisk = risk; }
	bool operator == (const state& other) const { return other.currentStation == currentStation && other.currentRisk == currentRisk && other.currentTime == currentTime; }
};

int		travellingTimeFromTo[maxStations][maxStations];
int		riskFromTo[maxStations][maxStations];
bool	visitedInCurrentPath[maxStations];
int		minimumRisk = infinity;
int		minimumTime = infinity;

state compute_min_risk_with_dijkstra()
{
	auto stateLessThan = [](const state& lhs, const state& rhs)
	{
		if (lhs.currentTime == rhs.currentTime)
			return lhs.currentRisk > rhs.currentRisk;
		return lhs.currentTime > rhs.currentTime;
	};

	priority_queue<state, vector<state>, decltype(stateLessThan)> pq(stateLessThan);

	bool visited[maxStations][maxStations];
	memset(visited, false, sizeof visited);

	state initial(0, 0, 0);
	state solution(stationsN - 1, infinity, infinity);

	pq.push(initial);

	while (!pq.empty())
	{
		auto currentState = pq.top();
		pq.pop();

		if (visited[currentState.currentStation][currentState.currentTime] || currentState.currentTime > deadlineTime)
			continue;

		if (currentState.currentStation == stationsN - 1)
		{
			if (currentState.currentRisk <= solution.currentRisk)
			{
				solution.currentRisk = currentState.currentRisk;
				solution.currentTime = currentState.currentTime;
			}
			continue;
		}

		visited[currentState.currentStation][currentState.currentTime] = true;

		for (auto adjacentStation = 0; adjacentStation < stationsN; adjacentStation++)
		{
			if (adjacentStation == currentState.currentStation)
				continue;

			auto nextState = state(
				adjacentStation,
				currentState.currentTime + travellingTimeFromTo[currentState.currentStation][adjacentStation],
				currentState.currentRisk + riskFromTo[currentState.currentStation][adjacentStation]
			);

			pq.push(nextState);
		}
	}

	return solution;
}
int   compute_min_risk_with_dfs(int currentStation = 0, int elapsedTime = 0, int elapsedRisk = 0)
{
	if (currentStation == stationsN - 1)
	{
		if(elapsedRisk < minimumRisk)
		{
			minimumRisk = elapsedRisk;
			minimumTime = elapsedTime;
		}
		if(elapsedRisk == minimumRisk)
		{
			minimumTime = min(minimumTime, elapsedTime);
		}
		return 0;
	}
		
	if (elapsedTime > deadlineTime || elapsedRisk > minimumRisk)
		return infinity;

	auto minRiskFromSubpaths = infinity;

	for (auto adjacentStation = 0; adjacentStation < stationsN; adjacentStation++)
	{
		if (adjacentStation == currentStation)
			continue;
		if(visitedInCurrentPath[adjacentStation])
			continue;
		if(elapsedTime + travellingTimeFromTo[currentStation][adjacentStation] > deadlineTime)
			continue;

		visitedInCurrentPath[adjacentStation] = true;
		
		minRiskFromSubpaths = min(
			minRiskFromSubpaths,
			compute_min_risk_with_dfs(adjacentStation, elapsedTime + travellingTimeFromTo[currentStation][adjacentStation], elapsedRisk + riskFromTo[currentStation][adjacentStation]) + riskFromTo[currentStation][adjacentStation]
		);

		visitedInCurrentPath[adjacentStation] = false;
	}

	return minRiskFromSubpaths;
}

int main()
{
	int tests;

	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &stationsN, &deadlineTime);

		for (auto sourceStation = 0; sourceStation < stationsN; sourceStation++)
			for (auto destinationStation = 0; destinationStation < stationsN; destinationStation++)
				scanf("%d", &travellingTimeFromTo[sourceStation][destinationStation]);

		for (auto sourceStation = 0; sourceStation < stationsN; sourceStation++)
			for (auto destinationStation = 0; destinationStation < stationsN; destinationStation++)
				scanf("%d", &riskFromTo[sourceStation][destinationStation]);

		memset(visitedInCurrentPath, false, sizeof visitedInCurrentPath);
		minimumRisk = infinity;
		minimumTime = infinity;
		visitedInCurrentPath[0] = true;
		compute_min_risk_with_dfs();

		if (minimumRisk == infinity)
			printf("-1\n");
		else
			printf("%d %d\n", minimumRisk, minimumTime);
	}
	return 0;
}