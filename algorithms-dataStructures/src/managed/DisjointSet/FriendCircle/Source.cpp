#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<array>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

#define maxPeopleN 20005

struct disjoint_set {
	disjoint_set() { clear(); }
	array<int, maxPeopleN> subsetElementsCountOf;
	array<int, maxPeopleN> rootOf;

	int findRoot(int element) {
		auto currentElement = element;
		while (rootOf[currentElement] != currentElement) {
			currentElement = rootOf[currentElement];
		}
		auto root = currentElement;
		currentElement = element;
		while (rootOf[currentElement] != currentElement) {
			rootOf[currentElement] = root;
			currentElement = rootOf[currentElement];
		}
		return root;
	}
	int merge(int left, int right) {
		auto leftRoot = findRoot(left);
		auto rightRoot = findRoot(right);
		if (leftRoot == rightRoot)
			return subsetElementsCountOf[leftRoot];

		if (subsetElementsCountOf[leftRoot] > subsetElementsCountOf[rightRoot]) {
			rootOf[rightRoot] = leftRoot;
			return subsetElementsCountOf[leftRoot] += subsetElementsCountOf[rightRoot];
		}
		else
		{
			rootOf[leftRoot] = rightRoot;
			return subsetElementsCountOf[rightRoot] += subsetElementsCountOf[leftRoot];
		}
	}
	bool areConnected(int node1, int node2) {
		return findRoot(node1) == findRoot(node2);
	}
	void clear() {
		subsetElementsCountOf.fill(1);
		for (int element = 1; element < rootOf.size(); element++)
			rootOf[element] = element;
	}
};

map<string, int> peopleNames;
disjoint_set dsu;

int getId_setIfNeeded(const string& name) {
	if (peopleNames.find(name) == peopleNames.end())
		return peopleNames[name] = peopleNames.size() + 1;
	return peopleNames[name];
}


int main() {
	int tests;
	int relationsN;
	char lhs[25], rhs[25];
	scanf("%d", &tests);
	while (tests--) {
		peopleNames.clear();
		dsu.clear();
		scanf("%d", &relationsN);
		while (relationsN--)
		{
			scanf("%s %s", &lhs, &rhs);
			printf("%d\n", dsu.merge(getId_setIfNeeded(lhs), getId_setIfNeeded(rhs)));
		}
	}
	return 0;
}