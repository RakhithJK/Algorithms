#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<string>
#include<algorithm>

const int infinity = 9999999;

using namespace std;

int numberOfRoads;
int lhs, rhs, weight;
int sourcePosition;
int numberOfQueries;
int destination;
int maxNode;

int graph[501][501];

void floyd_warshall()
{
	for (int k = 0; k <= maxNode + 1; k++)
		for (int i = 0; i <= maxNode + 1; i++)
			for (int j = 0; j <= maxNode + 1; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main()
{
	vector<string> results;
	vector<int> destinations;

	scanf("%d", &numberOfRoads);

	for (int i = 0; i <= 500; i++)
	{
		for (int j = 0; j <= 500; j++)
		{
			graph[i][j] = infinity;
		}
	}

	for (int r = 0; r < numberOfRoads; r++)
	{
		scanf("%d %d %d", &lhs, &rhs, &weight);
		graph[lhs][rhs] = weight;
		graph[rhs][lhs] = weight;

		if (lhs >= maxNode)
			maxNode = lhs;
		if (rhs >= maxNode)
			maxNode = rhs;
	}
	for (int i = 0; i <= maxNode; i++)
		graph[i][i] = 0;

	floyd_warshall();

	scanf("%d", &sourcePosition);
	scanf("%d", &numberOfQueries);
	for (int q = 0; q < numberOfQueries; q++)
	{
		scanf("%d", &destination);
		destinations.push_back(destination);
	}


	for (auto destination : destinations)
	{
		if (graph[sourcePosition][destination] == infinity)
			results.push_back("NO PATH");
		else
			results.push_back(to_string(graph[sourcePosition][destination]));
	}

	for (auto result : results)
		printf("%s\n", result.c_str());

	return 0;
}