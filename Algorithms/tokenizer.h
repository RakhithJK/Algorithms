#include <string>
#include <vector>
std::vector<std::string>  tokenize(const std::string& source, char* delimiters);
void tokenizeRecursively(const std::string& source, std::vector<std::string>&tokens, char* delimiters);
std::vector<std::string> tokenizeRecursively(const std::string& source, char* delimiters);