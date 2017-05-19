#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>

using namespace std;
const int		virtualMilkmanRoot = 0;
const int		maximumCitizensNumber = pow(10, 5) + 2;

struct disjoint_set {
	disjoint_set() { clear(); }
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
		return currentElement;
	}
	void merge(int left, int right) {
		auto leftRoot = findRoot(left);
		auto rightRoot = findRoot(right);
		if (subsetElementsCountOf[leftRoot] > subsetElementsCountOf[rightRoot]) {
			rootOf[rightRoot] = leftRoot;
			subsetElementsCountOf[leftRoot] += subsetElementsCountOf[rightRoot];
		}
		else
		{
			rootOf[leftRoot] = rightRoot;
			subsetElementsCountOf[rightRoot] += subsetElementsCountOf[leftRoot];
		}
	}
	bool areConnected(int node1, int node2) {
		return findRoot(node1) == findRoot(node2);
	}
	void clear() {
		subsetElementsCountOf = vector<int>(maximumCitizensNumber, 1);
		rootOf = vector<int>(maximumCitizensNumber);
		for (int element = 1; element < rootOf.size(); element++)
			rootOf[element] = element;
	}
};
struct road {
	road() {}
	road(int lhs, int rhs, int cost) {
		this->source = lhs;
		this->destination = rhs;
		this->cost = cost;
	}

	int source;
	int destination;
	int cost;

	bool operator < (road other) {
		return other.cost > this->cost;
	}
};

vector<road>	roads;
disjoint_set	dsu;

long computeMstCost(int citizensN) {
	sort(roads.begin(), roads.end());
	long cost = 0;
	for (auto& edge : roads) {
		if (!dsu.areConnected(edge.source, edge.destination)) {
			cost += edge.cost;
			dsu.merge(edge.source, edge.destination);
		}
	}
	for (int citizen = 1; citizen < citizensN; citizen++)
		if (!dsu.areConnected(virtualMilkmanRoot, citizen))
			return -1;
	return cost;
}

int main() {
	int testsN;
	scanf("%d", &testsN);
	while (testsN--) {
		int citizensN, roadsN, isMilkman;
		scanf("%d %d", &citizensN, &roadsN);
		roads.clear();
		dsu.clear();
		for (int citizen = 1; citizen <= citizensN; citizen++)
		{
			scanf("%d", &isMilkman);
			if (isMilkman)
				dsu.merge(virtualMilkmanRoot, citizen);
		}
		while (roadsN)
		{
			road road;
			scanf("%d %d %d", &road.source, &road.destination, &road.cost);
			roads.push_back(road);
			roadsN--;
		}
		auto cost = computeMstCost(citizensN + 1);
		if (cost == -1)
			printf("impossible\n");
		else
			printf("%ld\n", cost);
	}
	return 0;
}