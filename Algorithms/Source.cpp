#include <iostream>
#include <vector>
#include "MergeSort.h"


using namespace std;


int main()
{
	MergeSort * algorithm = new MergeSort();
	vector<int> items;



	for (int i = 0; i < 3; i++)
	{
		int temp = 0;
		cin >> temp;
		items.push_back(temp);
	}

	algorithm->SortVector(items, 0, items.size() - 1);

	for (const int ELEMENT : items)
	{
		cout << ELEMENT << endl;
	}


	std::system("pause");
}





