#define _CRT_SECURE_NO_WARNINGS
#define queriesMaxN 200010
#define numbersMaxN 30010
#define maxNumber 1000010

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct query
{
	query()
	{
		this->left = queriesMaxN;
		this->right = queriesMaxN;
		this->block = queriesMaxN;
		this->id = 0;
	}

	int id;
	int left;
	int right;
	int block;
};

vector<query> queries;

array<int, queriesMaxN> distinctElementsOfQuery;
array<int, numbersMaxN> numbers;
array<int, maxNumber> occurencesOfNumber;

int numbersN, queriesN;

void processQueries()
{
	auto currentLeft = 0, currentRight = 0, currentDistinctNumbers = 1;
	occurencesOfNumber[numbers[0]] = 1;

	for (const query &query : queries) {
		while (currentLeft < query.left) {
			occurencesOfNumber[numbers[currentLeft]]--;
			currentDistinctNumbers -= (occurencesOfNumber[numbers[currentLeft]] == 0);
			currentLeft++;
		}
		while (currentLeft > query.left) {
			currentLeft--;
			occurencesOfNumber[numbers[currentLeft]]++;
			currentDistinctNumbers += (occurencesOfNumber[numbers[currentLeft]] == 1);
		}
		while (currentRight < query.right) {
			currentRight++;
			occurencesOfNumber[numbers[currentRight]]++;
			currentDistinctNumbers += (occurencesOfNumber[numbers[currentRight]] == 1);
		}
		while (currentRight > query.right) {
			occurencesOfNumber[numbers[currentRight]]--;
			currentDistinctNumbers -= (occurencesOfNumber[numbers[currentRight]] == 0);
			currentRight--;
		}
		distinctElementsOfQuery[query.id] = currentDistinctNumbers;
	}

}
int main() {
	scanf("%d", &numbersN);

	for (auto i = 0; i < numbersN; i++)
		scanf("%d", &numbers[i]);

	int blockSize = sqrt(numbersN);

	scanf("%d", &queriesN);
	for (auto i = 0; i < queriesN; i++)
	{
		query query;
		scanf("%d %d", &query.left, &query.right);
		
		query.id = i;
		query.left--;
		query.right--;
		query.block = query.left / blockSize;
	
		queries.push_back(query);
	}

	sort(queries.begin(), queries.end(), [&](const query& lhs, const query& rhs)
	{
		if (lhs.block < rhs.block)
			return true;
		else if (lhs.block > rhs.block)
			return false;
		else
			return lhs.right < rhs.right;
	});

	processQueries();

	for (auto queryId  = 0; queryId < queriesN; queryId++)
		printf("%d\n", distinctElementsOfQuery[queryId]);

	return 0;
}