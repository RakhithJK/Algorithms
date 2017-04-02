#include<vector>
#include<map>
#include<queue>
#include<iostream>
#include<functional>
#include<array>
#include<climits>
#include<algorithm>

using namespace std;

typedef pair<int, int> edge;
typedef pair<int, int> street;
typedef pair<int, int> timeInterval;

#define infinity	INT_MAX / 2
#define destination first
#define cost		second

int							intersectionsN, streetsN, lukaStart, lukaDestination, diff, georgeIntersectionsN;
vector<vector<edge>>		graph;
vector<int>					allowedIntersections_george;
map<street, timeInterval>	blocked;

inline bool isBlockedStreet(street street)
{
	return blocked.find(street) != blocked.end();		
}
inline timeInterval getBlockedIntervalFor(street street)
{
	return blocked[street];
}
inline int calculateWaitingTime(street street, int currentTime) {
	if (!isBlockedStreet(street))
		return 0;

	auto blockedInterval = getBlockedIntervalFor(street);
	auto blockStart = blockedInterval.first;
	auto blockEnd = blockedInterval.second;

	if (currentTime >= blockStart && currentTime < blockEnd)
		return blockEnd - currentTime;
	else
		return 0;
}
void processGeorge()
{
	int currentTime = 0;
	for(int i = 0; i < allowedIntersections_george.size() -1; i++)
	{
		int sourceIntersection		= allowedIntersections_george[i];
		int destinationIntersection = allowedIntersections_george[i + 1];
		auto edgeIterator			= find_if(graph[sourceIntersection].begin(), graph[sourceIntersection].end(), 
		[&](const edge& edgeFromSource)
		{
			return edgeFromSource.destination == destinationIntersection;
		});

		if(edgeIterator != graph[sourceIntersection].end())
		{
			blocked[{sourceIntersection, destinationIntersection}] = { currentTime, currentTime + edgeIterator->cost};
			blocked[{destinationIntersection, sourceIntersection}] = blocked[{sourceIntersection, destinationIntersection}];
			currentTime = currentTime + edgeIterator->cost;
		}
	}
}

int processLuka()
{
	priority_queue<int, vector<edge>, greater<edge>> pq;
	vector<int> distance(intersectionsN + 1);
	fill(distance.begin(), distance.end(), infinity);
	distance[lukaStart] = diff;
	pq.push({ lukaStart, diff });

	while (!pq.empty())
	{
		auto currentIntersection = pq.top();
		pq.pop();

		for (auto adjacent : graph[currentIntersection.destination])
		{
			auto penalty = calculateWaitingTime({ currentIntersection.destination, adjacent.destination }, distance[currentIntersection.destination]);
			if (distance[currentIntersection.destination] + adjacent.cost + penalty < distance[adjacent.destination])
			{
				distance[adjacent.destination] = distance[currentIntersection.destination] + adjacent.cost + penalty;
				pq.push({ adjacent.destination, distance[adjacent.destination] });
			}
		}
	}

	return distance[lukaDestination] - diff;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> intersectionsN >> streetsN;
	cin >> lukaStart >> lukaDestination >> diff >> georgeIntersectionsN;

	while(georgeIntersectionsN)
	{
		int intersection;
		cin >> intersection;
		allowedIntersections_george.push_back(intersection);
		georgeIntersectionsN--;
	}

	graph.resize(intersectionsN + 1);
	while(streetsN)
	{
		int source, destination, cost;
		cin >> source >> destination >> cost;
		graph[source].push_back({ destination, cost });
		graph[destination].push_back({ source, cost });
		streetsN--;
	}
	processGeorge();
	cout << processLuka();
	return 0;
}