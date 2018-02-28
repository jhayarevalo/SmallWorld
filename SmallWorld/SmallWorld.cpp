// SmallWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>

#include "Map.h"
#include "Player.h"

using namespace std;

string mapName;
Map gameMap;
vector<Player> players;

bool validMap = false;
bool validAction;
bool endTurn;

int playerAction;
int playerAction2;
int regionID;

//Races, Badges, Combos
vector<Race> races;
vector<Badge> badges;
vector<GamePiece> gamePieces;
vector<pair<Race, Badge>> raceDeck;

//Victory Coins
int numCoins1, numCoins3, numCoins5, numCoins10;

//Region Additions
int numTrollLairs, numFortresses, numMountains, numEncampments, numHoles, numHeroes, numDragon;

//Race & Lost Tribe Tokens
int numAmazons, numDwarves, numElves, numGhouls, numGiants, numHalflings, numHumans, numOrcs, numRatmen, numSkeletons, numSorcerers, numTritons, numTrolls, numWizards, numTribes;

void setUpGamePieces() {//to same values as actual board game
	//Victory Coins
	numCoins1 = 35; numCoins3 = 20; numCoins5 = 24; numCoins10 = 30;

	//Game Pieces
	numTrollLairs = 10; numFortresses = 6; numMountains = 9; numEncampments = 5; numHoles = 2; numHeroes = 2; numDragon = 1;

	//Race & Lost Tribe Tokens
	numAmazons = 15; numDwarves = 8; numElves = 11; numGhouls = 10; numGiants = 11; numHalflings = 11; numHumans = 10; numOrcs = 10; numRatmen = 13; numSkeletons = 20; numSorcerers = 18; numTritons = 11; numTrolls = 10; numWizards = 10; numTribes = 18;

	//14 selectable races
	races.push_back(Race("Amazons", 6));
	races.push_back(Race("Dwarves", 3));
	races.push_back(Race("Elves", 6));
	races.push_back(Race("Ghouls", 5));
	races.push_back(Race("Giants", 6));
	races.push_back(Race("Halflings", 6));
	races.push_back(Race("Humans", 5));
	races.push_back(Race("Orcs", 5));
	races.push_back(Race("Ratmen", 8));
	races.push_back(Race("Skeletons", 6));
	races.push_back(Race("Sorcerers", 5));
	races.push_back(Race("Tritons", 6));
	races.push_back(Race("Trolls", 5));
	races.push_back(Race("Wizards", 5));

	//20 power badges
	badges.push_back(Badge("Alchemist", 4));
	badges.push_back(Badge("Berserk", 4));
	badges.push_back(Badge("Bivouacking", 5));
	badges.push_back(Badge("Commando", 4));
	badges.push_back(Badge("Diplomat", 5));
	badges.push_back(Badge("Dragon Master", 5));
	badges.push_back(Badge("Flying", 5));
	badges.push_back(Badge("Forest", 4));
	badges.push_back(Badge("Fortified", 3));
	badges.push_back(Badge("Heroic", 5));
	badges.push_back(Badge("Hill", 4));
	badges.push_back(Badge("Merchant", 2));
	badges.push_back(Badge("Mounted", 5));
	badges.push_back(Badge("Pillaging", 5));
	badges.push_back(Badge("Seafaring", 5));
	badges.push_back(Badge("Spirit", 5));
	badges.push_back(Badge("Stout", 4));
	badges.push_back(Badge("Swamp", 4));
	badges.push_back(Badge("Underworld", 5));
	badges.push_back(Badge("Wealthy", 4));

	//Game Pieces
	for (int gp = 0; gp < numTrollLairs; gp++) {
		gamePieces.push_back(GamePiece("Troll Lair", NULL));
	}
	for (int gp = 0; gp < numFortresses; gp++) {
		gamePieces.push_back(GamePiece("Fortress", NULL));
	}
	for (int gp = 0; gp < numMountains; gp++) {
		gamePieces.push_back(GamePiece("Mountain", NULL));
	}
	for (int gp = 0; gp < numEncampments; gp++) {
		gamePieces.push_back(GamePiece("Encampment", NULL));
	}
	for (int gp = 0; gp < numHoles; gp++) {
		gamePieces.push_back(GamePiece("Hole-in-the-Ground", NULL));
	}
	for (int gp = 0; gp < numHeroes; gp++) {
		gamePieces.push_back(GamePiece("Hero", NULL));
	}
	for (int tl = 0; tl < numDragon; tl++) {
		gamePieces.push_back(GamePiece("Dragon", NULL));
	}
}

