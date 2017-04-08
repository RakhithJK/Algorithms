#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include<vector>
#include<set>
#include<deque>
#include <climits>
#include<queue>
#include <functional>
#include <set>
#include<unordered_set>
using namespace std;

int pointsN, streetsN, source, destination;
typedef pair<int, int> edge;
typedef pair<int, int> state;
const int infinity = INT_MAX / 2;
#define point first
#define cost second

vector<vector<edge>> graph;
vector<vector<int>> parentOf;
set<edge> blockedEdges;

void bfs()
{
	queue<int> q;
	q.push(destination);
	while (!q.empty())
	{
		auto currentPoint = q.front();
		q.pop();

		for (auto previous : parentOf[currentPoint])
		{
			if (blockedEdges.find({ previous, currentPoint }) == blockedEdges.end())
			{
				blockedEdges.insert({ previous, currentPoint });
				q.push(previous);
			}
		}
	}
}
void dfs(int currentPoint)
{
	for (auto previous : parentOf[currentPoint])
	{
		if (blockedEdges.find({ previous, currentPoint }) == blockedEdges.end())
		{
			blockedEdges.insert({ previous, currentPoint });
			dfs(previous);
		}
	}
}

int getShortestPath()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	vector<int> distance(pointsN, infinity);
	distance[source] = 0;
	pq.push({ source, distance[source] });
	while (!pq.empty())
	{
		auto state = pq.top();
		pq.pop();
		for (auto adjacent : graph[state.point])
		{
			if (distance[state.point] + adjacent.cost <= distance[adjacent.point])
			{
				if (distance[state.point] + adjacent.cost < distance[adjacent.point]) {
					parentOf[adjacent.point].clear();
					parentOf[adjacent.point].push_back(state.point);
				}
				else
					parentOf[adjacent.point].push_back(state.point);

				distance[adjacent.point] = distance[state.point] + adjacent.cost;
				pq.push({ adjacent.point, distance[adjacent.point] });
			}
		}
	}
	dfs(destination); // or bfs()
	return distance[destination];
}

int getShortestPath_ignoreBlocked()
{
	priority_queue<state, vector<state>, greater<state>> pq;
	vector<int> distance(pointsN, infinity);
	distance[source] = 0;
	pq.push({ source, distance[source] });
	while (!pq.empty())
	{
		auto state = pq.top();
		pq.pop();
		for (auto adjacent : graph[state.point])
		{
			if (blockedEdges.find({ state.point, adjacent.point }) != blockedEdges.end())
				continue;
			if (distance[state.point] + adjacent.cost < distance[adjacent.point]) {
				distance[adjacent.point] = distance[state.point] + adjacent.cost;
				pq.push({ adjacent.point, distance[adjacent.point] });
			}
		}
	}
	return distance[destination] == infinity ? -1 : distance[destination];
}


int solve()
{
	if (getShortestPath() == infinity)
		return -1;
	return getShortestPath_ignoreBlocked();
}

inline int nextInt() {
	char c = getchar_unlocked();
	int x  = 0;
	while (c<'0' || c>'9') {
		c = getchar_unlocked();
	}
	while (c >= '0'&&c <= '9') {
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar_unlocked();
	}
	return x;
}

int main()
{
	pointsN		= nextInt();
	streetsN	= nextInt();
	
	while (pointsN && streetsN)
	{
		if (!pointsN && !streetsN)
			break;

		blockedEdges.clear();
		graph	 = vector<vector<edge>>(pointsN);
		parentOf = vector<vector<int>>(pointsN);

		source		= nextInt();
		destination = nextInt();

		for (int i = 0; i < streetsN; i++)
		{
			int lhs, rhs, weight;
			lhs		= nextInt();
			rhs		= nextInt();
			weight	= nextInt();
			graph[lhs].push_back({ rhs, weight });
		}
		printf("%d\n", solve());
		pointsN		= nextInt();
		streetsN	= nextInt();
	}
	return 0;
}