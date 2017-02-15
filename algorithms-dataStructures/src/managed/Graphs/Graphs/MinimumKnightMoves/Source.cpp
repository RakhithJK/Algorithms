#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

struct node {
	pair<int, int> location;
	node* parent;
};

string start;
string destination;
set<pair<int, int>> visited;

int numberOfTests;
vector<int> results;

inline pair<int, int> parseLocation(const string& location)
{
	auto x = location[1] - '0' - 1;
	auto y = location[0];

	if (y == 'a')
		return{ x, 0 };
	if (y == 'b')
		return{ x, 1 };
	if (y == 'c')
		return{ x, 2 };
	if (y == 'd')
		return{ x, 3 };
	if (y == 'e')
		return{ x, 4 };
	if (y == 'f')
		return{ x, 5 };
	if (y == 'g')
		return{ x, 6 };
	if (y == 'h')
		return{ x, 7 };
}
inline bool isInMap(const pair<int, int> &location)
{
	return location.first >= 0 && location.second >= 0 && location.first < 8 && location.second < 8;
}

int pathLength(node* current, int length = 0)
{
	if (current == nullptr)
		return length;

	return pathLength(current->parent, length + 1);
}
int calculateMinimumMoves()
{
	auto startLoc = parseLocation(start);
	auto destLoc = parseLocation(destination);

	queue<node*> nodesToVisit;
	node start;
	start.location = startLoc;
	start.parent = nullptr;

	nodesToVisit.push(&start);
	visited.clear();

	node* path;
	bool found = false;
	int xOff[8] = { -2, -2, -1, -1, 1, 1, 2 , 2 };
	int yOff[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	while (!nodesToVisit.empty() && !found)
	{
		auto currentNode = nodesToVisit.front();
		nodesToVisit.pop();
		if (currentNode->location.first == destLoc.first && currentNode->location.second == destLoc.second)
		{
			path = currentNode;
			found = true;
		}

		if (!found)
		{
			for (int i = 0; i < 8; i++)
			{
				pair<int, int> reachableLoc = { currentNode->location.first + xOff[i], currentNode->location.second + yOff[i] };
				if (isInMap(reachableLoc) && visited.find(reachableLoc) == visited.end())
				{
					node* next = new node();
					next->location = reachableLoc;
					next->parent = currentNode;
					nodesToVisit.push(next);
				}
			}
		}
	}

	auto moves = pathLength(path) - 1;
	return moves;
}

int main()
{
	cin >> numberOfTests;
	for (int i = 0; i < numberOfTests; i++)
	{
		cin >> start >> destination;
		results.push_back(calculateMinimumMoves());
	}

	for (auto result : results)
		cout << result << endl;

	return 0;
}