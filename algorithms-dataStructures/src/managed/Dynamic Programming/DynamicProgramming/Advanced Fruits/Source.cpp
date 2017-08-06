#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

#define maxLength 105

enum step
{
	undefined = -1,
	lastCharactersSame = 1,
	excludeLastFromFirst = 2,
	exludeLastFromSecond = 3
};

string  firstFruit, secondFruit, shortestCommonSupersequence;

int		supersequenceLengthOf[maxLength][maxLength];
step	stepOf[maxLength][maxLength];

int constructMinimumSupersequence (int firstFruitLength = firstFruit.size(), int secondFruitLength = secondFruit.size())
{
	if (!firstFruitLength)  return secondFruitLength;
	if (!secondFruitLength) return firstFruitLength;

	if (supersequenceLengthOf[firstFruitLength][secondFruitLength] != -1)
		return supersequenceLengthOf[firstFruitLength][secondFruitLength];

	if (firstFruit[firstFruitLength - 1] == secondFruit[secondFruitLength - 1])
	{
		supersequenceLengthOf[firstFruitLength][secondFruitLength] = 1 + constructMinimumSupersequence(firstFruitLength - 1, secondFruitLength - 1);
		stepOf[firstFruitLength][secondFruitLength] = lastCharactersSame;
		return supersequenceLengthOf[firstFruitLength][secondFruitLength];
	}
	
	auto supersequence_when_excludedLastFromFirst = constructMinimumSupersequence(firstFruitLength - 1, secondFruitLength);
	auto supersequence_when_excludedLastFromSecond = constructMinimumSupersequence(firstFruitLength, secondFruitLength - 1);
	auto optimalSupersequence = min(supersequence_when_excludedLastFromFirst, supersequence_when_excludedLastFromSecond);

	if(optimalSupersequence == supersequence_when_excludedLastFromFirst)
		stepOf[firstFruitLength][secondFruitLength] = excludeLastFromFirst;
	else
		stepOf[firstFruitLength][secondFruitLength] = exludeLastFromSecond;

	return supersequenceLengthOf[firstFruitLength][secondFruitLength] = 1 + optimalSupersequence;
}

string reconstructRecursively(int leftLength = firstFruit.size(), int rightLength = secondFruit.size(), string aggregate = "")
{
	if(leftLength > 0 && rightLength > 0)
	{
		if(stepOf[leftLength][rightLength] == lastCharactersSame)
			return reconstructRecursively(leftLength - 1, rightLength - 1, aggregate + firstFruit[leftLength - 1]);

		if(stepOf[leftLength][rightLength] == exludeLastFromSecond)
			return reconstructRecursively(leftLength, rightLength - 1, aggregate + secondFruit[rightLength - 1]);

		return reconstructRecursively(leftLength - 1, rightLength, aggregate + firstFruit[leftLength - 1]);
	}

	if(leftLength > 0)
	
		return reconstructRecursively(leftLength - 1, rightLength - 1, aggregate + firstFruit[leftLength - 1]);
	
	if(rightLength > 0)	
		return reconstructRecursively(leftLength, rightLength - 1, aggregate + secondFruit[rightLength - 1]);
	
	return aggregate;
}

int main()
{
	while(cin >> firstFruit && cin >> secondFruit)
	{

		memset(supersequenceLengthOf, -1, sizeof supersequenceLengthOf);
		memset(stepOf, undefined, sizeof stepOf);

	    constructMinimumSupersequence();
		auto superseq = reconstructRecursively();
		reverse(superseq.begin(), superseq.end());
		cout << superseq << endl;
	}
	return 0;
}