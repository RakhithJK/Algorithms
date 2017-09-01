#define _CRT_SECURE_NO_WARNINGS
#define maxCheckpoints 2001

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<int>			agnessRoute;
vector<vector<int>> tomRoutes;
int					tomRoute;
int					lcsLengthOf[maxCheckpoints][maxCheckpoints];

int lcs(int agnessSubseqLength, int tomSubseqLength)
{
	if (!agnessSubseqLength || !tomSubseqLength)
		return 0;

	if (lcsLengthOf[agnessSubseqLength][tomSubseqLength] != -1)
		return lcsLengthOf[agnessSubseqLength][tomSubseqLength];

	if (agnessRoute[agnessSubseqLength - 1] == tomRoutes[tomRoute][tomSubseqLength - 1])
		return lcsLengthOf[agnessSubseqLength][tomSubseqLength] = 1 + lcs(agnessSubseqLength - 1, tomSubseqLength - 1);

	return  lcsLengthOf[agnessSubseqLength][tomSubseqLength] = max(
		lcs(agnessSubseqLength -1,  tomSubseqLength),
		lcs(agnessSubseqLength, tomSubseqLength - 1)
	);
}

int main()
{
	int tests, checkpoint;
	scanf("%d", &tests);

	while(tests--)
	{
		agnessRoute.clear();
		tomRoutes.clear();
		tomRoute = 0;

		while(scanf("%d", &checkpoint) && checkpoint != 0)
			agnessRoute.push_back(checkpoint);

		while (true)
		{
			scanf("%d", &checkpoint);
			vector<int> currentRoute;

			if (checkpoint == 0)
				break;

			while (checkpoint != 0)
			{
				currentRoute.push_back(checkpoint);
				scanf("%d", &checkpoint);
			}
			tomRoutes.push_back(currentRoute);
		}

		auto maxCommonCheckpointSeqLength = 0;
		for(auto tomRouteIx = 0; tomRouteIx < tomRoutes.size(); tomRouteIx++)
		{
			memset(lcsLengthOf, -1, sizeof lcsLengthOf);
			tomRoute					 = tomRouteIx;
			maxCommonCheckpointSeqLength = max(maxCommonCheckpointSeqLength, lcs(agnessRoute.size(), tomRoutes[tomRoute].size()));
		}

		printf("%d\n", maxCommonCheckpointSeqLength);
	}
	return 0;
}