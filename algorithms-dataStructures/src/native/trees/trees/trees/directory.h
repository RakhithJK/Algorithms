#pragma once
#include<string>
#include<vector>

class directory
{
public:

	const std::string& name() const {
		return this->_name;
	}
	void setName(const std::string& newName)
	{
		this->_name = newName;
	}
	std::vector<directory*>& subDirectories()
	{
		return this->_subDirectories;
	}
	std::vector<std::string>& files()
	{
		return this->_files;
	}

	directory()
	{
	}
	~directory()
	{
	}
private:
	std::string _name;
	std::vector<directory*> _subDirectories;
	std::vector<std::string> _files;
};