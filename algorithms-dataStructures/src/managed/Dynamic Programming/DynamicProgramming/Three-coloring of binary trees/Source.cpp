#define _CRT_SECURE_NO_WARNINGS
#define maxTrees 10001
#define colors 3

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum color
{
	red = 0,
	green = 1,
	blue = 2
};

struct tree_node
{
	tree_node(int id)
	{
		this->id = id;
		this->left = nullptr;
		this->right = nullptr;
	}

	int id = maxTrees;
	tree_node * left;
	tree_node * right;
};

string	treeSchema;
int		lookup[maxTrees][colors];

unordered_map<color, vector<pair<color, color>>> colorings =
{
	{ red,		{ { green, blue },	{ blue,  green	} } },
	{ green,	{ { red, blue	},	{ blue,	 red	} } },
	{ blue,		{ { red, green	},	{ green, red	} } }
};

int position = 0;
tree_node * construct_tree() {

	auto childCount = treeSchema[position];
	auto root = new tree_node(position);
	position++;

	if (childCount == '2') {
		root->left = construct_tree();
		root->right = construct_tree();
	}
	else if (childCount == '1')
		root->left = construct_tree();

	return root;
}

int getMinGreenNodes(tree_node * currentNode, color currentNodeColor)
{
	if (lookup[currentNode->id][currentNodeColor] != -1)
		return lookup[currentNode->id][currentNodeColor];

	auto possibleSubColorings = colorings[currentNodeColor];
	auto minGreenCount = 0;

	if (currentNode->left != nullptr && currentNode->right != nullptr)
	{
		auto subCounts = {
			getMinGreenNodes(currentNode->left, possibleSubColorings[0].first) + getMinGreenNodes(currentNode->right, possibleSubColorings[0].second),
			getMinGreenNodes(currentNode->left, possibleSubColorings[1].first) + getMinGreenNodes(currentNode->right, possibleSubColorings[1].second)
		};

		minGreenCount += *min_element(subCounts.begin(), subCounts.end());
	}
	else if (currentNode->left != nullptr)
	{
		auto subCounts = {
			getMinGreenNodes(currentNode->left, possibleSubColorings[0].first),
			getMinGreenNodes(currentNode->left, possibleSubColorings[1].first)
		};

		minGreenCount += *min_element(subCounts.begin(), subCounts.end());
	}

	return lookup[currentNode->id][currentNodeColor] = minGreenCount + (currentNodeColor == green);
}

int getMaxGreenNodes(tree_node * currentNode, color currentNodeColor)
{
	if (lookup[currentNode->id][currentNodeColor] != -1)
		return lookup[currentNode->id][currentNodeColor];

	auto possibleSubColorings = colorings[currentNodeColor];
	auto maxGreenCount = 0;

	if (currentNode->left != nullptr && currentNode->right != nullptr)
	{
		auto subCounts = {
			getMaxGreenNodes(currentNode->left, possibleSubColorings[0].first) + getMaxGreenNodes(currentNode->right, possibleSubColorings[0].second),
			getMaxGreenNodes(currentNode->left, possibleSubColorings[1].first) + getMaxGreenNodes(currentNode->right, possibleSubColorings[1].second)
		};

		maxGreenCount += *max_element(subCounts.begin(), subCounts.end());
	}
	else if (currentNode->left != nullptr)
	{
		auto subCounts = {
			getMaxGreenNodes(currentNode->left, possibleSubColorings[0].first),
			getMaxGreenNodes(currentNode->left, possibleSubColorings[1].first)
		};

		maxGreenCount += *max_element(subCounts.begin(), subCounts.end());
	}

	return lookup[currentNode->id][currentNodeColor] = maxGreenCount + (currentNodeColor == green);
}

inline color asColor(int color) { return static_cast<::color>(color); }

int main()
{

	int tests;
	cin >> tests;
	while (tests--)
	{
		cin >> treeSchema;
		position = 0;

		memset(lookup, -1, sizeof lookup);

		auto tree   = construct_tree();
		auto minSol = maxTrees;
		auto maxSol = 0;

		for (auto color = 0; color < colors; color++)	
			minSol = min(minSol, getMinGreenNodes(tree, asColor(color)));
		
		memset(lookup, -1, sizeof lookup);

		for (auto color = 0; color < colors; color++)
			maxSol = max(maxSol, getMaxGreenNodes(tree, asColor(color)));

		cout << maxSol << ' ' << minSol << endl;
	}
	return 0;
}