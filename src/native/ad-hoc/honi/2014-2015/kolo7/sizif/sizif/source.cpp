#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int numberOfKeysAndDoors = 0;
int unlockCount = 0;
vector<int> keys;


int fails = 0;
int currentUnlockCount = 0;
int currentFailedUnlocksCount = 0;

void unlockAllDoors()
{
	int i = 0;
	int door = 1;
	while (currentUnlockCount < unlockCount)
	{
		if (i > keys.size() - 1)
		{
			i = 0;
		}
		if (door > keys.size())
		{
			door = 1;
		}
	
		int keyForDoor = keys[i];
		if (door == keyForDoor)
		{
			currentUnlockCount++;
			door++;
			i--;
		}
		else
		{
			currentFailedUnlocksCount++;
		}
		i++;
	}
}

int main()
{
	cin >> numberOfKeysAndDoors >> unlockCount;

	for (auto i = 0; i < numberOfKeysAndDoors; i++)
	{
		int currentKey;
		cin >> currentKey;
		keys.push_back(currentKey);
	}
	unlockAllDoors();
	cout << endl;
	cout << currentFailedUnlocksCount << endl;
	system("pause");
}