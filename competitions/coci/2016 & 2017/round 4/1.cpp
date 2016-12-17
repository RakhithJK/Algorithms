#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int jobStart;
	int jobEnd;
	vector<int> solutions;
	int vacation1;
	int vacation2;

	cin >> jobStart >> jobEnd >> vacation1 >> vacation2;
		
	if (vacation1 < jobStart)
		solutions.push_back(vacation1);
	if (vacation2 > jobEnd)
		solutions.push_back(vacation2);

	auto solution = min(solutions.begin(), solutions.end());

	cout << *solution << endl;
}