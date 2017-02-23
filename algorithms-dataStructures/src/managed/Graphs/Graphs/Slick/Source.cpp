#include<iostream>
#include<string>
#include<map>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int rows, cols;
int image[251][251];
int visited[251][251];
map<int, int> sectors;

int xOff[] = { -1,1,0,0, -1, 1, -1 , 1 };
int yOff[] = { 0,0,-1,1, -1, 1, 1, -1};

int componentsCount = 0;
int sectorMark = 1;

inline bool shouldGoTo(int row, int col)
{
	if(row >= 0 && col >= 0 && row < rows && col < cols)
	{
		if (image[row][col] == 1 && visited[row][col] == 0)
			return true;
		return false;
	}
	return false;
}

inline void addOrUpdateSectorArea(int sectorArea, int sectorsCount)
{
	if (sectors.find(sectorArea) != sectors.end())
		sectors[sectorArea]++;
	sectors.insert({ sectorArea, sectorsCount });
}

void flood_fill(int row, int col)
{
	visited[row][col] = sectorMark;
	componentsCount++;
	for(int i = 0; i < 4; i++)
	{
		if (shouldGoTo(row + yOff[i], col + xOff[i]))
			flood_fill(row + yOff[i], col + xOff[i]);
	}
}

inline void calculateNumberOfConnectedComponents()
{
	for(int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (visited[row][col] == 0 && image[row][col] == 1)
			{
				componentsCount = 0;
				sectorMark++;
				flood_fill(row, col);
				addOrUpdateSectorArea(componentsCount, 1);
			}
		}
	}
}

pair<int,int> parseGridSize(const string& line)
{
	vector<int> dimensions;
	string current;
	for(int i = 0; i < line.size(); i++)
	{
		if (!iswspace(line[i]))
			current += to_string(line[i] - '0');
		else
		{
			dimensions.push_back(stoi(current));
			current.clear();
		}
	}
	dimensions.push_back(stoi(current));
	current.clear();
	if (dimensions.size() == 2)
		return{ dimensions[0], dimensions[1] };
	return { -1, -1 };
}



int main()
{
	vector<pair<int, map<int, int>>> results;

	int populatedRows = 0;

	string currentLine;
	while(true)
	{
		getline(cin, currentLine);
		
		if (currentLine == "0 0" && populatedRows == cols)
		{
			sectors.clear();
			componentsCount = 0;
			sectorMark = 0;
			memset(visited, 0, sizeof(visited));
			calculateNumberOfConnectedComponents();
			results.push_back({ sectorMark ,sectors });
			memset(visited, 0, sizeof(visited));
			memset(image, 0, sizeof(image));
			populatedRows = 0;
			auto dimens = parseGridSize(currentLine);
			rows = dimens.first;
			cols = dimens.second;
			break;
		}
		auto whitespacesCount = count(currentLine.begin(), currentLine.end(), ' ');

		if(whitespacesCount == 1 && populatedRows == rows)
		{
			sectors.clear();
			componentsCount = 0;
			sectorMark = 0;
			calculateNumberOfConnectedComponents();
			results.push_back({ sectorMark ,sectors });
			memset(visited, false, sizeof(visited));
			memset(image, false, sizeof(image));
			populatedRows = 0;
			auto dimens = parseGridSize(currentLine);
			rows = dimens.first;
			cols = dimens.second;
		}
		else
		{
			remove_if(currentLine.begin(), currentLine.end(), [](const char c)
			{
				return c == 32;
			});
			for(int i = 0; i < cols; i++)
			{
				image[populatedRows][i] = currentLine[i] == '1' ? 1 : 0;
			}
			populatedRows++;
		}
	}
	results.erase(results.begin());
	for(auto result : results)
	{
		cout << result.first << endl;
		for (auto sectorArea : result.second)
			cout << sectorArea.first << ' ' << sectorArea.second << endl;
	}
	return 0;
}