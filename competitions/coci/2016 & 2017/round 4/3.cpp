#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>

using namespace std;

int calculateSumOfPoints(string& cards) {
	auto acesNumber = count(cards.begin(), cards.end(), 'A');
	auto kingsNumber = count(cards.begin(), cards.end(), 'K');
	auto ladiesNumber = count(cards.begin(), cards.end(), 'Q');
	auto boysNumber = count(cards.begin(), cards.end(), 'J');

	return acesNumber * 4 + kingsNumber * 3 + ladiesNumber * 2 + boysNumber;
}

int main() {
	int n;
	cin >> n;
	vector<int> points;

	for (int i = 0; i < n; i++)
	{
		string cards;
		cin >> cards;
		auto pointsOfCards = calculateSumOfPoints(cards);
		points.push_back(pointsOfCards);
	}

	auto finalSum = accumulate(points.begin(), points.end(), 0);

	cout << finalSum << endl;
}