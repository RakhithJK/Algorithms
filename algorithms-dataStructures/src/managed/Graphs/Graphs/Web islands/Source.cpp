#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<array>
#include<stack>
#include<set>
#include<unordered_set>
using namespace std;

#define maxPages 100005

vector<vector<int>> websitesGraph(maxPages);
vector<vector<int>> websitesTransposedGraph(maxPages);
vector<int> components(maxPages);

array<bool, maxPages> visited;
array<int, maxPages> discoveryTime, finishingTime, minimumComponentOfWebsite;
stack<int> sortedWebsites;

int websitesN, linksN, page, adjacentPage, currentTime = 1, currentComponentId = 0;

void topologicalSort(int currentWebsite)
{
	visited[currentWebsite] = true;
	discoveryTime[currentWebsite] = currentTime++;

	for (auto nextWebsite : websitesGraph[currentWebsite])
		if (!visited[nextWebsite])
			topologicalSort(nextWebsite);

	finishingTime[currentWebsite] = currentTime++;
	sortedWebsites.push(currentWebsite);
}

void dfs_transposed(int currentWebsite, int componentRoot)
{
	visited[currentWebsite] = true;
	components[componentRoot] = min(components[componentRoot],currentWebsite);
	minimumComponentOfWebsite[currentWebsite] = componentRoot;
	
	for (auto nextWebsite : websitesTransposedGraph[currentWebsite])
		if (!visited[nextWebsite] && finishingTime[componentRoot] > finishingTime[nextWebsite])
			dfs_transposed(nextWebsite, componentRoot);
}

void kosaraju()
{
	for (int nextWebsite = 0; nextWebsite < websitesN; nextWebsite++)
	{
		if (!visited[nextWebsite])
			topologicalSort(nextWebsite);
	}

	fill(visited.begin(), visited.end(), false);
	fill(components.begin(), components.end(), maxPages + 1);
	while(!sortedWebsites.empty())
	{
		int currentWebsite = sortedWebsites.top();
		sortedWebsites.pop();
		if(!visited[currentWebsite])
		{
			dfs_transposed(currentWebsite, currentWebsite);
			currentComponentId++;
		}
	}
}

int main()
{
	scanf("%d %d", &websitesN, &linksN);
	while(linksN)
	{
		scanf("%d %d", &page, &adjacentPage);
		websitesGraph[page].push_back(adjacentPage);
		websitesTransposedGraph[adjacentPage].push_back(page);
		linksN--;
	}
	kosaraju();

	for(int website = 0; website < websitesN; website++)
		printf("%d\n", components[minimumComponentOfWebsite[website]]);
	
	return 0;
}