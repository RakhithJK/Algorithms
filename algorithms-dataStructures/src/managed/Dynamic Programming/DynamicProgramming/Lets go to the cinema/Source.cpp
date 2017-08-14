#include<cstring>
#include<map>
#include<list>
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<algorithm>

using namespace std;

#define maxPeopleCount 100001

int singleTicketPrice, familyTicketPrice;

struct state
{
	int singleTickets;
	int familyTickets;

	state()										{ this->singleTickets = 0;				this->familyTickets = 0; }
	state(int singleTickets, int familyTickets) { this->singleTickets = singleTickets;	this->familyTickets = familyTickets; }

	void operator += (const state& other)
	{
		this->singleTickets += other.singleTickets;
		this->familyTickets += other.familyTickets;
	}

	bool operator < (const state& other) const
	{
		if (this->getCost() == other.getCost())
			return this->getTicketsCount() < other.getTicketsCount();

		return this->getCost() < other.getCost();
	}

	int getCost()			const { return this->singleTickets * singleTicketPrice + this->familyTickets * familyTicketPrice; }
	int getTicketsCount()	const { return this->singleTickets + this->familyTickets; }
};

map<string, int>	personNameToIdLookup;
vector<int>			familyTreeOf[maxPeopleCount];
bool				isChild[maxPeopleCount];
bool				didComputeState[maxPeopleCount][2];
state				minimumCostOf[maxPeopleCount][2];

int getPersonId(const string name) {
	auto lookupTableSize = personNameToIdLookup.size();

	return (personNameToIdLookup.find(name) == personNameToIdLookup.end()) ?
		personNameToIdLookup[name] = lookupTableSize :
		personNameToIdLookup[name];
}

state computeMinimumSubtreeCost_RootedAt(int parent, bool isUnderFamilyTicket) {
	if (familyTreeOf[parent].size() == 0)
		return isUnderFamilyTicket ? state(0, 0) : state(1, 0);

	if (didComputeState[parent][isUnderFamilyTicket])
		return minimumCostOf[parent][isUnderFamilyTicket];

	didComputeState[parent][isUnderFamilyTicket] = true;

	state costIfTakeFamilyTicket	(0, 1);
	state costIfTakeSelfTicket		(1 - isUnderFamilyTicket, 0);

	for (auto child : familyTreeOf[parent])
	{
		costIfTakeFamilyTicket += computeMinimumSubtreeCost_RootedAt(child, true);
		costIfTakeSelfTicket   += computeMinimumSubtreeCost_RootedAt(child, false);
	}

	return minimumCostOf[parent][isUnderFamilyTicket] = min(costIfTakeFamilyTicket, costIfTakeSelfTicket);
}

void clear()
{
	memset(didComputeState, false, sizeof didComputeState);
	memset(isChild, false, sizeof isChild);

	for (auto personId = 0; personId < personNameToIdLookup.size(); personId++)
		familyTreeOf[personId].clear();
	personNameToIdLookup.clear();
}

int main()
{
	string inputLine, parentName, childName;

	auto currentTestCase = 1;
	while (cin >> singleTicketPrice >> familyTicketPrice)
	{
		if (singleTicketPrice == 0 && familyTicketPrice == 0)
			break;

		clear();

		cin >> ws;
		while (getline(cin, inputLine))
		{
			istringstream inputLineStream(inputLine);
			inputLineStream >> parentName;
			auto parentId = getPersonId(parentName);

			while (inputLineStream >> childName) {
				auto childId = getPersonId(childName);

				isChild[childId] = true;
				familyTreeOf[parentId].push_back(childId);
			}

			cin >> ws;
			if (isdigit(cin.peek()))
				break;
		}

		state solutionState(0, 0);

		for (auto currentPersonId = 0; currentPersonId <personNameToIdLookup.size(); currentPersonId++)
			if (!isChild[currentPersonId])
				solutionState += computeMinimumSubtreeCost_RootedAt(currentPersonId, false);
		
		printf("%d. %d %d %d\n", currentTestCase++, solutionState.singleTickets, solutionState.familyTickets, solutionState.getCost());
	}
	return 0;
}