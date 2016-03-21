#include "tokenizer.h"

#include <string>
#include <vector>


std::vector<std::string>  tokenize(const std::string& source, char* delimiters)
{
	std::string value = source;
	std::vector<std::string> tokens;
	int delimeterIndex = value.find_first_of(delimiters);
	while (delimeterIndex != std::string::npos)
	{
		std::string token = value.substr(0, delimeterIndex);
		tokens.push_back(token);
		value = value.substr(delimeterIndex + 1);
		delimeterIndex = value.find_first_of(delimiters);
	}
	return tokens;
}

void tokenizeRecursively(const std::string& source, std::vector<std::string>&tokens, char* delimiters)
{
	std::string value = source;
	int delimeterIndex = value.find_first_of(delimiters);
	if (delimeterIndex != std::string::npos)
	{
		std::string token = value.substr(0, delimeterIndex);
		tokens.push_back(token);
		return tokenizeRecursively(value.substr(delimeterIndex + 1), tokens, delimiters);
	}
}

std::vector<std::string> tokenizeRecursively(const std::string& source, char* delimiters)
{
	std::vector<std::string> tokens;
	tokenizeRecursively(source, tokens, delimiters);
	return tokens;
}
