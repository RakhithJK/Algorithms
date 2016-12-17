#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int studentsCount;
	int unHappy = 0;
	cin >> studentsCount;

	vector<int> corrects;
	vector<int> actuals;

	for (int i = 0; i < studentsCount; i++)
	{
		int actual;
		cin >> actual;
		corrects.push_back(i + 1);
		actuals.push_back(actual);
	}

	for (int i = 0; i < studentsCount; i++)
	{
		int actual = actuals.at(i);
		int correct = corrects.at(i);

		if (actual < correct)
			unHappy++;
	}

	cout << studentsCount - unHappy << endl;
}