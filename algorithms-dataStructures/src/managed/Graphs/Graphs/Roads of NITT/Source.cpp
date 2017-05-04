#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<cstdio>
#include<stack>
#include<queue>

using namespace std;
typedef unsigned int uint;

struct disjoint_set {
	disjoint_set() {  }
	disjoint_set(int elementsN)
	{
		subsetElementsCountOf = vector<int>(elementsN + 10, 1);
		rootOf = vector<int>(elementsN + 10);
		for (int element = 1; element < rootOf.size(); element++)
			rootOf[element] = element;
	}
	vector<int> subsetElementsCountOf;
	vector<int> rootOf;

	int findRoot(int element) {
		auto currentElement = element;
		while (rootOf[currentElement] != currentElement) {
			currentElement = rootOf[currentElement];
		}
		auto root = currentElement;
		while (rootOf[currentElement] != currentElement) {
			rootOf[currentElement] = root;
			currentElement = rootOf[currentElement];
		}
		return root;
	}
	void merge(int left, int right) {
		auto leftRoot  = findRoot(left);
		auto rightRoot = findRoot(right);
		if (subsetElementsCountOf[leftRoot] > subsetElementsCountOf[rightRoot]) {
			rootOf[leftRoot] = rightRoot;
			subsetElementsCountOf[rightRoot] += subsetElementsCountOf[leftRoot];
		}
		else
		{
			rootOf[rightRoot] = leftRoot;
			subsetElementsCountOf[leftRoot] += subsetElementsCountOf[rightRoot];
		}
	}
};

enum commandType { query = 0, removeRoad = 1 };
struct command {
	command() {}
	command(commandType type, uint road) {
		this->road = road;
		this->type = type;
	}
	commandType type;
	uint		road;
};
struct road {
	road() {
		this->source = -1;
		this->destination = -1;
	}
	road(int source, int destination, bool willBeRemoved)
	{
		this->source = source;
		this->destination = destination;
		this->willBeRemoved = willBeRemoved;
	}
	bool isSet() {
		return this->source > 0;
	}
	int source;
	int destination;
	bool willBeRemoved;
};

vector<road>	roads;
stack<command>	commands;
disjoint_set	dsu;
int				hotelsN, roadsN, queriesN;

uint computeNumberOfDisconnectedPairs() {
	uint maxNumberOfConnections = (hotelsN * (hotelsN - 1)) / 2;
	uint connectedPairs			= 0;
	for (auto road : roads)
	{
		if (road.willBeRemoved || !road.isSet())
			continue;
		auto leftRoot  = dsu.findRoot(road.source);
		auto rightRoot = dsu.findRoot(road.destination);
		if (leftRoot != rightRoot) {
			connectedPairs += dsu.subsetElementsCountOf[leftRoot] * dsu.subsetElementsCountOf[rightRoot];
			dsu.merge(leftRoot, rightRoot);
		}
	}
	return maxNumberOfConnections - connectedPairs;
}

stack<uint> processCommands() {
	stack<uint> disconnectedPairsPerStep;
	auto disconnectedPairs = computeNumberOfDisconnectedPairs();
	while (!commands.empty()) {
		auto currentCommand = commands.top();
		commands.pop();
		if (currentCommand.type == commandType::query)
			disconnectedPairsPerStep.push(disconnectedPairs);
		if (currentCommand.type == commandType::removeRoad) {
			auto road = roads[currentCommand.road];
			if (!road.willBeRemoved)
				continue;
			auto leftRoot  = dsu.findRoot(road.source);
			auto rightRoot = dsu.findRoot(road.destination);
			if (leftRoot != rightRoot) {
				disconnectedPairs -= dsu.subsetElementsCountOf[leftRoot] * dsu.subsetElementsCountOf[rightRoot];
				dsu.merge(leftRoot, rightRoot);
			}
		}
	}
	return disconnectedPairsPerStep;
}
int main() {
	int tests, lhs, rhs, roadToRemove;
	char commandCharacter;
	scanf("%d", &tests);
	while (tests--) {
		scanf("%d", &hotelsN);
		roadsN = hotelsN - 1;
		roads.clear();
		roads.resize(roadsN + 1);
		dsu = disjoint_set(roadsN);
		for (auto roadId = 1; roadId <= roadsN; roadId++) {
			scanf("%d %d", &lhs, &rhs);
			roads[roadId] = road(lhs, rhs, false);
		}
		scanf("%d", &queriesN);
		getchar();
		while (queriesN--)
		{
			scanf("%c", &commandCharacter);
			if (commandCharacter == 'R')
			{
				scanf("%d", &roadToRemove);
				commands.push(command(commandType::removeRoad, roadToRemove));
				roads[roadToRemove].willBeRemoved = true;
			}
			else if (commandCharacter == 'Q')
			{
				commands.push(command(commandType::query, -1));
			}
			getchar();
		}
		auto disconnectedPairsPerStep = processCommands();
		while (!disconnectedPairsPerStep.empty()) {
			printf("%lu\n", disconnectedPairsPerStep.top());
			disconnectedPairsPerStep.pop();
		}
	}
	return 0;
}