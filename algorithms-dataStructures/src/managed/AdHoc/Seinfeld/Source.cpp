#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stack>

using namespace std;

string		expression;
stack<char> expressionStack;

inline char next()
{
	auto character = expressionStack.top();
	expressionStack.pop();
	return character;
}

int computeMinBalanceOperations()
{
	auto operationsCount = 0;

	for(auto brace : expression)
	{
		if (brace == '{')
			expressionStack.push(brace);
		else if (!expressionStack.empty() && expressionStack.top() == '{')
			expressionStack.pop();
		else
			expressionStack.push(brace);
	}

	while(!expressionStack.empty())
	{
		if(expressionStack.size() % 2 == 0)
		{
			auto left = next();
			auto right = next();

			if (left != right)
				operationsCount += 2;
			else
				operationsCount += 1;
		}
		else
		{
			next();
			operationsCount++;
		}
	}
	return operationsCount;
}

int main()
{
	auto currentTest = 0;
	while(cin >> expression && expression[0] != '-')
	{
		currentTest++;
		cout << currentTest << ". " << computeMinBalanceOperations() << endl;
	}
	return 0;
}