#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<stack>

using namespace std;

int xMax, yMax;
vector<string> grid;
vector<vector<int>> visited;
int currentFlood = 0, traps = 0;

inline bool isInGrid(int row, int col)
{
	return row >= 0 && col >= 0 && row < xMax && col < yMax;
}

void floodFill(int row, int col)
{
	if (!visited[row][col])
	{
		visited[row][col] = currentFlood;

		if (grid[row][col] == 'S' && isInGrid(row + 1, col))
			floodFill(row + 1, col);
		if (grid[row][col] == 'N' && isInGrid(row - 1, col))
			floodFill(row - 1, col);
		if (grid[row][col] == 'E' && isInGrid(row, col + 1))
			floodFill(row, col + 1);
		if (grid[row][col] == 'W' && isInGrid(row, col - 1))
			floodFill(row, col - 1);

		visited[row][col] = currentFlood;
	}
	else
		currentFlood = visited[row][col];
}

int calculateNumberOfTraps()
{
	for (int i = 0; i < xMax; i++)
	{
		for(int j = 0; j < yMax; j++)
		{
			currentFlood = traps + 1;
 			floodFill(i, j);

			for (int k = 0; k < xMax; k++)
			{
				for(int l = 0; l < yMax; l++)
				{
					cout << visited[k][l];
				}
				cout << endl;
			}
			cout << endl;

			if (currentFlood > traps)
				traps++;
		}
	}
	return traps;
}

int main()
{
	scanf("%d %d", &xMax, &yMax);
	vector<int> emptyBlock;
	emptyBlock.resize(yMax);
	fill(emptyBlock.begin(), emptyBlock.end(), 0);
	string row;

	for (auto i = 0; i < xMax; i++)
	{
		cin >> row;
		grid.push_back(row);
		visited.push_back(emptyBlock);
	}

	printf("%d", calculateNumberOfTraps());
	return 0;
}
