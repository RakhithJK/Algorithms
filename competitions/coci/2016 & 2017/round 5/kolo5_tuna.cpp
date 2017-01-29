#include<iostream>
#include<numeric>
#include<vector>
#include <algorithm>

using namespace std;

int main()
{
	int n, x, sum = 0;

	cin >> n >> x;

	for (int i = 0; i < n; i++)
	{
		int p1, p2, p3;
		cin >> p1 >> p2;
		if (abs(p2 - p1) <= x)
			sum += max(p1, p2);
		else
		{
			cin >> p3;
			sum += p3;
		}
	}

	cout << sum << endl;
}