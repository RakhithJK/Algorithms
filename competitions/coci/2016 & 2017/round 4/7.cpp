#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

vector<int> solutions;

vector<string> was;
vector<string> words;
map<int, vector<string>> wordsGroupedByLength;


bool wasBefore(const string& word)
{
	return find(was.begin(), was.end(), word) != was.end();
}

bool areCompatible(const string& kraca, const string& dulja) {
	auto postojiLiZajednickiSufiks1 = dulja.find(kraca);
	auto sameLength = kraca.size() == dulja.size();

	if (postojiLiZajednickiSufiks1 == string::npos && !sameLength)
		return false;

	else if (postojiLiZajednickiSufiks1 != string::npos && !sameLength) {
		auto sufiks = dulja.substr(postojiLiZajednickiSufiks1, kraca.size());
		return sufiks.size() == dulja.size() || sufiks.size() == dulja.size() - 1;
	}


	auto temp = kraca;
	auto kracaBezPrvog = temp;
	kracaBezPrvog.erase(0, 1);
	auto postojiLiZajednickiSufiks2 = dulja.find(kracaBezPrvog);

	if(postojiLiZajednickiSufiks2 != string::npos)
	{
		auto sufiks = dulja.substr(postojiLiZajednickiSufiks2, kraca.size());
		return sufiks.size() == dulja.size() || sufiks.size() == dulja.size() - 1;
	}
	
	return false;
}

int substringLength = 0;
void constructSubstringRecursively(const string& currentWord) {
	if (wasBefore(currentWord))
		return;

	was.push_back(currentWord);
	substringLength++;

	auto areAnyWordsSameLengthAsCurrent = wordsGroupedByLength.find(currentWord.length()) != wordsGroupedByLength.end();
	auto areAnyWords1LongerThanCurrent  = wordsGroupedByLength.find(currentWord.length() + 1) != wordsGroupedByLength.end();
	
	if(!areAnyWordsSameLengthAsCurrent && !areAnyWords1LongerThanCurrent)
		return;
		
	if(areAnyWordsSameLengthAsCurrent)
	{
		auto wordsSameLengthAsCurrent = wordsGroupedByLength.at(currentWord.length());

		for_each(wordsSameLengthAsCurrent.begin(), wordsSameLengthAsCurrent.end(), [&](const string& word)
		{
			auto areWordsCompatible = areCompatible(currentWord, word);
			if (areWordsCompatible)
			{
				constructSubstringRecursively(word);
			}
		});
	}

	if (areAnyWords1LongerThanCurrent)
	{
		auto words1LongerThanCurrent = wordsGroupedByLength.at(currentWord.length() + 1);

		for_each(words1LongerThanCurrent.begin(), words1LongerThanCurrent.end(), [&](const string& word)
		{
			auto areWordsCompatible = areCompatible(currentWord, word);
			if (areWordsCompatible)
			{
				constructSubstringRecursively(word);
			}
		});
	}
}

int calculateMaximumSubstring()
{
	sort(words.begin(), words.end(), [](const string& lhs, const string& rhs) { return lhs.size() < rhs.size(); });
	vector<int> allSolutions;

	for (int i = 0; i< words.size(); i++)
	{
		constructSubstringRecursively(words[i]);
		if (substringLength)
		{
			allSolutions.push_back(substringLength);
			substringLength = 0;
			was.clear();
		}
	}
	return *max_element(allSolutions.begin(), allSolutions.end());
}

int main() {
	int wordsCount;
	cin >> wordsCount;

	for (int i =0 ; i < wordsCount; i++)
	{
		string word;
		cin >> word;

		reverse(word.begin(), word.end());
		words.push_back(word);

		if(!wordsGroupedByLength.count(word.length()))
		{
			vector<string> wordsOfLength;
			wordsOfLength.push_back(word);
			wordsGroupedByLength.insert(make_pair(word.length(), wordsOfLength));
		}
		else
		{
			wordsGroupedByLength[word.length()].push_back(word);
		}
	}
	cout << calculateMaximumSubstring() << endl;
}