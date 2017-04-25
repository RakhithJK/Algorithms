#define _CRT_SECURE_NO_WARNINGS
#include<cstdio> 
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include<functional>
#include <deque>
using namespace std;

int pagesN, scribersN;
typedef unsigned long long bigint;

bigint	findMaxAmountOfWorkPerScriber	();
void    binarySearch					(bigint lo, bigint hi, bigint* optimum, function<bool(bigint)> canDistribute);
void	partition						(bigint maxWork);
void	partitionRecursively			(int currentPartition, int currentPageIndex, int remainingScribers, bigint maxWork);

vector<bigint>			pages;
vector<deque<bigint>>	partitions;
vector<bool>			processedBooks;
bigint					pagesSum = 0;

bigint findMaxAmountOfWorkPerScriber()
{
	auto canDistribute = [&](bigint maxScriberWork)
	{
		bigint	currentPagesToScribe = 0;
		auto	requiredScribers = 1;
		for (auto bookPages : pages)
		{
			if (bookPages > maxScriberWork)
				return false;
			if (currentPagesToScribe + bookPages > maxScriberWork) {
				requiredScribers++;
				currentPagesToScribe = 0;
			}
			currentPagesToScribe += bookPages;
		}
		return requiredScribers <= scribersN;
	};
	bigint lo = 1;
	bigint hi = pagesSum;
	bigint optimum = pagesSum;
	binarySearch(lo, hi, &optimum, canDistribute);
	return optimum;
}
void binarySearch(bigint lo, bigint hi, bigint* optimum, function<bool(bigint)> canDistribute)
{
	if (lo > hi)
		return;
	auto mid = (lo + hi) >> 1;
	if (canDistribute(mid))
	{
		*optimum = min(*optimum, mid);
		return binarySearch(lo, mid - 1, optimum, canDistribute);
	}
	return binarySearch(mid + 1, hi, optimum, canDistribute);
}
void partition(bigint maxWork)
{
	partitions = vector<deque<bigint>>(scribersN);
	partitionRecursively(0, pagesN - 1, scribersN, maxWork);
	reverse(partitions.begin(), partitions.end());
}
void partitionRecursively(int currentPartition, int currentPageIndex, int remainingScribers, bigint maxWork)
{
	auto   i		    = currentPageIndex;
	bigint currentWork	= 0;
	while(i >= 0)
	{
		if (currentWork + pages[i] > maxWork || i + 1 == remainingScribers - 1)
		{
			if (processedBooks[i])
				continue;
			processedBooks[i] = true;
			return partitionRecursively(currentPartition + 1, i, remainingScribers - 1, maxWork);
		}
		else
		{
			processedBooks[i] = true;
			currentWork		 += pages[i];
			partitions[currentPartition].push_front(pages[i]);
		}
		i--;
	}
}

int main() {
	int tests;
	scanf("%d", &tests);
	while(tests)
	{
		scanf("%d %d", &pagesN, &scribersN);
		pages			= vector<bigint>(pagesN);
		processedBooks	= vector<bool>(pagesN, false);
		pagesSum		= 0;
		for (auto i = 0; i < pagesN; i++)
		{
			scanf("%lld", &pages[i]);
			pagesSum += pages[i];
		}
		partition(findMaxAmountOfWorkPerScriber());
		for(auto p = 0; p < partitions.size(); p++)
		{
			for (auto i = 0; i < partitions[p].size(); i++)
			{
				if (i == partitions[p].size() - 1 && p != partitions.size() - 1)
					printf("%lld / ", partitions[p][i]);
				else if(i != partitions[p].size() - 1)
					printf("%lld ", partitions[p][i]);
				else
					printf("%lld", partitions[p][i]);
			}
		}
		printf("\n");
		tests--;
	}
	return 0; 
}