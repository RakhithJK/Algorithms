#define _CRT_SECURE_NO_WARNINGS

#include<vector>
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

struct nodeState
{
	colors::color color;
	int			  discoveringTime;
	int			  finishingTime;
};

int studentsN, successStudentsN;
vector<vector<int>> superiors;
vector<bool>		visitedStudents;
vector<int>			bossOfStudent;
vector<nodeState>	states;
queue<int>		    hierarchy;

int currentTime = 0;

void visit(int student)
{
	currentTime++;
	states[student].discoveringTime = currentTime;
	states[student].color = colors::gray;

	for (int boss : superiors[student])
	{
		if (states[boss].color == colors::white)
			visit(boss);
	}

	states[student].color = colors::black;
	currentTime++;
	states[student].finishingTime = currentTime;
	hierarchy.push(student);
}

void topologicalSort()
{
	for (auto student = 1;  student <= studentsN; student++)
	{
		if (states[student].color == colors::white)
		{
			visit(student);
		}
	}
}

int main()
{
	nodeState empty;
	empty.color = colors::white;
	empty.discoveringTime = 0;
	empty.finishingTime = 0;

	scanf("%d%d", &studentsN, &successStudentsN);
	superiors.resize(studentsN + 1);
	bossOfStudent.resize(studentsN + 1);
	visitedStudents.resize(studentsN + 1);
	states.resize(studentsN + 1);
	fill(visitedStudents.begin(), visitedStudents.end(), false);
	fill(states.begin(), states.end(), empty);
	fill(bossOfStudent.begin(), bossOfStudent.end(), 0);

	int studentWishes = 0;
	int superior = 0;
	for (auto successful = 1; successful <= successStudentsN; successful++)
	{
		scanf("%d", &studentWishes);

		for (int j = 0; j < studentWishes; j++)
		{
			scanf("%d", &superior);
			superiors[superior].push_back(successful);
		}
	}
	topologicalSort();
	int previousBoss = 0;
	while (!hierarchy.empty()) {
		int student = hierarchy.front();
		hierarchy.pop();
		bossOfStudent[student] = previousBoss;
		previousBoss = student;
	}
	for (int i = 1; i <= studentsN; i++) {
		printf("%d\n", bossOfStudent[i]);
	}
	return 0;
}