#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<array>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>

using namespace std;

enum packageState
{
	undiscovered	= 0,
	discovered		= 1,
	installed		= 2
};

unordered_map<string, vector<string>>	dependencyGraph;
unordered_set<string>					availablePackages;
unordered_map<string, int>				packageState;

bool dfs(string currentPackage)
{
	packageState[currentPackage] = discovered;

	for(auto dependent : dependencyGraph[currentPackage])
	{
		if (availablePackages.find(dependent) == availablePackages.end())
			return false;
		if (packageState[dependent] == discovered)
			return false;
		if(packageState[dependent] == installed)
			continue;
		if(packageState[dependent] == undiscovered)
		{
			if (!dfs(dependent))
				return false;
		}
	}

	for(auto dependent : dependencyGraph[currentPackage])
	{
		if(packageState[dependent] != installed)
			return false;
	}

	packageState[currentPackage] = installed;
	return true;
}

int process()
{
	for(auto package : availablePackages)
	{
		if(packageState[package] == undiscovered)
		{
			dfs(package);
		}
	}
	return count_if(packageState.begin(), packageState.end(), [](pair<string, int> packageState) { return packageState.second == installed; });
}

int main()
{
	char packageNameArray[10000];
	char packageDependencyNameArray[10000];
	for (;;)
	{
		packageNameArray[0] = 0;
		scanf("%s", packageNameArray);
		if (!packageNameArray[0])
			break;
		
		string packageName = packageNameArray;
		packageState[packageName] = undiscovered;
		availablePackages.insert(packageName);
		for (;;)
		{
			scanf("%s", packageDependencyNameArray);
			if (packageDependencyNameArray[0] == '0' && !packageDependencyNameArray[1])
				break;
		
			string dependent = packageDependencyNameArray;
			dependencyGraph[packageName].push_back(dependent);
		}
	}
	cout << process();
	return 0;
}