#include<iostream>
#include<numeric>
#include<vector>
#include<map>

using namespace std;

typedef long long bigint;
typedef unsigned int uint;

const long double phi = 1.6180339887498948482;
const int divisor = 1000000007;
uint m, n;

bigint fibonacci(uint n)
{
	return abs(round(pow(phi, n) / sqrt(5)));
}

bigint computeSum()
{
	bigint sum = 0;
	for (uint i = n; i <= m; i++)
	{
		sum += fibonacci(i);
	}
	if(sum < 0)
	{
		sum += divisor;
	}
	return sum % divisor;
}
int main ()
{
	int tests;
	cin >> tests;
	for(int t = 0; t < tests; t++)
	{
		cin >> n >> m;
		cout << computeSum() << endl;
	}
	return 0;
}