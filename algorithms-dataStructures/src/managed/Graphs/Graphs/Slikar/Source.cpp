#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
#include<string>
#include<cstring>

using namespace std;

#define infinity			INT_MAX / 2 
#define row					first
#define col					second
#define location			first
#define positionElapsedTime second

typedef pair<int, int>				position;
typedef pair<pair<int, int>, int>	position_time;
int				rowsN, columnsN;
vector<string>	terrain;
int				was[51][51];
bool			visited[51][51];
position		source;
position		destination;

int xOff[] = { 0, 0, -1,1 };
int yOff[] = { 1, -1, 0,0 };

bool isInMap(position p) {
	return p.row >= 0 && p.col >= 0 && p.row < rowsN && p.col < columnsN;
}

void dfs(position currentPosition, int elapsedTime = 0) {
	for (int off = 0; off < 4; off++)
	{
		position next = {
			currentPosition.row + yOff[off],
			currentPosition.col + xOff[off]
		};
		if (isInMap(next) && terrain[next.row][next.col] == '.' && elapsedTime + 1 < was[next.row][next.col]) {
			was[next.row][next.col] = elapsedTime + 1;
			dfs(next, elapsedTime + 1);
		}
	}
}

void flood_fill() {
	vector<position> floodStartPoints;
	for (int i = 0; i < rowsN; i++)
		for (int j = 0; j < columnsN; j++)
			if (terrain[i][j] == '*')
				floodStartPoints.push_back({ i, j });

	for (auto floodStartPoint : floodStartPoints)
	{
		was[floodStartPoint.row][floodStartPoint.col] = 0;
		dfs(floodStartPoint);
	}
}

int bfs() {
	queue<position_time> q;
	q.push({ source, 0 });
	memset(&visited, false, sizeof visited);
	while (!q.empty())
	{
		auto currentPosition = q.front();
		q.pop();
		if (visited[currentPosition.location.row][currentPosition.location.col])
			continue;
		visited[currentPosition.location.row][currentPosition.location.col] = true;
		if (currentPosition.location == destination)
			return currentPosition.positionElapsedTime;
		for (int off = 0; off < 4; off++)
		{
			position next = {
				currentPosition.location.row + yOff[off],
				currentPosition.location.col + xOff[off]
			};
			if (	
				isInMap(next)																&& 
				(terrain[next.row][next.col] == '.' || terrain[next.row][next.col] == 'D')	&& 
				currentPosition.positionElapsedTime + 1 < was[next.row][next.col]
			) 
			{
				if (visited[next.row][next.col])
					continue;
				q.push({ next, currentPosition.positionElapsedTime + 1 });
			}
		}
	}
	return infinity;
}

int main() {
	scanf("%d %d", &rowsN, &columnsN);
	char line[51];
	terrain = vector<string>(rowsN);
	for (int i = 0; i < rowsN; i++) {
		scanf("%s", &line);
		terrain[i]				 = line;
		auto sourcePosition		 = terrain[i].find('S');
		auto destinationPosition = terrain[i].find('D');
		if (sourcePosition != string::npos)
			source = { i, sourcePosition };
		if (destinationPosition != string::npos)
			destination = { i, destinationPosition };
	}
	for (int i = 0; i < rowsN; i++)
		for (int j = 0; j < columnsN; j++)
			was[i][j] = infinity;
	flood_fill();
	auto pathDistance = bfs();
	printf("%s", pathDistance != infinity ? to_string(pathDistance).c_str() : "KAKTUS");
	return 0;
}