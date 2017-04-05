#include<iostream>
#include<set>
#include<algorithm>

using namespace std;
int main()
{
	set<int> friendsOfFriends;
	set<int> friends;
	
	int friendsN;
	cin >> friendsN;

	while(friendsN)
	{
		int friendId, friendsOfFriendN;
		cin >> friendId >> friendsOfFriendN;
		friends.insert(friendId);

		while(friendsOfFriendN)
		{
			int friendOfFriend;
			cin >> friendOfFriend;
			friendsOfFriends.insert(friendOfFriend);
			friendsOfFriendN--;
		}
		friendsN--;
	}

	int result = friendsOfFriends.size();

	for(auto f : friends)
		if(friendsOfFriends.find(f) != friendsOfFriends.end())
			result--;

	cout << result;
	return 0;
}