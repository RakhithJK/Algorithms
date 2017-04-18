#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<cmath>
using namespace std;

typedef long long	bigint;
typedef				pair<bigint, bigint> robot;
const				bigint infinity = pow(10, 12);

#define products		first
#define improvementCost second 

vector<robot>	robots;
int				testsN, robotsN;
bigint			budget;

void binarySearch(bigint lo, bigint hi, bigint* optimum, function<bool(bigint)> canProduce)
{
	if (lo > hi)
		return;
	auto mid = (lo + hi) / 2;
	if (canProduce(mid))
	{
		*optimum = max(*optimum, mid);
		return binarySearch(mid + 1, hi, optimum, canProduce);
	}
	return binarySearch(lo, mid - 1, optimum, canProduce);
}

bigint calculate()
{
	const auto canProduce = [&](bigint productsCount) {
		bigint requiredPrice = 0;
		for (auto robot : robots)
		{
			auto remaining = productsCount - robot.products;
			requiredPrice += remaining * robot.improvementCost;
			if (requiredPrice > budget)
				return false;
		}
		return requiredPrice <= budget;
	};

	sort(robots.begin(), robots.end());
	auto optimum = new bigint(0);
	binarySearch(1, infinity, optimum, canProduce);
	return *optimum;
}

int main()
{
	scanf("%d", &testsN);
	for (int t = 0; t < testsN; t++)
	{
		scanf("%d %lld", &robotsN, &budget);
		for (int r = 1; r <= robotsN; r++)
		{
			bigint products, cost;
			scanf("%lld %lld", &products, &cost);
			robots.push_back({ products, cost});
		}
		printf("%lld\n", calculate());
		robots.clear();
	}
	return 0;
}