void showGameBankContents() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Victory Coins in Bank" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << numCoins1 << "x '1 Coins'" << endl;
	cout << numCoins3 << "x '3 Coins'" << endl;
	cout << numCoins5 << "x '5 Coins'" << endl;
	cout << numCoins10 << "x '10 Coins'" << endl;

	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Race Deck" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	for (int r = 0; r < 6; r++) {
		cout << r + 1 << ". " << raceDeck[r].first.name << " (" << raceDeck[r].first.tokens << ") + " << raceDeck[r].second.name << " (" << raceDeck[r].second.tokens << ")" << endl;
	}

	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Race & Lost Tribe Tokens" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << numAmazons << "x 'Amazon Tokens'" << endl; 
	cout << numDwarves << "x 'Dwarf Tokens'" << endl;
	cout << numElves << "x 'Elf Tokens'" << endl;
	cout << numGhouls << "x 'Ghoul Tokens'" << endl;
	cout << numGiants << "x 'Giant Tokens'" << endl;
	cout << numHalflings << "x 'Halfling Tokens'" << endl;
	cout << numHumans << "x 'Human Tokens'" << endl;
	cout << numOrcs << "x 'Orc Tokens'" << endl;
	cout << numRatmen << "x 'Ratmen Tokens'" << endl;
	cout << numSkeletons << "x 'Skeleton Tokens'" << endl;
	cout << numSorcerers << "x 'Sorcerer Tokens'" << endl;
	cout << numTritons << "x 'Triton Tokens'" << endl;
	cout << numTrolls << "x 'Troll Tokens'" << endl;
	cout << numWizards << "x 'Wizard Tokens'" << endl;
	cout << numTribes << "x 'Lost Tribe Tokens'" << endl;

	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Game Pieces" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << numTrollLairs << "x 'Troll Lairs'" << endl;
	cout << numFortresses << "x 'Fortresses'" << endl;
	cout << numMountains << "x 'Mountains'" << endl;
	cout << numHoles << "x 'Holes-in-the-Ground'" << endl;
	cout << numHeroes << "x 'Heroes'" << endl;
	cout << numDragon << "x 'Dragon'" << endl;
}

vector<pair<Race, Badge>> createRaceDeck() {
	int numRaces = races.size();
	int raceIndex;
	int badgeIndex;

	vector<pair<Race, Badge>> rd;

	for (int i = 0; i < numRaces; i++) {
		raceIndex = rand() % races.size();
		badgeIndex = rand() % badges.size();

		rd.push_back(pair<Race, Badge>(races[raceIndex], badges[badgeIndex]));

		races.erase(races.begin() + raceIndex);
		badges.erase(badges.begin() + badgeIndex);
	}

	return rd;
}

int getIntegerInput() {//only allows integer input
	int x = 0;
	while (!(cin >> x)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input. Try Again: ";
	}
	return x;
}

void displayScoreboard() { //displays players in ascending order of total victory coins
	for (int i = 0; i < players.size(); i++) {
		cout << i << ". Player" << players[i].ID << endl;
	}
}

void addPlayer(int pID) {
	Player newPlayer(pID);
	newPlayer.giveCoins(1, 5);
	numCoins1 -= 5;
	players.push_back(newPlayer);
}

