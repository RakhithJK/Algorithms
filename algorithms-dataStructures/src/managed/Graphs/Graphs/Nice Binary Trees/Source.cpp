#define _CRT_SECURE_NO_WARNINGS
#define maxLength 10005

#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

char tree[maxLength];
int  currentPosition = -1;
int  maxDepth = 0;

void constructTree(const int currentDepth = 0)
{	
	currentPosition++;
	maxDepth = max(currentDepth, maxDepth);

	if (currentPosition >= 10000 || tree[currentPosition] == 'l')
		return;
	
	constructTree(currentDepth + 1);
	constructTree(currentDepth + 1);
}

int main()
{
	int tests;
	scanf("%d", &tests);

	while(tests--)
	{
		scanf("%s", &tree);
		currentPosition = -1;
		maxDepth        = 0;
		constructTree();
		printf("%d\n", maxDepth);
	}

	return 0;
}