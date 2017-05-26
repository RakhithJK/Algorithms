#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	long n, diff;
	scanf("%d %d", &n, &diff);
	vector<long> numbers(n);
	for (long i = 0; i < n; i++)
		scanf("%d", &numbers[i]);
	sort(numbers.begin(), numbers.end());
	
	long count = 0;
	for(auto number : numbers)
	{
		if (number + diff > numbers[n - 1])
			break;
		if (binary_search(numbers.begin(), numbers.end(), number + diff))
			count++;
	}
	printf("%d", count);
	return 0;
}