#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

typedef		pair<int,int>	node;
const		int				infinity = numeric_limits<int>::max() / 2;

int nOfMalls,
	sizeY, 
	sizeX,
	carX = infinity,
	carY = infinity;

string			row;
vector<string>	map;
int				distances[101][101];

inline bool isInMap(int y, int x)
{
	return y >= 0 && x >= 0 && y < sizeY && x < sizeX;
}
inline void bfs()
{
	queue<node> q;

	node car;
	car.first				= carY;
	car.second				= carX;
	distances[carY][carX]	= 0;
	q.push(car);

	int xOff[] = { 0, 0, -1, 1 };
	int yOff[] = { -1,1,0,0 };
	while(!q.empty())
	{
		auto currentPoint = q.front();
		auto currentPointDistance = distances[currentPoint.first][currentPoint.second];
		q.pop();

		for(int o = 0; o < 4; o++)
		{
			int newY = currentPoint.first + yOff[o];
			int newX = currentPoint.second + xOff[o];
			if(
				isInMap(newY, newX) && 
				distances[newY][newX] == infinity &&
				map[newY][newX] != '#'
			)
			{
				distances[newY][newX] = currentPointDistance + 1;
				q.push({ newY, newX });
			}
		}
	}
}
inline int	calculatePathCost()
{
	bfs();
	
	int maxPath = 0;
	int cost = 0;

	for(int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if(map[i][j] == 'S')
			{
				cost += 60 + 2 * distances[i][j];
				maxPath = max(maxPath, distances[i][j]);
			}
		}
	}

	return cost - maxPath;
}
inline void clearDistances()
{
	for (int row = 0; row < sizeY; row++)
		for (int col = 0; col < sizeX; col++)
			distances[row][col] = infinity;
}

int main()
{
	cin >> nOfMalls;

	for(int m = 0; m < nOfMalls; m++)
	{
		cin >> sizeY >> sizeX;
		clearDistances();
		map.clear();
		for (int y = 0; y < sizeY; y++)
		{
			cin >> row;
			map.push_back(row);
			auto maybeCar = row.find('C');

			if(maybeCar != string::npos)
			{
				carY = y;
				carX = maybeCar;
			}
		}

		cout << calculatePathCost() << endl;
	}
	return 0;
}