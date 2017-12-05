#define _CRT_SECURE_NO_WARNINGS
#define maxStudents 20
#define maxMask (1 << maxStudents)

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif

#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long bigint;

int    studentsN, allAssignedMask;
bool   preferencesOfStudent[25][25];
bigint dp[maxMask];

inline bool isAssignmentAlreadyGiven(int mask, int assignment) { return mask & (1 << assignment); }
inline int markAssignmentAsGiven(int mask, int assignment) { return mask | (1 << assignment); }

bigint countWays(int currentMask) {
	auto currentStudent = __builtin_popcount(currentMask);

	if (currentStudent == studentsN && currentMask == allAssignedMask)
		return 1;

	if (dp[currentMask] != -1)
		return dp[currentMask];

	bigint ways = 0;
	for (auto assignment = 0; assignment < studentsN; assignment++) 
	{
		if (!preferencesOfStudent[currentStudent][assignment])
			continue;
		if (isAssignmentAlreadyGiven(currentMask, assignment))
			continue;
		
		ways += countWays(markAssignmentAsGiven(currentMask, assignment));
	}
	return dp[currentMask] = ways;
}

int main() {
	int tests;
	scanf("%d", &tests);

	while (tests--) {
		memset(dp, -1, sizeof dp);
		scanf("%d", &studentsN);
		allAssignedMask = pow(2, studentsN) - 1;

		for (auto student = 0; student < studentsN; student++) 
			for (auto assignment = 0; assignment < studentsN; assignment++) 
				scanf("%d", &preferencesOfStudent[student][assignment]);

		bigint ways = countWays(0);
		printf("%llu\n", ways);
	}
	return 0;
}