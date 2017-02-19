#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include <queue>
#include <map>
#include<cstring>
using namespace std;

struct coords_hash
{
	size_t operator () (pair<int, int> const& p) const
	{
		return (hash<int>()(p.first) + hash<int>()(p.second));
	}
};
typedef pair<int, int> coords;

const int									maxDimension = 8;
int board[maxDimension][maxDimension];
queue<coords> unplacedPositions;


bool isInMap(int i, int j) {
	return (i >= 0 && i < maxDimension && j >= 0 && j < maxDimension);
}


bool canPlaceNumber(int number, int numberRow, int numberCol)
{
	unordered_set<int> rowElements;
	unordered_set<int> colElements;
	int boxRepeatingElements[] = { 0,0,0,0,0,0,0,0,0,0 };

	for (int row = 0; row < maxDimension; row++)
	{
		if (row != numberRow)
			rowElements.insert(board[row][numberCol]);
	}

	if (rowElements.find(number) != rowElements.end())
		return false;

	for (int col = 0; col < maxDimension; col++)
	{
		if (col != numberCol)
			rowElements.insert(board[numberRow][col]);
	}

	if (colElements.find(number) != colElements.end())
		return false;

	auto boxStartRow = numberRow - numberRow % 4;
	auto boxStartCol = numberCol - numberCol % 4;

	for (auto i = 0; i < 4; i++)
		for (auto j = 0; j < 4; j++)
			boxRepeatingElements[board[boxStartRow + i][boxStartCol + j]]++;

	return boxRepeatingElements[number] < 2;
}
bool didComputeAll()
{
	if (unplacedPositions.empty())
		return true;

	auto unplacedPosition = unplacedPositions.front();
	unplacedPositions.pop();

	for(int number = 1; number < 10; number++)
	{
		if (canPlaceNumber(number, unplacedPosition.first, unplacedPosition.second))
		{
			board[unplacedPosition.first][unplacedPosition.second] = number;
			if (didComputeAll())
				return true;
		}
	}
	board[unplacedPosition.first][unplacedPosition.second] = 0;
	unplacedPositions.push(unplacedPosition);
	return false;
}

bool isBoardValid()
{
	int rowRepeatingElements[] = { 0,0,0,0,0,0,0,0,0,0 };
	int colRepeatingElements[] = { 0,0,0,0,0,0,0,0,0,0 };

	for(int row = 0; row < maxDimension; row++)
	{
		for (auto col = 0; col < maxDimension; col++)
			rowRepeatingElements[board[row][col]]++;

		for (int i = 0; i < 10; i++)
		{
			if (rowRepeatingElements[i] > 1)
				return false;
		}

		memset(rowRepeatingElements, 0, sizeof(rowRepeatingElements));
	}

	for (int col = 0; col < maxDimension; col++)
	{
		for (auto row = 0; row < maxDimension; row++)
			colRepeatingElements[board[row][col]]++;

		for (int i = 0; i < 10; i++)
		{
			if (colRepeatingElements[i] > 1)
				return false;
		}
		memset(colRepeatingElements, 0, sizeof(colRepeatingElements));
	}

	int boxRepeatingElements[] = { 0,0,0,0,0,0,0,0,0,0 };
	memset(boxRepeatingElements, 0, sizeof(boxRepeatingElements));
	//left top
	for(int row = 0; row <4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			boxRepeatingElements[board[row][col]]++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (boxRepeatingElements[i] > 2)
			return false;
	}

	memset(boxRepeatingElements, 0, sizeof(boxRepeatingElements));
	//left bottom

	for (int row = 4; row <8; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			boxRepeatingElements[board[row][col]]++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (boxRepeatingElements[i] > 2)
			return false;
	}
	memset(boxRepeatingElements, 0, sizeof(boxRepeatingElements));
	// right top
	for (int row = 0; row <4; row++)
	{
		for (int col = 4; col < 8; col++)
		{
			boxRepeatingElements[board[row][col]]++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (boxRepeatingElements[i] > 2)
			return false;
	}
	memset(boxRepeatingElements, 0, sizeof(boxRepeatingElements));

	// right bottom

	for (int row = 4; row < 8; row++)
	{
		for (int col = 4; col < 8; col++)
		{
			boxRepeatingElements[board[row][col]]++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (boxRepeatingElements[i] > 2)
			return false;
	}

	return true;
}
bool isSolveable()
{
	for (auto row = 0; row < maxDimension; row++)
	{
		for (auto col = 0; col < maxDimension; col++)
		{
			if (board[row][col] == 0)
				unplacedPositions.push({ row, col });
		}
	}

	if (unplacedPositions.empty())
		return isBoardValid();

	auto didPlaceAll = didComputeAll();
	if (!didPlaceAll)
		return false;

	return isBoardValid();
}

int main()
{
	int testsNumber;
	cin >> testsNumber;

	for (int t = 0; t < testsNumber; t++)
	{
		for (int row = 0; row < maxDimension; row++)
		{
			for (int col = 0; col < maxDimension; col++)
				cin >> board[row][col];
		}

		if (isSolveable())
		{
			printf("Test case #%d: YES\n", t + 1);
			for (int row = 0; row < maxDimension; row++)
			{
				for (int col = 0; col < maxDimension; col++)
				{
					cout << board[row][col];
					if (col != maxDimension - 1)
						cout << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			printf("Test case #%d: NO\n", t + 1);
	}
	return 0;
}