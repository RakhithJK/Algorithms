#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

const int maxStationsN = 2505;
const int maxSegmentStationsN = 95;
const int modulo = 10243;

vector<int> tree[maxStationsN];
int segmentsOfStationWithLength[maxStationsN][maxSegmentStationsN];
int allSegmentsOfStationWithTargetLength[maxStationsN];
int stationsN, targetSegmentStationsN;

inline int addWithModulo(const int a, const int b)
{
	return (a + b) % modulo;
}
inline int multiplyWithModulo(const int a, const int b)
{
	return (a * b) % modulo;
}

inline void computeNumberOfSegmentCombinations(int station, int childStation)
{
	int currentSubtreesOfLengthCopy[maxStationsN];

	for (auto i = 0; i < targetSegmentStationsN; i++)
		currentSubtreesOfLengthCopy[i] = segmentsOfStationWithLength[station][i];

	for (auto segmentRootedAtCurrentLength = 1; segmentRootedAtCurrentLength <= targetSegmentStationsN; segmentRootedAtCurrentLength++)
	{
		for (auto segmentRootedAtChildLength = 1; segmentRootedAtChildLength < segmentRootedAtCurrentLength; segmentRootedAtChildLength++)
		{
			segmentsOfStationWithLength[station][segmentRootedAtCurrentLength] = addWithModulo(
				segmentsOfStationWithLength[station][segmentRootedAtCurrentLength],
				multiplyWithModulo(
					currentSubtreesOfLengthCopy[segmentRootedAtCurrentLength - segmentRootedAtChildLength],
					segmentsOfStationWithLength[childStation][segmentRootedAtChildLength]
				)
			);
		}
	}
}

int dfs(int currentStation, int previousStation)
{
	segmentsOfStationWithLength[currentStation][1] = 1;

	for (int child : tree[currentStation])
	{
		if (child == previousStation)
			continue;

		dfs(child, currentStation);
		computeNumberOfSegmentCombinations(currentStation, child);
	}

	for (auto child : tree[currentStation])
		segmentsOfStationWithLength[currentStation][targetSegmentStationsN] = addWithModulo(
			segmentsOfStationWithLength[currentStation][targetSegmentStationsN],
			allSegmentsOfStationWithTargetLength[child]
		);

	return allSegmentsOfStationWithTargetLength[currentStation] = segmentsOfStationWithLength[currentStation][targetSegmentStationsN];
}


int main() {
	scanf("%d %d", &stationsN, &targetSegmentStationsN);
	int source, destination;

	for (int i = 1; i < stationsN; i++) {
		scanf("%d %d", &source, &destination);
		tree[source].push_back(destination);
		tree[destination].push_back(source);
	}

	auto solution = dfs(1, 0);
	printf("%d\n", solution);

	return 0;
}