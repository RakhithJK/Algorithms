#include<iostream>
#include<string>

#include "directory.h"
#include "directory_tree.h"
int main()
{
	directory* root = new directory();
	root->setName("root");

	root->files().push_back("rootDoc.txt");
	root->files().push_back("ovoJeRoot.txt");

	{
		directory* documents = new directory();
		documents->setName("documents");
		documents->files().push_back("dokument1.txt");
		documents->files().push_back("dokument2.txt");

		directory* presentations = new directory();
		presentations->setName("presentations");
		presentations->files().push_back("aplikacije.pptx");
		presentations->files().push_back("geografija.pptx");

		documents->subDirectories().push_back(presentations);
		root->subDirectories().push_back(documents);
	}

	{
		directory* common = new directory();
		common->setName("common");
		common->files().push_back("common.txt");
		common->files().push_back("nesto.txt");
		root->subDirectories().push_back(common);
	}

	directory_tree* directoryTree = new directory_tree();
	directoryTree->root = root;
	std::cout << "BFS" << std::endl;
	directoryTree->traverseByBfs();
	std::cout << "DFS" << std::endl;
	directoryTree->traverseByDfs();
	system("pause");
}
