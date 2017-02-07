#define _CRT_SECURE_NO_WARNINGS

#include<set>
#include<map>
#include<queue>

using namespace std;

namespace colors
{
	enum color
	{
		white,
		gray,
		black
	};
}

int jobsCount, jobRelations;
vector<vector<int>> jobsToDoAfter;
vector<int>			in_degree;
vector<int>			schedule;

// Kahn's indegree based topological sort
void topologicalSort()
{
	set<int> jobsToProcess;
	for (int job = 1; job <= jobsCount; job++)
		if (!in_degree[job])
			jobsToProcess.insert(job);

	while(!jobsToProcess.empty())
	{
		auto job = *jobsToProcess.begin();
		jobsToProcess.erase(jobsToProcess.begin());

		schedule.push_back(job);

		for(auto nextJobToProcess : jobsToDoAfter[job])
		{
			in_degree[nextJobToProcess]--;
			if (!in_degree[nextJobToProcess])
				jobsToProcess.insert(nextJobToProcess);
		}
	}
}

int main()
{
	scanf("%d %d", &jobsCount, &jobRelations);
	jobsToDoAfter.resize(jobsCount + 1);
	in_degree.resize(jobsCount + 1);
	fill(in_degree.begin(), in_degree.end(), 0);

	int jobBefore, job;
	for (int i = 0; i < jobRelations; i++)
	{
		scanf("%d %d", &jobBefore, &job);
		jobsToDoAfter[jobBefore].push_back(job);
		in_degree[job]++;
	}
	topologicalSort();
	if (schedule.size() == jobsCount)
	{
		for (int i = 0 ; i < schedule.size();i++)
		{
			if (i < schedule.size() - 1)
				printf("%d ", schedule[i]);
			else
				printf("%d", schedule[i]);
		}
	}
	else
		printf("Sandro fails.");
	return 0;	
}