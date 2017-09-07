#define _CRT_SECURE_NO_WARNINGS
#define maxNumbersCount 10001
#define sequences 2

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int		firstElementsCount, secondElementsCount;

int		sequenceNumbers		[sequences][maxNumbersCount];
int		maxSumAfter			[sequences][maxNumbersCount];

bool	isIntersectionIndex	[sequences][maxNumbersCount];
int		leadingTo			[sequences][maxNumbersCount];
 

enum sequence
{
	first = 0,
	second = 1
};

inline sequence getOpposite(sequence current)
{
	return (current == first) ? second : first;
}

int computeMaxSumAfter(int index, sequence seq) 
{
	if (seq == first && index > firstElementsCount)
		return 0;
	if (seq == second && index > secondElementsCount)
		return 0;

	if (maxSumAfter[seq][index] != -1)
		return maxSumAfter[seq][index];

	if (isIntersectionIndex[seq][index])
	{
		return maxSumAfter[seq][index] = max(
			sequenceNumbers[seq][index] + computeMaxSumAfter(index + 1, seq),
			sequenceNumbers[seq][index] + computeMaxSumAfter(leadingTo[seq][index], getOpposite(seq))
		);
	}

	return maxSumAfter[seq][index] = sequenceNumbers[seq][index] + computeMaxSumAfter(index + 1, seq);
}

void findIntersections()
{
	memset(isIntersectionIndex, false, sizeof isIntersectionIndex);
	
	unordered_map<int, int> firstSeq;
	unordered_map<int, int> secondSeq;

	for (auto i = 0; i <= firstElementsCount; i++) 
		firstSeq[sequenceNumbers[first][i]]   = i;
	
	for (auto i = 0; i <= secondElementsCount; i++) 
		secondSeq[sequenceNumbers[second][i]] = i;

	for (auto i = 0; i <= firstElementsCount; i++)
	{
		if(secondSeq.find(sequenceNumbers[first][i]) != secondSeq.end())
		{
			isIntersectionIndex[first][i]   = true;
			leadingTo[first][i]			    = secondSeq[sequenceNumbers[first][i]] + 1;
		}
	}

	for (auto i = 0; i <= secondElementsCount; i++)
	{
		if (firstSeq.find(sequenceNumbers[second][i]) != firstSeq.end())
		{
			isIntersectionIndex[second][i]  = true;
			leadingTo[second][i]			= firstSeq[sequenceNumbers[second][i]] + 1;
		}
	}
}

int main()
{
	string		 firstLine, secondLine;
	stringstream firstLineStream, secondLineStream;
	int			 number;

	while (getline(cin, firstLine) && firstLine[0] != '0' && getline(cin, secondLine))
	{
		firstLineStream  = stringstream(firstLine);
		secondLineStream = stringstream(secondLine);

		firstElementsCount = 0;
		firstLineStream >> number;
		while(firstLineStream >> number)
		{
			sequenceNumbers[first][firstElementsCount] = number;
			firstElementsCount++;
		}
		firstElementsCount--;

		secondElementsCount = 0;
		secondLineStream >> number;
		while (secondLineStream >> number)
		{
			sequenceNumbers[second][secondElementsCount] = number;
			secondElementsCount++;
		}
		secondElementsCount--;

		findIntersections(); 

		memset(maxSumAfter, -1, sizeof maxSumAfter);
		auto solution = max(
			computeMaxSumAfter(0, first),
			computeMaxSumAfter(0, second)
		);

		printf("%d\n", solution);
	}
	return 0;
}