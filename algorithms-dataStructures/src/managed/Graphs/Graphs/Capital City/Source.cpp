#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<stack>
#include<array>

using namespace std;

#define citiesNMax 100000 + 10

int							citiesN, 
							connectionsN, 
							currentTime			= 1, 
							currentComponent	= 1;

array<int, citiesNMax>		discoveryTime,
							finishingTime,
							componentOfCity,
							outDegreeOfComponent;

array<bool, citiesNMax>		visited;

vector<vector<int>>			graph(citiesNMax);
vector<vector<int>>			transposedGraph(citiesNMax);

stack<int>					topologicallySorted;
vector<int>					candidates;

void topologicalSort(int currentCity)
{
	visited[currentCity]		= true;
	discoveryTime[currentCity]	= currentTime++;

	for (auto adjacent : graph[currentCity])
		if (!visited[adjacent])
			topologicalSort(adjacent);

	finishingTime[currentCity]	= currentTime++;
	topologicallySorted.push(currentCity);
}

void dfs_transposed(int currentCity, int componentRoot)
{
	visited[currentCity]		 = true;
	componentOfCity[currentCity] = currentComponent;

	for (auto adjacent : transposedGraph[currentCity])
	{
		if (!visited[adjacent] && finishingTime[componentRoot] >finishingTime[adjacent])
			dfs_transposed(adjacent, componentRoot);
	}
}

void kosaraju()
{
	for (int city = 1; city <= citiesN; city++)
		if (!visited[city])
			topologicalSort(city);

	fill(visited.begin(), visited.end(), false);

	while (!topologicallySorted.empty())
	{
		auto candidate = topologicallySorted.top();
		topologicallySorted.pop();

		if (!visited[candidate]) {
			dfs_transposed(candidate, candidate);
			currentComponent++;
		}
	}
}

void processOutDegress()
{
	for (int city = 1; city <= citiesN; city++)
		for (auto adjacent : graph[city])
			if (componentOfCity[city] != componentOfCity[adjacent])
				outDegreeOfComponent[componentOfCity[city]]++;

	auto candidateComponentsCount = 0;

	for (int component = 1; component < currentComponent; component++)
		if (outDegreeOfComponent[component] == 0)
			candidateComponentsCount++;

	if (candidateComponentsCount > 1)
		return;

	for (int city = 1; city <= citiesN; city++)
		if (outDegreeOfComponent[componentOfCity[city]] == 0)
			candidates.push_back(city);
}

int main()
{
	scanf("%d %d", &citiesN, &connectionsN);

	while (connectionsN--)
	{
		int city, adjacent;
		scanf("%d %d", &city, &adjacent);
		graph[city].push_back(adjacent);
		transposedGraph[adjacent].push_back(city);
	}

	kosaraju();
	processOutDegress();

	printf("%d\n", candidates.size());

	for (int i = 0; i < candidates.size(); i++)
	{
		if (i != 0) printf(" ");
		printf("%d", candidates[i]);
	}
	return 0;
}