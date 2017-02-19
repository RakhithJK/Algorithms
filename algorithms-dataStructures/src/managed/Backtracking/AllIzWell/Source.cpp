#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<unordered_set>
using namespace std;

struct coords_hash
{
	size_t operator () (pair<int, int> const& p) const
	{
		return (hash<int>()(p.first) + hash<int>()(p.second));
	}
};
typedef pair<int, int> coords;

int									maxRow, maxCol;
vector<string>						chars;
string								pattern = "ALLIZZWELL";
unordered_set<coords, coords_hash>	visited;

bool isInMap(int i, int j) {
	return (i >= 0 && i < maxRow && j >= 0 && j < maxCol);
}
bool canFindMorePatternParts(int row, int col, int pathIndex)
{
	if (pathIndex == pattern.size() - 1)
		return true;

	visited.insert({ row,col });

	int xOff[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
	int yOff[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };

	for(int offset = 0; offset < 8; offset++)
	{
		auto nextRow = row + yOff[offset];
		auto nextCol = col + xOff[offset];
		if (
			isInMap(nextRow, nextCol)							&&
			visited.find({ nextRow, nextCol }) == visited.end() &&
			pattern[pathIndex + 1] == chars[nextRow][nextCol]	&&
			canFindMorePatternParts(nextRow, nextCol, pathIndex + 1)
		)
		{
			return true;
		}
	}

	visited.erase(visited.find({ row, col }));
	return false;
}
bool didFindPattern()
{
	bool found = false;

	for(int row = 0; row < maxRow && !found; row++)
		for(int col = 0; col < maxCol && !found; col++)
			if(chars[row][col] == pattern.at(0))
				found = canFindMorePatternParts(row, col, 0);

	return found;
}

int main()
{
	int testsNumber;
	cin >> testsNumber;

	for (int t = 0; t < testsNumber; t++)
	{
		cin >> maxRow >> maxCol;
		chars.resize(maxRow);
		for (int row = 0; row < maxRow; row++)
		{
			string temp;
			cin >> temp;
			chars[row] = temp;
		}

		cout << (didFindPattern() ? "YES\n" : "NO\n");
		visited.clear();
		chars.clear();
	}
	return 0;
}