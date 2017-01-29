#include<iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> Xs(n);
	vector<int> Ys(n);

	int maxY = 0;

	for (auto i = 0; i < n; i++)
	{
		int pravX, pravY;
		cin >> pravX >> pravY;
	
		Xs[i] = pravX / 2;
		Ys[i] = pravY / 2;

		if (Ys[i] > maxY)
			maxY = Ys[i];
	}

	
	vector<int> m(maxY);
	unsigned long long sum = 0;
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < Ys[i]; j++)
		{
			if (Xs[i] > m[j])
			{
				sum += Xs[i] - m[j];
				m[j] = Xs[i];
			}
		}
	}

	cout << sum * 4 << endl;
}