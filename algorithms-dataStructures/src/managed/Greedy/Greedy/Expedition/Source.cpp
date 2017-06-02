#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct station
{
	station() {}
	station (int distance, int fuel)
	{
		this->distanceFromTruck = distance;
		this->fuelGain			= fuel;
	}
	int fuelGain;
	int distanceFromTruck;
};

int stationsN, distanceToCity, remainingFuel;

int calculateMinimumStopsCount(vector<station> &stations)
{
	auto stopsCount							    = 0;
	auto orderStationsByDistanceAscending		= [](station& lhs, station&rhs) { return lhs.distanceFromTruck < rhs.distanceFromTruck; };
	auto orderReachableStationsByFuelDescending = [](station& lhs, station&rhs) { return lhs.fuelGain < rhs.fuelGain; };

	priority_queue<
		station, 
	    vector<station>, 
	    decltype(orderReachableStationsByFuelDescending)> 
	reachableStations(orderReachableStationsByFuelDescending);

	sort(stations.begin(), stations.end(), orderStationsByDistanceAscending);
	auto distanceTravelled = 0;
	for(auto station : stations)
	{
		auto distanceToTravel = station.distanceFromTruck - distanceTravelled;
		if(remainingFuel < distanceToTravel)
		{
			while(!reachableStations.empty() && remainingFuel < distanceToTravel)
			{
				stopsCount++;
				remainingFuel += reachableStations.top().fuelGain;
				reachableStations.pop();
			}
		}
		if (remainingFuel < distanceToTravel)
			return -1;
		reachableStations.push(station);
		remainingFuel -= distanceToTravel;
		distanceTravelled = station.distanceFromTruck;
	}
	return stopsCount;
}
int main()
{
	int tests;
	scanf("%d", &tests);
	while(tests--)
	{
		vector<station> stations;
		scanf("%d", &stationsN);
		for(auto i = 0; i < stationsN; i++)
		{
			station station;
			scanf("%d %d", &station.distanceFromTruck, &station.fuelGain);
			stations.push_back(station);
		}
		scanf("%d %d", &distanceToCity, &remainingFuel);
		for (auto &station : stations)
			station.distanceFromTruck = distanceToCity - station.distanceFromTruck;
		stations.push_back(station(distanceToCity, 0)); // town - latestStation
		printf("%d\n", calculateMinimumStopsCount(stations));
	}
	return 0;
}