#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<limits>
#include<numeric>
#include<climits>

using namespace std;

const int noParent = 0;
struct node
{
	node(int parent = 0) { this->parent = parent; };
	int parent;
	vector<int> children;
};

int testsN, employeesN, queriesN;
unordered_map<int, long long> salary;
unordered_map<int, node> hierarchy;
unordered_set<int> employees;

vector<int> emptyVector;

long long minSalary;
long long increase;
void findMinSalary(int employeeId)
{
	if (salary[employeeId] < minSalary)
		minSalary = salary[employeeId];

	for (auto child : hierarchy[employeeId].children)
		findMinSalary(child);
}

void increaseRecursively(int employeeId)
{
	salary[employeeId] += increase;
	for (auto child : hierarchy[employeeId].children)
		increaseRecursively(child);
}
void increaseSalaries(int employeeId)
{
	increase = 0;
	minSalary = LLONG_MAX - 1;
    findMinSalary(employeeId);
	if (minSalary >= 1000)
		minSalary = 1000;
	increase = minSalary;
	increaseRecursively(employeeId);
}

long long sumRecursively(int employeeId)
{
	auto currentSum = salary[employeeId];
	for (auto child : hierarchy[employeeId].children)
		currentSum += sumRecursively(child);
	return currentSum;
}
void sumSalaries(int employeeId)
{
	auto sum = sumRecursively(employeeId);
	printf("%lld\n", sum);
}
inline void buildTreeForTest()
{
	salary.clear();
	hierarchy.clear();
	employees.clear();

	scanf("%d %d", &employeesN, &queriesN);

	for (int i = 1; i <= employeesN; i++)
	{
		employees.insert(i);
		salary.insert({ i, 0 });
		hierarchy.insert({ i, node(0) });
	}

	int p;
	long long s;
	int qType, empId;
	for (int i = 1; i <= employeesN; i++)
	{  
		scanf("%d %lld", &p, &s);
		salary[i] = s;
		hierarchy[p].children.push_back(i);
		hierarchy[i].parent = p;
	}

	for(int q = 0; q < queriesN; q++)
	{
		scanf("%d %d", &qType, &empId);
		if (qType == 1)
			sumSalaries(empId);
		else if (qType == 2)
			increaseSalaries(empId);
	}

}
int main()
{
	scanf("%d", &testsN);
	for(int t = 1; t <= testsN; t++)
	{
		printf("Case %d:\n", t);
		buildTreeForTest();
	}
	return 0;
}