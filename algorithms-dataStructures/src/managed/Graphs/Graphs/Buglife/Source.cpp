#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

enum color
{
	white,
	red,
	black
};
static inline color  getOppositeColor(color& c) { return c == red ? black : red; }
struct experiment
{
	experiment(int numberOfBugs, vector<pair<int,int>>& interactions)
	{
		vector<int> empty;
		this->numberOfBugs = numberOfBugs;

		for (auto bug = 1; bug <= numberOfBugs; bug++)
		{
			graph.insert({ bug, empty });
			colors.insert({ bug, white });
		}

		for(auto &interaction : interactions)
		{
			graph[interaction.first].push_back(interaction.second);
			graph[interaction.second].push_back(interaction.first);
		}
	}

	bool anySuspicious()
	{
		for (auto bug = 1; bug <= numberOfBugs; bug++)
		{
			if(visited.find(bug) != visited.end())
				continue;

			queue<int> bugsToVisit;
			colors[bug] = black;
			bugsToVisit.push(bug);

			while (!bugsToVisit.empty())
			{
				auto currentBug   = bugsToVisit.front();
				auto adjacentBugs = graph[currentBug];
				bugsToVisit.pop();

				visited.insert(currentBug);

				for (auto adjacentBug : adjacentBugs)
				{
					if (colors[adjacentBug] == white)
						colors[adjacentBug] = getOppositeColor(colors[currentBug]);

					else if(colors[adjacentBug] == colors[currentBug])
						return true;		

					if (visited.find(adjacentBug) == visited.end())
						bugsToVisit.push(adjacentBug);
				}
			}
		}
		return false;
	}

	int numberOfBugs;
	set<int> visited;
	stack<int> cycle;
	map<int, vector<int>> graph;
	map<int, color> colors;
};

vector<pair<int, int>> tests;
map<int, bool> results;

int main()
{
	int testsCount;
	cin >> testsCount;
	map<bool, string> testMessages;
	testMessages.insert({ true, "Suspicious bugs found!" });
	testMessages.insert({ false, "No suspicious bugs found!" });

	for (auto i = 1; i <= testsCount; i++)
	{
		vector<pair<int, int>> interactions;
		int bugsCount, interactionsCount;
		cin >> bugsCount >> interactionsCount;

		for (auto j = 0; j < interactionsCount; j++)
		{
			int bug1, bug2;
			cin >> bug1 >> bug2;
			interactions.push_back({ bug1, bug2 });
		}
		experiment exp(bugsCount, interactions);
		results.insert({ i, exp.anySuspicious() });
	}

	for(auto result : results)
	{
		cout << "Scenario #" << result.first << ":" << endl;
		cout << testMessages.at(result.second).c_str() << endl;
	}

	system("pause");
}