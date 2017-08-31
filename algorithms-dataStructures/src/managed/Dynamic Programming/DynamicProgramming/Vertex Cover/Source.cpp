#define _CRT_SECURE_NO_WARNINGS

#define maxSize 100001
#define isTakenAsRoot 2

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int					verticesCount;
bool				visitedInCurrentPath[maxSize];
int					minimumCoverSetRootedAt[maxSize][isTakenAsRoot];
vector<vector<int>> subtreeOf;

int compute_minimum_cover_set_size(int root, bool shouldIncludeInCoverSet)
{
	if (minimumCoverSetRootedAt[root][shouldIncludeInCoverSet] != -1)
		return minimumCoverSetRootedAt[root][shouldIncludeInCoverSet];
	
	visitedInCurrentPath[root] = true;

	if(shouldIncludeInCoverSet)
	{
		auto coverSetSize_includingRoot = shouldIncludeInCoverSet ? 1 : 0;

		for (auto child : subtreeOf[root])
		{
			if (visitedInCurrentPath[child])
				continue;

			visitedInCurrentPath[child] = true;

			coverSetSize_includingRoot += min(
				compute_minimum_cover_set_size(child, false), 
				compute_minimum_cover_set_size(child, true)
			);

			visitedInCurrentPath[child] = false;
		}
		return minimumCoverSetRootedAt[root][shouldIncludeInCoverSet] = coverSetSize_includingRoot;
	}
	
	auto coverSetSize_excludingRoot = 0;
	for (auto child : subtreeOf[root])
	{
		if (visitedInCurrentPath[child])
			continue;

		visitedInCurrentPath[child] = true;

		coverSetSize_excludingRoot += compute_minimum_cover_set_size(child, true);

		visitedInCurrentPath[child] = false;
	}

	visitedInCurrentPath[root] = false;
	return minimumCoverSetRootedAt[root][shouldIncludeInCoverSet] = coverSetSize_excludingRoot;
}

int main()
{
	int parent, child;
	scanf("%d", &verticesCount);
	memset(minimumCoverSetRootedAt, -1, sizeof minimumCoverSetRootedAt);
	memset(visitedInCurrentPath, false, sizeof visitedInCurrentPath);

	subtreeOf = vector<vector<int>>(verticesCount + 1, vector<int>());
	for(auto i = 0; i < verticesCount -1; i++)
	{
		scanf("%d %d", &parent, &child);
		subtreeOf[parent].push_back(child);
		subtreeOf[child].push_back(parent);
	}

	auto solution = min(
		compute_minimum_cover_set_size(1, true),
		compute_minimum_cover_set_size(1, false)
	);
	printf("%d\n", solution);
	return 0;
}