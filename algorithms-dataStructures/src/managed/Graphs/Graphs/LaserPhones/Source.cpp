#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;

struct coordinates
{
	coordinates(){}
	coordinates(int row, int col)
	{
		this->row = row;
		this->col = col;
	}
	int row;
	int col;
	bool operator == (coordinates other) const
	{
		return other.row == row && other.col == col;
	}
};

int visited[101][101][2];
string terrain[101];
int yOff[] = { 0,0, -1, 1 };
int xOff[] = { -1, 1, 0,0 };

char direction[] = { 'h','h','v','v' };
coordinates cows[2];
int rowsN, colsN;
const int infinity = 1000000;

struct position_state
{
	position_state(){}

	position_state(coordinates coords, int cost, char direction)
	{
		this->coords = coords;
		this->cost = cost;
		this->direction = direction;
	}

	coordinates coords;
	int cost;
	char direction;

	inline int directionToInt() const
	{
		return direction == 'h' ? 0 : 1;
	}

	bool isVisited() const
	{
		return visited[coords.row][coords.col][directionToInt()] == 1;
	}
	void visit() const
	{
		visited[coords.row][coords.col][directionToInt()] = 1;
	}

	bool operator < (position_state other) const
	{
		return this->cost  > other.cost;
	}
};


inline bool shouldGoTo(coordinates pos)
{
	if(pos.row >= 0 && pos.col >= 0 && pos.row < rowsN && pos.col < colsN)
	{
		if(terrain[pos.row][pos.col] != '*')
			return true;

		return false;
	}
	return false;
}


long calculate()
{
	priority_queue<position_state, vector<position_state>> q;

	auto start1 = position_state(cows[0], 0, 'h');
	auto start2 = position_state(cows[0], 0, 'v');
	q.push(start1);
	q.push(start2);

	int pathCost = infinity;
	while (!q.empty())
	{
		auto top = q.top();
		q.pop();
		if(top.coords == cows[1])
		{
			pathCost = min(pathCost, top.cost);
		}
		if (top.isVisited())
			continue;
		top.visit();
	
		for (int i = 0; i < 4; i++)
		{
			auto nextCoords = coordinates(top.coords.row + yOff[i], top.coords.col + xOff[i]);
			
			if(shouldGoTo(nextCoords))
			{
				if (top.direction == 'h')
				{
					if (top.coords.row == nextCoords.row)
						q.push(position_state(nextCoords, top.cost, 'h'));
					else
						q.push(position_state(nextCoords, top.cost + 1, 'v'));
				}
				else
				{
					if (top.coords.col == nextCoords.col)
						q.push(position_state(nextCoords, top.cost, 'v'));
					else
						q.push(position_state(nextCoords, top.cost + 1, 'h'));
				}
			}
		}
	}

	return pathCost;
}


int main()
{
	cin >> colsN >> rowsN;

	int cowIndex = -1;
	for(int row = 0; row < rowsN; row++)
	{
		cin >> terrain[row];

		if (cowIndex < 2)
		{
			for(int i = 0; i <colsN && cowIndex < 2; i++)
			{
				if (terrain[row][i] == 'C')
				{
					cowIndex++;
					cows[cowIndex] = {row, i};
				}
			}
		}
	}
	cout << calculate() << endl;
	return 0;
}