#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<set>

using namespace std;

int			graph[101][101];
int			maxNode;
int			maxTime;
int			destinationNode;
int			adjacenciesCount;
set<int>	mice;

const int	infinity = 9999999;

void floyd_warshall()
{
	for (int k = 1; k <= maxNode; k++)
		for (int i = 1; i <= maxNode; i++)
			for (int j = 1; j <= maxNode; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int calculateNumberOfSuccessfulMice()
{
	floyd_warshall();

	for (int i = 1; i <= maxNode; i++)
	{
		if (graph[destinationNode][i] <= maxTime)
			mice.insert(i);
		if (graph[i][destinationNode] <= maxTime)
			mice.insert(i);
	}
	return mice.size();
}


int main()
{
	scanf("%d", &maxNode);
	scanf("%d", &destinationNode);
	scanf("%d", &maxTime);
	scanf("%d", &adjacenciesCount);

	for (int i = 1; i < 101; i++)
		for (int j = 1; j < 101; j++)
			if (i == j)
				graph[i][j] = 0;
			else
				graph[i][j] = infinity;

	for (int a = 0; a < adjacenciesCount; a++)
	{
		int lhs, rhs, weight;
		scanf("%d %d %d", &lhs, &rhs, &weight);

		graph[lhs][rhs] = weight;
	}

	printf("%d", calculateNumberOfSuccessfulMice());
	return 0;
}