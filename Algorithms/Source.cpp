#include <iostream>
#include <vector>
#include "QuickSort.h"

using namespace std;

int main()
{
	QuickSort * algorithm = new QuickSort();
	vector<int> items;
	for (int i = 0; i < 3; i++)
	{
		int temp;
		cin >> temp;
		items.push_back(temp);
	}

	algorithm->Sort(items, 0, items.size() - 1);

	for (auto item : items)
	{
		cout << item << endl;
	}


	std::system("pause");
}





