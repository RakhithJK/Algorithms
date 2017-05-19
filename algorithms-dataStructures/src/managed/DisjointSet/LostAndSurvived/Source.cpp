#define _CRT_SECURE_NO_WARNINGS
#define maxPeopleN 100005

#include<array>
#include<algorithm>
#include<set>
#include<cstdio>
using namespace std;

struct disjoint_set {
	disjoint_set(int peopleN) { clear(peopleN); }

	array<int, maxPeopleN> subsetElementsCountOf;
	array<int, maxPeopleN> rootOf;
	multiset<int> subsetElementsCounts;

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
		{
			return *(--subsetElementsCounts.end()) - *subsetElementsCounts.begin();
		}

		subsetElementsCounts.erase(subsetElementsCounts.find(subsetElementsCountOf[leftRoot]));
		subsetElementsCounts.erase(subsetElementsCounts.find(subsetElementsCountOf[rightRoot]));

		if (subsetElementsCountOf[leftRoot] > subsetElementsCountOf[rightRoot]) {
			rootOf[rightRoot] = leftRoot;
			subsetElementsCountOf[leftRoot] += subsetElementsCountOf[rightRoot];
			subsetElementsCounts.insert(subsetElementsCountOf[leftRoot]);
		}
		else
		{
			rootOf[leftRoot] = rightRoot;
			subsetElementsCountOf[rightRoot] += subsetElementsCountOf[leftRoot];
			subsetElementsCounts.insert(subsetElementsCountOf[rightRoot]);
		}
		return *(--subsetElementsCounts.end()) - *subsetElementsCounts.begin();
	}

	bool areConnected(int node1, int node2) {
		return findRoot(node1) == findRoot(node2);
	}

	void clear(int peopleN) {
		for (int element = 1; element <= peopleN; element++)
		{
			rootOf[element] = element;
			subsetElementsCountOf[element] = 1;
			subsetElementsCounts.insert(1);
		}
	}
};


int peopleN, queriesN;
int main() {
	int person1, person2;
	scanf("%d %d", &peopleN, &queriesN);
	disjoint_set dsu(peopleN);
	while (queriesN--) {
		scanf("%d %d", &person1, &person2);
		printf("%d\n", dsu.merge(person1, person2));
	}

	return 0;
}