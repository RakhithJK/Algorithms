#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int wordsCount;
	vector<string> words;
	vector<string> keyboard;
	vector<char> suggestedChars;
	string startsWithSegment;

	keyboard.push_back("***ABCDE");
	keyboard.push_back("FGHIJKLM");
	keyboard.push_back("NOPQRSTU");
	keyboard.push_back("VWXYZ***");

	cin >> wordsCount;

	for (int i = 0; i < wordsCount; i++)
	{
		string currentWord;
		cin >> currentWord;

		words.push_back(currentWord);
	}

	cin >> startsWithSegment;

	for (auto word : words)
	{
		auto startsWithStartIndex = word.find(startsWithSegment);

		if (startsWithStartIndex == 0) {
			auto suggestedCharIndex = startsWithStartIndex + startsWithSegment.size();
			auto suggestedChar = word[suggestedCharIndex];
			suggestedChars.push_back(suggestedChar);
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {
			auto keyboardChar = keyboard[i][j];
			auto isSuggestedChar = find(suggestedChars.begin(), suggestedChars.end(), keyboardChar) != suggestedChars.end();
			if (isSuggestedChar)
				cout << keyboardChar;
			else
				cout << '*';
		}
		cout << endl;
	}
}