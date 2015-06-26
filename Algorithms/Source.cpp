#include <iostream>
#include <vector>
#include "SelectionSort.h"

using namespace std;

int main()
{
	SelectionSort * algorithm = new SelectionSort();
	vector<int> items;
	for (int i = 0; i < 3; i++)
	{
		int temp;
		cin >> temp;
		items.push_back(temp);
	}

	algorithm->Sort(items);

	for (auto item : items)
	{
		cout << item << endl;
	}


	std::system("pause");
}





