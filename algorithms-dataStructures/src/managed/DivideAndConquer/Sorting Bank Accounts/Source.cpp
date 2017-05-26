#define _CRT_SECURE_NO_WARNINGS
#include<map>
#include<string>
#include <iostream>
using namespace std;

#define account	first
#define count second
map<string, int> accounts;

int main()
{
	int tests, accountsN;
	scanf("%d", &tests);

	while(tests)
	{
		accounts.clear();
	
		string account;
		for (scanf("%d\n", &accountsN); accountsN; accountsN--) {
			getline(cin, account);
			accounts[account]++;
		}
		for(auto pair : accounts)
			printf("%s %d\n", pair.account.c_str(), pair.count);

		tests--;
	}
	return 0;
}