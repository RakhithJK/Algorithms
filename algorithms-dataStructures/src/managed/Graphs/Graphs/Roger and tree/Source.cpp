#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#define maxVerticesN pow(10,5) + 1

int					root, verticesN, queriesN;
vector<vector<int>> subtreeOf(maxVerticesN, vector<int>());
vector<int>			subtreeDepthOf(maxVerticesN, 0);
vector<int>			diameterOf(maxVerticesN, 0);

int computeSubtreeDepth(const int current, const int parent)
{
	for (auto child : subtreeOf[current])
	{
		if (child == parent)
			continue;
		subtreeDepthOf[current] = max(subtreeDepthOf[current], computeSubtreeDepth(child, current));
	}

	subtreeDepthOf[current] += 1;
	return subtreeDepthOf[current];
}

int getDiameterOfSubtree(const int root, const int parent)
{
	vector<int> childrenSubtreeDepths;

	auto	firstMaxDepth		  = 0, 
			secondMaxDepth		  = 0, 
			maxDiameterOfAnyChild = 0;

	for (auto child : subtreeOf[root])
	{
		if (child == parent)
			continue;
		childrenSubtreeDepths.push_back(subtreeDepthOf[child]);

		maxDiameterOfAnyChild = max(
			maxDiameterOfAnyChild, 
			getDiameterOfSubtree(child, root)
		);
	}
	sort(childrenSubtreeDepths.begin(), childrenSubtreeDepths.end(), greater<int>());

	if (childrenSubtreeDepths.size() >= 2)
		firstMaxDepth = childrenSubtreeDepths[0], secondMaxDepth = childrenSubtreeDepths[1];
	else if (childrenSubtreeDepths.size())
		firstMaxDepth = childrenSubtreeDepths[0];

	return diameterOf[root] = max(maxDiameterOfAnyChild, firstMaxDepth + secondMaxDepth + 1);
}

int main()
{
	int source, destination;
	scanf("%d", &verticesN);
	for (auto i = 0; i < verticesN - 1; i++)
	{
		scanf("%d %d", &source, &destination);
		subtreeOf[source].push_back(destination);
		subtreeOf[destination].push_back(source);
	}
	scanf("%d", &root);
	scanf("%d", &queriesN);
	computeSubtreeDepth(root, -1);
	getDiameterOfSubtree(root, -1);
	while (queriesN--)
	{
		scanf("%d", &source);
		printf("%d\n", diameterOf[source] - 1);
	}
	return 0;
}