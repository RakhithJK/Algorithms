#include<iostream>

using namespace std;

int main()
{
	int k, d, o;
	cin >> k >> d >> o;

	bool pogodija = false;
	int broj = -1;
	for (int i = 1; i < k * d && !pogodija; i++)
	{
		if ((i * k) % d == o)
		{
			pogodija = true;
			broj = i;
		}
	}
	cout << broj << endl;
}