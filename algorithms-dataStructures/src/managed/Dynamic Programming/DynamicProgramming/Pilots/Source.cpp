#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> salary;
#define asPilot first
#define asAssistant second
#define infinity INT_MAX / 2

vector<salary> salaries;

int pilotsN;
int costUptoCurrentPilotWithAssistants[10010][10010];

int computeCostUptoPilotRecursively(int currentPilotIx, int remainingAssistants)
{
	if (remainingAssistants < 0)
		return infinity;
	if (currentPilotIx == 0)
		return salaries[0].asAssistant;

	if (costUptoCurrentPilotWithAssistants[currentPilotIx][remainingAssistants] != 0)
		return costUptoCurrentPilotWithAssistants[currentPilotIx][remainingAssistants];

	costUptoCurrentPilotWithAssistants[currentPilotIx][remainingAssistants] = min(
		computeCostUptoPilotRecursively(currentPilotIx - 1, remainingAssistants + 1) + salaries[currentPilotIx].asPilot,
		computeCostUptoPilotRecursively(currentPilotIx - 1, remainingAssistants - 1) + salaries[currentPilotIx].asAssistant
	);

	return costUptoCurrentPilotWithAssistants[currentPilotIx][remainingAssistants];
}

int main() {
	scanf("%d", &pilotsN);
	salaries = vector<salary>(pilotsN);
	for (int i = 0; i < pilotsN; i++)
		scanf("%d %d", &salaries[i].first, &salaries[i].second);
	printf("%d", computeCostUptoPilotRecursively(pilotsN - 1, 0));
	return 0;
}