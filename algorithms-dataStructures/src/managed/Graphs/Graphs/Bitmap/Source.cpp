#define _CRT_SECURE_NO_WARNINGS
#include<deque>
#include<iostream>
#include<climits>
#include<string>
#include <vector>
#include<queue>

using namespace std;

#define maxSize 200
typedef pair<int, int> position;
#define row first
#define col second
#define infinity INT_MAX / 2

vector<string> map;
int distances[maxSize][maxSize];
int rows, cols;

int offsetX[] = { -1,1, 0,0, };
int offsetY[] = { 0,0 ,1, -1, };

queue<position> sources;

void computeDistances(position source)
{
	auto isInMap = [&](const position& p) { return p.row >= 0 && p.col >= 0 && p.row < rows && p.col < cols; };
	auto at		 = [&](const position& p) { return map[p.row][p.col]; };

	auto getCostFor = [&](const position& start, const position& destination) {
		auto sourcePixel	  = at(start);
		auto destinationPixel = at(destination);
		return (sourcePixel == '0' && destinationPixel == '0') ? 1 : sourcePixel != destinationPixel;
	};

	deque<position> pq;
	distances[source.row][source.col] = 0;
	pq.push_back(source);

	while (!pq.empty())
	{
		auto currentPos = pq.front();
		pq.pop_front();

		for (auto offset = 0; offset < 4; offset++)
		{
			position nextPos = {
				currentPos.row + offsetY[offset],
				currentPos.col + offsetX[offset]
			};

			if (isInMap(nextPos))
			{
				int cost = getCostFor(currentPos, nextPos);
				if (distances[currentPos.row][currentPos.col] + cost < distances[nextPos.row][nextPos.col])
				{
					distances[nextPos.row][nextPos.col] = distances[currentPos.row][currentPos.col] + cost;
					if (cost)
						pq.push_back(nextPos);
					else
						pq.push_front(nextPos);
				}
			}
		}
	}
}

void solve()
{
	for (auto i = 0; i < rows; i++)
		for (auto j = 0; j < cols; j++)
			distances[i][j] = infinity;

	while(!sources.empty())
	{
		auto source = sources.front();
		sources.pop();
		computeDistances(source);
	}
}

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests)
	{
		scanf("%d %d", &rows, &cols);
		map = vector<string>(rows);
		for (int i = 0; i < rows; i++)
		{
			char line[maxSize];
			scanf("%s", &line);
			map[i] = line;
			for (int j = 0;  j < cols; j++)
				if (map[i][j] == '1')
					sources.push({ i,j });
		}
		solve();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (j == cols - 1)
					printf("%d", distances[i][j]);
				else
					printf("%d ", distances[i][j]);
			}
			printf("\n");
		}
		tests--;
	}
	return 0;
}