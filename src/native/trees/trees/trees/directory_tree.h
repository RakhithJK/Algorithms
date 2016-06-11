#include "directory.h"
#include <array>
#include <queue>
#include <iostream>
class directory_tree
{
public:
	directory_tree()
	{
		root = new directory();
	}
	~directory_tree()
	{
	}

	void printTabbed(const std::string& content, int tabsCount = 0)
	{
		for (size_t i = 0; i < tabsCount; i++)
		{
			std::cout << "\t";
		}
		std::cout << content << std::endl;
	}
	void processDirectory(directory* directory, int tabsCount)
	{
		printTabbed(directory->name(), tabsCount);
		tabsCount++;
		auto filesContainter = directory->files();

		for (size_t i = 0; i < filesContainter.size(); i++)
		{
			printTabbed(filesContainter[i], tabsCount);
		}
	}

	void traverseByBfs(directory* rootDirectory, std::queue<directory*> *directoriesQueue)
	{
		int tabsCount = 0;
		directoriesQueue->push(rootDirectory);

		while (directoriesQueue->size())
		{
			auto currentDirectory = directoriesQueue->front();
			processDirectory(currentDirectory, tabsCount);
			directoriesQueue->pop();
			tabsCount++;
			for (size_t i = 0; i < currentDirectory->subDirectories().size(); i++)
			{
				directoriesQueue->push(currentDirectory->subDirectories()[i]);
			}
		}
	}

	void traverseByBfs()
	{
		auto directoriesQueue = new std::queue<directory*>();
		traverseByBfs(this->root, directoriesQueue);
		delete directoriesQueue;
	}

	void traverseByDfs(directory* currentDirectory, int tabsCount = 0)
	{
		if (currentDirectory != nullptr)
		{
			processDirectory(currentDirectory, tabsCount);
			tabsCount++;
			auto currentDirectorySubdirectories = currentDirectory->subDirectories();
			for (size_t i = 0; i < currentDirectorySubdirectories.size(); i++)
			{
				traverseByDfs(currentDirectorySubdirectories[i], tabsCount);
			}
		}
	}
	void traverseByDfs()
	{
		traverseByDfs(this->root);
	}

	directory* root;
};