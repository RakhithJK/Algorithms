#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<stack>
#include<cstdio>
using namespace std;

void printPostfix(string infixExpression)
{
	stack<char>		operatorsStack;
	string			allOperators = "+-/*^";
	auto			isOperator = [&](char character) {return allOperators.find(character) != string::npos; };
	for(auto character : infixExpression)
	{
		if (isalnum(character))	
			printf("%c", character);
		if (isOperator(character))
			operatorsStack.push(character);
		if (character == '(')
			operatorsStack.push(character);
		if(character == ')')
		{
			while(!operatorsStack.empty() && operatorsStack.top() != '(')
			{
				printf("%c", operatorsStack.top());
				operatorsStack.pop();
			}
			if(!operatorsStack.empty())
				operatorsStack.pop();
		}
	}
}

int main()
{
	char	expression[10000];
	int		tests;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%s", &expression);
		printPostfix(expression);
		printf("\n");
	}
	return 0;
}