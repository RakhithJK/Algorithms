#include<iostream>
#include<map>
#include<queue>
#include<vector>
#include<array>
#include<functional>
using namespace std;

int						projectsN, rules;
map<int, vector<int>>	dependentOn;
array<int, 1000>		in_degree;
vector<int>				sortedProjects;

void topologicalSort()
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for(int project = 1; project <= projectsN; project++)
		if (!in_degree[project])
			pq.push(project);
		
	while (!pq.empty())
	{
		auto currentProject = pq.top();
		pq.pop();

		sortedProjects.push_back(currentProject);

		for (auto dependency : dependentOn[currentProject])
		{
			in_degree[dependency]--;
			if (!in_degree[dependency])
				pq.push(dependency);
		}
	}
}

int main()
{
	cin >> projectsN >> rules;
	fill(in_degree.begin(), in_degree.end(), 0);

	for(int r = 0; r < rules; r++)
	{
		int target, k, dependent;
		cin >> target >> k;

		for(int i = 0; i < k; i++)
		{
			cin >> dependent;
			dependentOn[dependent].push_back(target);
			in_degree[target]++;
		}
	}

	topologicalSort();
	for (int i = 0; i < sortedProjects.size() - 1; i++)
		cout << sortedProjects[i] << ' ';

	cout << sortedProjects[sortedProjects.size() - 1];
	return 0;
}