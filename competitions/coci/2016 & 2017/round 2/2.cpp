#include<iostream>
using namespace std;

int main()
{
	int restOfPoints, segment, multiplier;
	cin >> restOfPoints >> segment >> multiplier;

	int throwPoints = segment * multiplier;
	int diff = restOfPoints - throwPoints;


	if (diff > 0)
		cout << "Dobro" << endl; 
	else if (diff <= restOfPoints && multiplier != 2)
		cout << "Lose" << endl;
	else if (diff == 0 && multiplier == 2)
		cout << "Odlicno" << endl;

	return 0;
}