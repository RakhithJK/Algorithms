#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<unordered_set>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<set>
using namespace std;

typedef pair<int, int> coordinates;

struct coords_hash {
	size_t operator () (const coordinates &c) const {
		auto h1 = std::hash<int>{}(c.first);
		auto h2 = std::hash<int>{}(c.second);
		return h1 ^ h2;
	}
};
struct position_distance
{
	position_distance() {}
	position_distance(coordinates coords, int distance = 0) {
		this->coords = coords;
		this->distance = distance;
	}
	coordinates coords;
	int distance = 0;
	bool operator<(const position_distance& rhs) const
	{
		return coords < rhs.coords;
	}
};

int			mouseMap[101][101];
int			catsMap[101][101];
const int	infinity = INT_MAX / 4;

int yOff[] = { -1,1,0,0 };
int xOff[] = { 0,0,-1,1 };

int					testsN, rows, cols;
coordinates			mouse, cat1, cat2;
set<coordinates>	visited;

inline double distance(coordinates x1, coordinates x2)
{
	return sqrt(pow(x1.first - x2.first, 2) + pow(x1.second - x2.second, 2));
}
inline bool isInMap(coordinates coords)
{
	return coords.first >= 0 && coords.second >= 0 && coords.first < rows && coords.second < cols;
}

void bfs(coordinates start, char type = 'm')
{
	visited.clear();
	queue<position_distance> q;
	q.push(position_distance(start, 1));
	mouseMap[start.first][start.second] = 1;
	while (!q.empty())
	{
		auto currentPos = q.front();
		q.pop();

		if (visited.find(currentPos.coords) != visited.end())
			continue;

		visited.insert(currentPos.coords);

		if (type == 'm')
			mouseMap[currentPos.coords.first][currentPos.coords.second] = min(mouseMap[currentPos.coords.first][currentPos.coords.second], currentPos.distance);
		if (type == 'c')
			catsMap[currentPos.coords.first][currentPos.coords.second] = min(catsMap[currentPos.coords.first][currentPos.coords.second], currentPos.distance);

		for (int i = 0; i < 4; i++)
		{
			auto nextRow = currentPos.coords.first + yOff[i];
			auto nextCol = currentPos.coords.second + xOff[i];
			coordinates nextCoords = { nextRow, nextCol };
			if (isInMap(nextCoords) && visited.find(nextCoords) == visited.end())
			{
				q.push(position_distance(nextCoords, currentPos.distance + 1));
			}
		}
	}
}

bool canMouseEscape()
{
	if (cols == 1 && rows == 1)
		return false;

	vector<coordinates> edges;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			mouseMap[row][col] = infinity;
			catsMap[row][col] = infinity;

			if (row == 0 || row == rows - 1 || col == 0 || cols == cols - 1)
				edges.push_back({ row,col });
		}
	}

	bfs(mouse, 'm');
	bfs(cat1, 'c');
	bfs(cat2, 'c');

	queue<position_distance> q;
	q.push(position_distance(mouse, 1));
	visited.clear();

	while (!q.empty())
	{
		auto currentPos = q.front();
		q.pop();

		if (visited.find(currentPos.coords) != visited.end())
			continue;

		if (find(edges.begin(), edges.end(), currentPos.coords) != edges.end())
			return true;

		visited.insert(currentPos.coords);

		for (int i = 0; i < 4; i++)
		{
			auto nextRow = currentPos.coords.first + yOff[i];
			auto nextCol = currentPos.coords.second + xOff[i];
			coordinates nextCoords = { nextRow, nextCol };
			if (isInMap(nextCoords) && mouseMap[nextRow][nextCol] < catsMap[nextRow][nextCol] && visited.find(nextCoords) == visited.end())
			{
				q.push(position_distance(nextCoords, currentPos.distance + 1));
			}
		}
	}
	return false;
}

int main()
{
	cin >> rows >> cols >> testsN;
	for (int t = 0; t < testsN; t++)
	{
		cin >> mouse.first >> mouse.second
			>> cat1.first >> cat1.second
			>> cat2.first >> cat2.second;

		mouse.first--;
		mouse.second--;
		cat1.first--;
		cat1.second--;
		cat2.first--;
		cat2.second--;

		cout << (canMouseEscape() ? "YES" : "NO") << endl;
	}
	return 0;
}