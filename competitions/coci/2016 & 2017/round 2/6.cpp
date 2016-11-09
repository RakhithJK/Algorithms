#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector< vector<int> > matrix(n);

	if (n == 1)
	{
		cout << 1 << endl;
		return 0;
	}

	if (n % 2 > 0)
	{
		int currentElement = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << currentElement << " ";
				currentElement++;
			}
			cout << endl;
		}
		return 0;
	}

	// average element is one at n - 2 index at row and column
	int averageElementIndex = n - 2;

	// construct first row

	int sumUntilLastElement = 0;
	for (int i = 0; i <= averageElementIndex; i++)
	{
		matrix[0].push_back(i + 1);
		sumUntilLastElement += i + 1;
	}
	int lastElementInFirstRow = n * (n - 1) - sumUntilLastElement;
	matrix[0].push_back(lastElementInFirstRow);

	// construct until last row
	for (int i = 1; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i].push_back(matrix[i - 1][j] + lastElementInFirstRow);
		}
	}

	// construct last row

	sumUntilLastElement = 0;

	for (int i = 0; i <= averageElementIndex; i++)
	{
		sumUntilLastElement += matrix[i][0];
	}

	int firstElementInLastColumn = matrix[n - 2][0] * n - sumUntilLastElement;
	int bottomColumnsDiff        = firstElementInLastColumn - matrix[n - 2][0];
	matrix[n - 1].push_back(firstElementInLastColumn);

	for (int i = 1; i < n; i++)
	{
		matrix[n - 1].push_back(matrix[n - 2][i] + bottomColumnsDiff);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}