int main()
{
	cout << "Welcome to Smallworld.\n" << "Please type in the name of the map file to use.\n";
	cin >> mapName;

	gameMap.loadMap(mapName);

	while (!gameMap.isValid) {

		if (!gameMap.isValid) {
			cout << "\nThe map you have entered was invalid. Please try again.\n";
			cin >> mapName;
			gameMap.loadMap(mapName);
		}
	}

	setUpGamePieces();
	raceDeck = createRaceDeck();

	for (int i = 0; i < gameMap.numPlayers; i++) {
		addPlayer(i+1);
	}

	for(int i = 0; i < gameMap.numTurns; i++) {//loop for turn indicator (game turn marker)
		for (int j = 0; j < players.size(); j++) {
			playerAction = 0; //Reset player action each turn
			playerAction = 0;
			validAction = false;
			endTurn = false;

			cout << "----------------------------------" << endl;
			cout << "ROUND " << i + 1 << ": Player " << j + 1 << endl;
			cout << "----------------------------------" << endl;

			 do { //do-while loop for a player turn

				cout << "\nPlease select one of the following options: " << endl;
				cout << "1. List Region Connections" << endl;
				cout << "2. Pick a Race" << endl;
				cout << "3. Conquer a Region" << endl;
				cout << "4. View Player Summary Sheet" << endl;
				cout << "5. Display Game Bank Contents" << endl; 
				cout << "(6. Dice Rolling Facility)" << endl; //temporary option
				cout << "(7. End Turn)" << endl; //temporary option

				playerAction = getIntegerInput();

				//Map related action to see edges of whole map or individual region
				if (playerAction == 1) { 
					cout << "\n->List Region Connections: " << endl;
					cout << "1. List All Map Edges" << endl;
					cout << "2. List Connections of a Specific Region" << endl;
					cout << "Return to Options with Any Other Integer Value" << endl;

					playerAction2 = getIntegerInput();

					if (playerAction2 == 1) {
						gameMap.showAllEdges();
					}
					else if (playerAction2 == 2) {
						cout << "Enter Region ID: ";
						do {
							regionID = getIntegerInput();

							if (regionID > 0 && regionID <= gameMap.numRegions) {
								gameMap.showRegionConnections(regionID);
								validAction = true;
							}
							else {
								cout << "\nEntered Invalid Region ID. Please Try Again: ";
							}
							
						} while (!validAction);
					}
					else {
						cout << "This is an invalid action." << endl;
					}
					
				}
				//Race related action
				else if (playerAction == 2) {
					if (players[j].activeRace.isNull()) {
						int selectRace;

						cout << "\n->No Current Active Race. Select one from the following:" << endl;
						for (int r = 0; r < 6; r++) {
							cout << r + 1 << ". " << raceDeck[r].first.name << " (" << raceDeck[r].first.tokens << ") + " << raceDeck[r].second.name << " (" << raceDeck[r].second.tokens << ")" << endl;
						}
						selectRace = getIntegerInput();
						if (selectRace > 0 && selectRace <= 6) {
							players[j].picks_race(raceDeck[selectRace - 1]);
							raceDeck.erase(raceDeck.begin() + (selectRace - 1));//remove chosen combo from race deck
						}
						else {
							cout << "Invalid selection." << endl;
						}
					}
					else {
						cout << "\n->Active Race Already Selected." << endl;
					}
					
				}
				//Conquering related action
				else if (playerAction == 3) {
					int selectRegion;

					if (players[j].ownedRegionIDs.size() <= 0) {
						cout << "\n->No Current Owned Regions. Enter one of the following region IDs:" << endl;
						for (int sR = 0; sR < gameMap.mapRegions.size(); sR++) {
							if(gameMap.mapRegions[sR].isStart)
								cout << "Region " << gameMap.mapRegions[sR].ID << endl;
						}
					}
					else {
						cout << "\n->Select one of the following adjacent regions to the ones you own. Enter the region you wish to conquer by region ID:" << endl;
					}

					selectRegion = getIntegerInput();
					players[j].conquers(selectRegion - 1);
					
				}
				//Game statistics related action
				else if (playerAction == 4) {
					players[j].scores();
				}
				else if (playerAction == 5) {
					showGameBankContents();
				}
				else if (playerAction == 6) {
					int roll = players[j].diceFacility.roll();
					cout << "->\nYou have rolled a " << roll << "!" << endl;
				}
				else if (playerAction == 7) {
					endTurn = true;
				}
				else {
					cout << "This is an invalid action." << endl;
				}
			 } while (!endTurn);

			 players[j].countVictoryCoins(); //count coins at end of turn
		}
	}

	cout << "Game Over!" << endl;
	cout << "==================================" << endl;
	cout << "SCOREBOARD" << endl;
	cout << "==================================" << endl;

	void displayScoreboard();


    return 0;
}


