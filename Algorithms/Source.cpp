#include <iostream>
#include <vector>
#include "SelectionSort.h"

using namespace std;

int main()
{
	int n, result = 0;
	scanf_s("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int iterationResult = 1;
		for (int j = 0; j < i; j++)
		{
			iterationResult *= i;
		}
		result += iterationResult;
	}

	printf("%d", result);

	std::system("pause");
}





