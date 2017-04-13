#define _CRT_SECURE_NO_WARNINGS
#include<deque>
#include<array>
#include<vector>
#include<algorithm>
#include<climits>
#include<cstring>
#include<iostream>
#include <string>
#include <set>
using namespace std;
typedef pair<int, int> position;
#define maxSize 1001
#define row first
#define col second
#define infinity INT_MAX / 2

int		xOff[] = { 0,0,1,-1 };
int		yOff[] = { 1,-1,0,0 };

string	map[maxSize];
int		guards[maxSize][maxSize];
int		rows, cols;

inline auto numberOfGuardsToBeKilled()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			guards[i][j] = infinity;

	auto isInMap = [&] (const position& position)
	{
		return position.row >= 0 && position.col >= 0 && position.row < rows && position.col < cols;
	};

	auto getCost = [&] (const position& source, const position& destination)
	{
		return map[source.row][source.col] == map[destination.row][destination.col] ? 0 : 1;
	};

	deque<position> q;
	guards[0][0] = 0;
	q.push_back({ 0,0 });
	while(!q.empty())
	{
		auto currentPosition = q.front();
		q.pop_front();

		for(int offset = 0; offset < 4;offset++)
		{
			position nextPosition = { currentPosition.row + yOff[offset], currentPosition.col + xOff[offset] };
			if(isInMap(nextPosition))
			{
				int cost = getCost(currentPosition, nextPosition);
				if(guards[currentPosition.row][currentPosition.col] + cost < guards[nextPosition.row][nextPosition.col])
				{
					guards[nextPosition.row][nextPosition.col] = guards[currentPosition.row][currentPosition.col] + cost;
					if (cost)
						q.push_back(nextPosition);
					else
						q.push_front(nextPosition);
				}
			}
		}
	}
	return guards[rows - 1][cols - 1];
}

int main()
{
	int tests;
	scanf("%d", &tests);

	while(tests)
	{
		scanf("%d %d", &rows, &cols);

		for (int row = 0; row < rows; row++)
		{
			char temp[1002];
			scanf("%s", &temp);
			map[row] = temp;
		}
				
		printf("%d\n", numberOfGuardsToBeKilled());
		tests--;
	}
}