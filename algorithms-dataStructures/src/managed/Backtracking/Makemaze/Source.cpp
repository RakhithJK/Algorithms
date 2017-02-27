#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
typedef pair<int, int> position;

string		map[21];
int			visited[21][21];
int			yOff[] = { -1, 1, 0, 0 };
int			xOff[] = { 0,0,-1,1 };
int			rows;
int			cols;
position	start;
position	destination;

inline bool isInMap(position current)
{
	return current.first >= 0 && current.second >= 0 && current.first < rows && current.second < cols;
}

bool canFindDeeperPath(position current, int pathLength = 1)
{
	if(current == destination)
		return true;

	visited[current.first][current.second] = pathLength;

	for(int o = 0; o < 4; o++)
	{
		position nextPos = {
			current.first + yOff[o],
			current.second + xOff[o]
		};

		if(
			isInMap(nextPos) && map[nextPos.first][nextPos.second] == '.'	&& 
			!visited[nextPos.first][nextPos.second]							&& 
			canFindDeeperPath(nextPos, pathLength + 1)
		)
		{
			return true;
		}
	}

	visited[current.first][current.second] = 0;
	return false;
}

bool isValidMaze()
{
	vector<position> openings;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if (map[i][j] == '.' && (i == 0 || j == 0 || i == rows - 1 || j == cols - 1))
				openings.push_back({ i, j });
		}
	}

	if (openings.size() != 2)
		return false;

	start		= openings[0];
	destination = openings[1];

	memset(visited, 0, sizeof(visited));

	return canFindDeeperPath(start);
}

int main()
{
	int tests;
	cin >> tests;
	for(int i = 0; i < tests; i++)
	{
		cin >> rows >> cols;
		int currentRow = 0;
		for (int row = 0; row <= rows; row++)
		{
			string temp;
			getline(cin, temp);
			if(!temp.empty())
			{
				remove_if(temp.begin(), temp.end(), [](const char character) { return iswspace(character); });
				map[currentRow] = temp;
				currentRow++;
			}
		}
		cout << (isValidMaze() ? "valid" : "invalid") << endl;
	}
	return 0;
}