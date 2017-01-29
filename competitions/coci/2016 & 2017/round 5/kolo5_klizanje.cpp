#include<iostream>
using namespace std;
int main()
{
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	int ukupno = n + m;
	int dosli = a + b;
	if (dosli < ukupno)
		cout << dosli;
	else
		cout << ukupno;
}