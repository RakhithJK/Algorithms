#define _CRT_SECURE_NO_WARNINGS
#define maxBudget 101
#define resultBenefit first
#define resultCost second

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

struct dish
{
	int id;
	int cost;
	int benefit;
};


int daysN, dishesN, budget;

vector<dish> dishes;



struct state
{
	double benefit;
	int cost;
	int day;

	state(double benefit, int cost, int day) { this->benefit = benefit; this->cost = cost; this->day = day; }
};


int main()
{
	while (scanf("%d %d %d", &daysN, &dishesN, &budget) && !(!daysN && !dishesN && !budget))
	{
		dishes = vector<dish>(dishesN);

		for(auto dish = 0; dish < dishesN; dish++)
		{
			dishes[dish].id = dish;
			scanf("%d %d", &dishes[dish].cost, &dishes[dish].benefit);
		}

	}
	return 0;
}