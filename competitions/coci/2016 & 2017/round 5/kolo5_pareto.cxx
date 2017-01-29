#include<iostream>
#include<vector>
#include <algorithm>
#include <numeric>

using namespace std;
int main()
{
	int brojKlijenata;
	cin >> brojKlijenata;
	vector<int> racuni;
	long long vrijednostBanke = 0;

	for (auto i = 0; i < brojKlijenata; i++)
	{
		int parica;
		cin >> parica;
		vrijednostBanke += parica;
		racuni.push_back(parica);
	}

	sort(racuni.begin(), racuni.end(), [](int lhs, int rhs) { return lhs > rhs; });

	long double sumaDotad = 0;
	long double najboljaRazlika = 0;
	long double A = 0;
	long double B = 0;
	for (auto i = 0; i < racuni.size(); i++)
	{
		sumaDotad += racuni.at(i);
		
		long double A1 = sumaDotad / vrijednostBanke;
		long double B1 = (long double)(i + 1) / brojKlijenata;

		if(abs(A1 - B1) > najboljaRazlika)
		{
			
			najboljaRazlika = abs(A1 - B1);
			A = A1;
			B = B1;
		}
	}
	cout << B * 100 << endl;
	cout << A * 100 << endl;
}