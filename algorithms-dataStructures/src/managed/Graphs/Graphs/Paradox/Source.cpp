#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<string>

using namespace std;

map<int, pair<int,bool>>	sentence;
map<int, bool>				state;
set<int>					validatedSentences;
map<int, bool>				correctSentences;

bool isContradiction = false;

void tryFindContradictionIf(int sentenceToExecute, bool isCurrentCorrect)
{
	if(validatedSentences.find(sentenceToExecute) != validatedSentences.end())
	{
		if(correctSentences.find(sentenceToExecute) != correctSentences.end())
		{
			isContradiction = correctSentences[sentenceToExecute] != isCurrentCorrect;
			return;
		}
		isContradiction = false;
		return;
	}

	validatedSentences.insert(sentenceToExecute);
	correctSentences[sentenceToExecute] = isCurrentCorrect;
	auto toExecute = sentence[sentenceToExecute];

	if(isCurrentCorrect)
	{
		state[toExecute.first] = toExecute.second;
		tryFindContradictionIf(toExecute.first, toExecute.second);
	}
	else
	{
		state[toExecute.first] = !toExecute.second;
		tryFindContradictionIf(toExecute.first, !toExecute.second);
	}
}

void validate()
{
	for(auto sentence : sentence)
	{
		if (validatedSentences.find(sentence.first) == validatedSentences.end())
		{
			correctSentences.clear();
			state.clear();
			tryFindContradictionIf(sentence.first, true);
			if(isContradiction)
			{
				cout << "PARADOX \n";
				return;
			}
		}
	}
	cout << "NOT PARADOX \n";
}


int main()
{
	int n;
	cin >> n;
	while(n)
	{
		sentence.clear();
		validatedSentences.clear();
		for(int i = 1; i <= n; i++)
		{
			int x;
			string value;
			cin >> x >> value;
			sentence[i] = { x, value == "true" };
		}
		validate();
		cin >> n;
	}
	return 0;
}