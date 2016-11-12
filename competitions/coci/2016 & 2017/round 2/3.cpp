#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

struct pokemon
{
	string name;
	int requiredAmountOfSweets;
	int totalNumberOfSweets;
	int evolved = 0;
};

int evolveMaxPokemonsOfType(pokemon* poke)
{
	while (poke->requiredAmountOfSweets <= poke->totalNumberOfSweets)
	{
		poke->evolved++;
		poke->totalNumberOfSweets = poke->totalNumberOfSweets - poke->requiredAmountOfSweets + 2;
	}
	return poke-> evolved;
}


map<pokemon, int> solutions;

int main()
{
	vector<pokemon*> pokemons;
	int numberOfPokemons;
	cin >> numberOfPokemons;

	for (int i = 0; i < numberOfPokemons; i++)
	{
		pokemon* poke = new pokemon();
		cin >> poke->name >> poke->requiredAmountOfSweets >> poke->totalNumberOfSweets;
		pokemons.push_back(poke); 
	}
	
	for (int i = 0; i < numberOfPokemons; i++)
	{
		pokemon* poke = pokemons.at(i);
		poke->evolved = evolveMaxPokemonsOfType(poke);
	}

	int numberOfEvolvedPokemons = 0;

	for (int i = 0; i < numberOfPokemons; i++)
	{
		pokemon* poke = pokemons.at(i);
		numberOfEvolvedPokemons += poke->evolved;
	}

	pokemon* maxPoke = new pokemon();
	for (int i = 0; i < numberOfPokemons; i++)
	{
		pokemon* poke = pokemons.at(i);
		if (poke->evolved > maxPoke->evolved)
			maxPoke = poke;
	}

	cout << numberOfEvolvedPokemons << endl;
	cout << maxPoke->name << endl;
	return 0;
}