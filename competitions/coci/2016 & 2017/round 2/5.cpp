#include<iostream>
#include<vector>
#include<deque>

using namespace std;

int palindromize(vector<int>& seq)
{
	int actionsPerformed = 0; 
 
    for (int i = 0, j = seq.size() - 1; i<=j;)
    {
		int lhs = seq[i];
		int rhs = seq[j];

        if (lhs == rhs)
        {
            i++;
            j--;
        }

        else if (lhs > rhs)
        {
            j--;
			seq[j] += seq[j+1];
			actionsPerformed++;
        }

        else
        {
            i++;
			seq[i] += seq[i-1];
			actionsPerformed++;
        }
    }
 
    return actionsPerformed;
}

int palindromizeRecursively(deque<int>& seq, int actionsPerformed = 0)
{
	if (seq.size() == 0)
		return actionsPerformed;

	int lhs = seq.front();
	int rhs = seq.back();

	if(lhs == rhs)
	{
		seq.pop_front();
		seq.pop_back();
	}

	if(lhs < rhs)
	{
		seq.pop_front();
		int after = seq.front();
		seq.pop_front();

		seq.push_front(after + lhs);
		actionsPerformed++;
	}

	else if(lhs > rhs)
	{
		seq.pop_back();
		int previous = seq.back();
		seq.pop_back();

		seq.push_back(previous + rhs);
		actionsPerformed++;
	}

	return palindromizeRecursively(seq, actionsPerformed);
}


int main()
{
	int         numberOfElements;
	vector<int> seq;
	deque<int>  deq;

	cin >> numberOfElements;

	for (int i = 0; i < numberOfElements; i++)
	{
		int temp;
		cin >> temp;
		seq.push_back(temp);
		deq.push_back(temp);
	}

	cout << palindromizeRecursively(deq);
	return 0;
}