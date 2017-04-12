#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define infinity			1.0
#define maxIntersectionsN	101

double	graph[maxIntersectionsN][maxIntersectionsN];
int		intersectionsN, streetsN;

inline double computeOptimalPath()
{
	for (int k = 1; k <= intersectionsN; k++)
		for (int i = 1; i <= intersectionsN; i++)
			for (int j = 1; j <= intersectionsN; j++)
				graph[i][j] = max(graph[i][j], graph[i][k] * graph[k][j]);

	return graph[1][intersectionsN] * 100.0;
}
int main()
{
	scanf("%d", &intersectionsN);
	while (intersectionsN)
	{
		scanf("%d", &streetsN);
		memset(graph, 1, sizeof(graph));
		for (int i = 0; i < streetsN; i++)
		{
			int lhs, rhs;
			double probability;
			scanf("%d %d %lf", &lhs, &rhs, &probability);
			graph[lhs][rhs] = probability / 100.0;
			graph[rhs][lhs] = probability / 100.0;
		}
		printf("%.6lf percent\n", computeOptimalPath());
		scanf("%d", &intersectionsN);
	}
	return 0;
}