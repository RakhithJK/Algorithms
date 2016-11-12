#include<iostream>
using namespace std;

int main()
{
	int numberOfEyes;
	int numberOfPeople;
	int numberOfAnimalEyes;

	cin >> numberOfEyes >> numberOfPeople >> numberOfAnimalEyes;

	int restOfEyes = (numberOfEyes - (numberOfPeople * 2) - numberOfAnimalEyes);
	int unseenAnimals = restOfEyes / 2;
	cout <<  unseenAnimals << endl;

	return 0;
}