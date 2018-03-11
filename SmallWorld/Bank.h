#pragma once

#include "Player.h"

#include <map>
#include <vector>

using namespace std;

class Bank
{
private:
	vector<pair<string, int>> bankContents;

	//Victory Coins
	int numCoins1;
	int numCoins3;
	int numCoins5;
	int numCoins10;

	//Game Pieces
	int numTrollLairs;
	int numFortresses;
	int numMountains;
	int numEncampments;
	int numHoles;
	int numHeroes;
	int numDragon;

	//Race & Lost Tribe Tokens
	int numAmazons;
	int numDwarves;
	int numElves;
	int numGhouls;
	int numGiants;
	int numHalflings;
	int numHumans;
	int numOrcs;
	int numRatmen;
	int numSkeletons;
	int numSorcerers;
	int numTritons;
	int numTrolls;
	int numWizards;
	int numTribes;

public:
	Bank();
	void initialize();
	void displayBankContents();
	//void givePlayer(Player p, string var, int amount);
};

