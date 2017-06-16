#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int rowsN, colsN, patternsN;
int terrain[25][25][25];

struct position
{
	position(int row, int col, int pattern, int distance)
	{
		this->row = row;
		this->col = col;
		this->pattern = pattern;
		this->distance = distance;
	}
	bool canVisit() const
	{
		return row >= 0 && col >= 0 && row < rowsN && col < colsN &&
			   terrain[pattern][row][col] == 0;
	}
	void visit() const { terrain[pattern][row][col] = 1; }
	int row;
	int col;
	int pattern;
	int distance;
};

#define directions 5
int yOff[] = { 0,1,-1,0,0 };
int xOff[] = { 0,0,0,1,-1 };

int bfs() {
	queue<position> q;
	q.push(position(0,0,0,0));
	terrain[0][0][0] = 1;
	while (!q.empty()) {
		auto currentPosition = q.front();
		q.pop();

		if (currentPosition.row == rowsN - 1 && currentPosition.col == colsN - 1) 
			return currentPosition.distance;
		
		for (auto direction = 0; direction < directions; direction++) {
			auto nextPosition = position(
				currentPosition.row + yOff[direction], 
				currentPosition.col + xOff[direction], 
				(currentPosition.pattern + 1) % patternsN, 
				currentPosition.distance + 1
			);

			if(!nextPosition.canVisit())
				continue;
			nextPosition.visit();
			q.push(nextPosition);
		}
	}
	return -1;
}

int main() {
	auto currentTest = 0;
	string line;
	memset(terrain, 0, sizeof terrain);

	while (true) {
		scanf("%d %d %d", &rowsN, &colsN, &patternsN);
		if (rowsN == 0 && colsN == 0 && patternsN == 0)
			break;
		for (auto pattern = 0; pattern < patternsN; pattern++) {
			for (auto row = 0; row < rowsN; row++) {
				cin >> line;
				for (auto col = 0; col < colsN; col++) {
					terrain[pattern][row][col] = line[col] - '0';
				}
			}
		}
		auto distance = bfs();
		if (distance == -1) {
			printf("Case %d: Luke and Leia cannot escape.\n", ++currentTest);
		}
		else
			printf("Case %d: Luke and Leia can escape in %d steps.\n", ++currentTest, distance);
	}
	return 0;
}