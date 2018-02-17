#include "stdafx.h"
#include "Bank.h"

#include <iostream>

Bank::Bank()
{
	//Victory Coins
	numCoins1 = 0;
	numCoins3 = 0;
	numCoins5 = 0;
	numCoins10 = 0;

	//Game Pieces
	numTrollLairs = 0;
	numFortresses = 0;
	numMountains = 0;
	numEncampments = 0;
	numHoles = 0;
	numHeroes = 0;
	numDragon = 0;

	//Race & Lost Tribe Tokens
	numAmazons = 0;
	numDwarves = 0;
	numElves = 0;
	numGhouls = 0;
	numGiants = 0;
	numHalflings = 0;
	numHumans = 0;
	numOrcs = 0;
	numRatmen = 0;
	numSkeletons = 0;
	numSorcerers = 0;
	numTritons = 0;
	numTrolls = 0;
	numWizards = 0;
	numTribes = 0;
}

void Bank::initialize() {
	//Initialize bank with same amount of pieces from the board game
	//Victory Coins
	numCoins1 = 35;
	numCoins3 = 20;
	numCoins5 = 24;
	numCoins10 = 30;

	//Game Pieces
	numTrollLairs = 10;
	numFortresses = 6;
	numMountains = 9;
	numEncampments = 5;
	numHoles = 2;
	numHeroes = 2;
	numDragon = 1;

	//Race & Lost Tribe Tokens
	numAmazons = 15;
	numDwarves = 8;
	numElves = 11;
	numGhouls = 10;
	numGiants = 11;
	numHalflings = 11;
	numHumans = 10;
	numOrcs = 10;
	numRatmen = 13;
	numSkeletons = 20;
	numSorcerers = 18;
	numTritons = 11;
	numTrolls = 10;
	numWizards = 10;
	numTribes = 18;

	//Push all game items to the bank at start of game in type value pairs
	bankContents.push_back(pair<string, int>("coin1", numCoins1));
	bankContents.push_back(pair<string, int>("coin3", numCoins3));
	bankContents.push_back(pair<string, int>("coin5", numCoins5));
	bankContents.push_back(pair<string, int>("coin10", numCoins10));

	bankContents.push_back(pair<string, int>("trollLairToken", numTrollLairs));
	bankContents.push_back(pair<string, int>("fortressToken", numFortresses));
	bankContents.push_back(pair<string, int>("mountainToken", numMountains));
	bankContents.push_back(pair<string, int>("encampmentToken", numEncampments));
	bankContents.push_back(pair<string, int>("holeToken", numHoles));
	bankContents.push_back(pair<string, int>("heroToken", numHeroes));
	bankContents.push_back(pair<string, int>("dragonToken", numDragon));

	bankContents.push_back(pair<string, int>("amazonToken", numAmazons));
	bankContents.push_back(pair<string, int>("dwarfToken", numDwarves));
	bankContents.push_back(pair<string, int>("elfToken", numElves));
	bankContents.push_back(pair<string, int>("ghoulToken", numGhouls));
	bankContents.push_back(pair<string, int>("giantToken", numGiants));
	bankContents.push_back(pair<string, int>("halflingToken", numHalflings));
	bankContents.push_back(pair<string, int>("humanToken", numHumans));
	bankContents.push_back(pair<string, int>("orcToken", numOrcs));
	bankContents.push_back(pair<string, int>("ratmanToken", numRatmen));
	bankContents.push_back(pair<string, int>("skeletonToken", numSkeletons));
	bankContents.push_back(pair<string, int>("sorcererToken", numSorcerers));
	bankContents.push_back(pair<string, int>("tritonToken", numTritons));
	bankContents.push_back(pair<string, int>("trollToken", numTrolls));
	bankContents.push_back(pair<string, int>("wizardToken", numWizards));
	bankContents.push_back(pair<string, int>("tribeToken", numTribes));
}

/*void Bank::givePlayer(Player p, string type, int amount) {
}*/

void Bank::displayBankContents() {
	for (int i = 0; i < bankContents.size(); i++) {

	}
}