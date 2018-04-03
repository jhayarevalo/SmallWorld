// SmallWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <time.h>

#include "Map.h"
#include "Player.h"
#include "Game.h"

using namespace std;

//---OFFICIAL SMALL WORLD GAME CONTENTS
//VICTORY COINS
const int NUM_COINS1 = 35; 
const int NUM_COINS3 = 20; 
const int NUM_COINS5 = 24; 
const int NUM_COINS10 = 30;

//GAME PIECES
const int NUM_TROLLLAIRS = 10; 
const int NUM_FORTRESSES = 6;
const int NUM_MOUNTAINS = 9;
const int NUM_ENCAMPMENTS = 5;
const int NUM_HOLES = 2;
const int NUM_HEROES = 2;
const int NUM_DRAGONS = 1;

//RACE & LOST TRIBE TOKENS
const int NUM_AMAZONS = 15;
const int NUM_DWARVES = 8;
const int NUM_ELVES = 11;
const int NUM_GHOULS = 10;
const int NUM_GIANTS = 11;
const int NUM_HALFLINGS = 11;
const int NUM_HUMANS = 10;
const int NUM_ORCS = 10;
const int NUM_RATMEN = 13;
const int NUM_SKELETONS = 20;
const int NUM_SORCERERS = 18;
const int NUM_TRITONS = 11;
const int NUM_TROLLS = 10;
const int NUM_WIZARDS = 10;
const int NUM_TRIBES = 18;

//RACES (14)
Race amazonRace("Amazons", 6);
Race dwarfRace("Dwarves", 3);
Race elfRace("Elves", 6);
Race ghoulRace("Ghouls", 5);
Race giantRace("Giants", 6);
Race halflingRace("Halflings", 6);
Race humanRace("Humans", 5);
Race orcRace("Orcs", 5);
Race ratmanRace("Ratmen", 8);
Race skeletonRace("Skeletons", 6);
Race sorcererRace("Sorcerers", 5);
Race tritonRace("Tritons", 6);
Race trollRace("Trolls", 5);
Race wizardRace("Wizards", 5);

Race tribeRace("Tribe", 0); //lost tribes not part of the race deck

//BADGES (20)
Badge alchemistBadge("Alchemist", 4);
Badge berserkBadge("Berserk", 4);
Badge bivouackingBadge("Bivouacking", 5);
Badge commandoBadge("Commando", 4);
Badge diplomatBadge("Diplomat", 5);
Badge dragonMasterBadge("Dragon Master", 5);
Badge flyingBadge("Flying", 5);
Badge forestBadge("Forest", 4);
Badge fortifiedBadge("Fortified", 3);
Badge heroicBadge("Heroic", 5);
Badge hillBadge("Hill", 4);
Badge merchantBadge("Merchant", 2);
Badge mountedBadge("Mounted", 5);
Badge pillagingBadge("Pillaging", 5);
Badge seafaringBadge("Seafaring", 5);
Badge spiritBadge("Spirit", 5);
Badge stoutBadge("Stout", 4);
Badge swampBadge("Swamp", 4);
Badge underworldBadge("Underworld", 5);
Badge wealthyBadge("Wealthy", 4);

//---Game Variables
Game currentGame;
string mapName;
Map gameMap;
vector<Player> players;

bool validMap = false;
bool validAction;
bool endTurn;
bool diceRolled;

int numPlayers;
int playerAction;
int playerAction2;
int regionID;

//---Containers
//Available maps 
vector<string> mapDirectory = { "2player.txt", "3player.txt", "4player.txt", "5player.txt" };

//Races, Badges, Combos
vector<Race> races;
vector<Badge> badges;

vector<Race> discardedRaces;
vector<Badge> discardedBadges;

/* RACE DECK:
1) pair<Race,Badge> is the race x power combo
2) vector<Coin> contains the coins on top of each combo in the race deck
Race deck is composed of pairs of these 2 elements.
Used for discarded declined race x badge combos
*/
vector<pair<pair<Race, Badge>,vector<Coin>>> raceDeck;	

//Victory Coins
vector<Coin> coins1, coins3, coins5, coins10;

//Region Additions
vector<GamePiece> trollLairs, fortresses, mountains, encampments, holes, heroes, dragons;

//Race Tokens
vector<Token> amazons, dwarves, elves, ghouls, giants, halflings, humans, orcs, ratmen, skeletons, sorcerers, tritons, trolls, wizards, tribes;

//--Helper functions
void setUpGamePieces() {

	//Victory Coins
	for (int i = 0; i < NUM_COINS1; i++) {
		coins1.push_back(Coin(1));
	}
	for (int i = 0; i < NUM_COINS3; i++) {
		coins3.push_back(Coin(3));
	}
	for (int i = 0; i < NUM_COINS5; i++) {
		coins5.push_back(Coin(5));
	}
	for (int i = 0; i < NUM_COINS10; i++) {
		coins10.push_back(Coin(10));
	}

	//Game Pieces
	for (int i = 0; i < NUM_TROLLLAIRS; i++) {
		trollLairs.push_back(GamePiece("Troll Lair"));
	}
	for (int i = 0; i < NUM_FORTRESSES; i++) {
		fortresses.push_back(GamePiece("Fortress"));
	}
	for (int i = 0; i < NUM_MOUNTAINS; i++) {
		mountains.push_back(GamePiece("Mountain"));
	}
	for (int i = 0; i < NUM_ENCAMPMENTS; i++) {
		encampments.push_back(GamePiece("Encampment"));
	}
	for (int i = 0; i < NUM_HOLES; i++) {
		holes.push_back(GamePiece("Hole-in-the-Ground"));
	}
	for (int i = 0; i < NUM_HEROES; i++) {
		heroes.push_back(GamePiece("Hero"));
	}
	for (int i = 0; i < NUM_DRAGONS; i++) {
		dragons.push_back(GamePiece("Dragon"));
	}

	races.push_back(amazonRace);
	races.push_back(dwarfRace);
	races.push_back(elfRace);
	races.push_back(ghoulRace);
	races.push_back(giantRace);
	races.push_back(halflingRace);
	races.push_back(humanRace);
	races.push_back(orcRace);
	races.push_back(ratmanRace);
	races.push_back(skeletonRace);
	races.push_back(sorcererRace);
	races.push_back(tritonRace);
	races.push_back(trollRace);
	races.push_back(wizardRace); //vector used for race deck

	//20 power badges
	badges.push_back(alchemistBadge);
	badges.push_back(berserkBadge);
	badges.push_back(bivouackingBadge);
	badges.push_back(commandoBadge);
	badges.push_back(diplomatBadge);
	badges.push_back(dragonMasterBadge);
	badges.push_back(flyingBadge);
	badges.push_back(forestBadge);
	badges.push_back(fortifiedBadge);
	badges.push_back(heroicBadge);
	badges.push_back(hillBadge);
	badges.push_back(merchantBadge);
	badges.push_back(mountedBadge);
	badges.push_back(pillagingBadge);
	badges.push_back(seafaringBadge);
	badges.push_back(spiritBadge);
	badges.push_back(stoutBadge);
	badges.push_back(swampBadge);
	badges.push_back(underworldBadge);
	badges.push_back(wealthyBadge); //vector used for race deck

	//Race & Lost Tribe Tokens
	for (int i = 0; i < NUM_AMAZONS; i++) {
		amazons.push_back(Token(amazonRace));
	}
	for (int i = 0; i < NUM_DWARVES; i++) {
		dwarves.push_back(Token(dwarfRace));
	}
	for (int i = 0; i < NUM_ELVES; i++) {
		elves.push_back(Token(elfRace));
	}
	for (int i = 0; i < NUM_GHOULS; i++) {
		ghouls.push_back(Token(ghoulRace));
	}
	for (int i = 0; i < NUM_GIANTS; i++) {
		giants.push_back(Token(giantRace));
	}
	for (int i = 0; i < NUM_HALFLINGS; i++) {
		halflings.push_back(Token(halflingRace));
	}
	for (int i = 0; i < NUM_HUMANS; i++) {
		humans.push_back(Token(humanRace));
	}
	for (int i = 0; i < NUM_ORCS; i++) {
		orcs.push_back(Token(orcRace));
	}
	for (int i = 0; i < NUM_RATMEN; i++) {
		ratmen.push_back(Token(ratmanRace));
	}
	for (int i = 0; i < NUM_SKELETONS; i++) {
		skeletons.push_back(Token(skeletonRace));
	}
	for (int i = 0; i < NUM_SORCERERS; i++) {
		sorcerers.push_back(Token(sorcererRace));
	}
	for (int i = 0; i < NUM_TRITONS; i++) {
		tritons.push_back(Token(tritonRace));
	}
	for (int i = 0; i < NUM_TROLLS; i++) {
		trolls.push_back(Token(trollRace));
	}
	for (int i = 0; i < NUM_WIZARDS; i++) {
		wizards.push_back(Token(wizardRace));
	}
	for (int i = 0; i < NUM_TRIBES; i++) {
		tribes.push_back(Token(tribeRace)); //not part of race deck
	}
}

int totalCoins(vector<Coin> coinVector) {
	int total = 0;

	for (int i = 0; i < coinVector.size(); i++) {
		if (coinVector[i].getValue() == 1) {
			total += 1;
		}
		else if (coinVector[i].getValue() == 3) {
			total += 3;
		}
		else if (coinVector[i].getValue() == 5) {
			total += 5;
		}
		else if (coinVector[i].getValue() == 10) {
			total += 10;
		}
	}

	return total;
}

void showGameBankContents() {
	cout << endl << "############################################" << endl;
	cout << "Bank Contents" << endl;
	cout << "############################################" << endl;
	cout << "---------------------------" << endl;
	cout << "Victory Coins" << endl;
	cout << "---------------------------" << endl;
	cout << coins1.size() << "x '1 Coins'" << endl;
	cout << coins3.size() << "x '3 Coins'" << endl;
	cout << coins5.size() << "x '5 Coins'" << endl;
	cout << coins10.size() << "x '10 Coins'" << endl;

	cout << endl;
	cout << "---------------------------" << endl;
	cout << "Race Deck" << endl;
	cout << "---------------------------" << endl;
	for (int r = 0; r < 6; r++) {
		pair<Race, Badge> * combo;
		vector<Coin> * comboCoins;

		combo = &raceDeck[r].first;
		comboCoins = &raceDeck[r].second;

		cout << "[+" << totalCoins(*comboCoins) << "]   ";
		cout << r + 1 << ". " << combo->first.getName() << " (" << combo->first.getTokens() << ") + " << combo->second.getName() << " (" << combo->second.getTokens() << ")" << endl;
	}

	cout << endl;
	cout << "---------------------------" << endl;
	cout << "Race & Lost Tribe Tokens" << endl;
	cout << "---------------------------" << endl;
	cout << amazons.size() << "x 'Amazon Tokens'" << endl; 
	cout << dwarves.size() << "x 'Dwarf Tokens'" << endl;
	cout << elves.size() << "x 'Elf Tokens'" << endl;
	cout << ghouls.size() << "x 'Ghoul Tokens'" << endl;
	cout << giants.size() << "x 'Giant Tokens'" << endl;
	cout << halflings.size() << "x 'Halfling Tokens'" << endl;
	cout << humans.size() << "x 'Human Tokens'" << endl;
	cout << orcs.size() << "x 'Orc Tokens'" << endl;
	cout << ratmen.size() << "x 'Ratmen Tokens'" << endl;
	cout << skeletons.size() << "x 'Skeleton Tokens'" << endl;
	cout << sorcerers.size() << "x 'Sorcerer Tokens'" << endl;
	cout << tritons.size() << "x 'Triton Tokens'" << endl;
	cout << trolls.size() << "x 'Troll Tokens'" << endl;
	cout << wizards.size() << "x 'Wizard Tokens'" << endl;
	cout << tribes.size() << "x 'Lost Tribe Tokens'" << endl;

	cout << endl;
	cout << "---------------------------" << endl;
	cout << "Game Pieces" << endl;
	cout << "---------------------------" << endl;
	cout << trollLairs.size() << "x 'Troll Lairs'" << endl;
	cout << fortresses.size() << "x 'Fortresses'" << endl;
	cout << mountains.size() << "x 'Mountains'" << endl;
	cout << holes.size() << "x 'Holes-in-the-Ground'" << endl;
	cout << heroes.size() << "x 'Heroes'" << endl;
	cout << dragons.size() << "x 'Dragon'" << endl;

	cout << "############################################" << endl << endl;
}

vector<pair<pair<Race, Badge>,vector<Coin>>> createRaceDeck() {

	srand((unsigned)time(0));

	int numRaces = races.size();
	int raceIndex;
	int badgeIndex;

	vector<pair<pair<Race, Badge>,vector<Coin>>> rd;

	for (int i = 0; i < numRaces; i++) {
		pair<Race, Badge> combo;
		vector<Coin> comboCoins;

		raceIndex = rand() % races.size();
		badgeIndex = rand() % badges.size();

		combo = pair<Race, Badge>(races[raceIndex], badges[badgeIndex]);
		pair<pair<Race, Badge>, vector<Coin>> raceDeckEntry;

		raceDeckEntry.first = combo;
		raceDeckEntry.second = comboCoins;

		rd.push_back(raceDeckEntry);

		//remove used race and badge choices for future combos
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
		cout << i << ". Player" << players[i].getID() << endl;
	}
}

void giveCoins(vector<Coin> * coinVector, Player * p, int amount) {

	int size = coinVector->size();
	int value = coinVector->front().getValue();

	if (size < amount) {
		cout << "\nBank is missing " << size - amount << " x " << value << " coin." << endl;
	}
	else {
		for (int i = 0; i < amount; i++) {
			p->addCoin(coinVector->front());
			coinVector->pop_back();
		}
	}
}

void placeGamePiece(vector<GamePiece> * gamePieceVector, Region * r) {
	int size = gamePieceVector->size();
	GamePiece gamePiece = gamePieceVector->front();

	if (size < 1) {
		cout << "\nThere are no more " << gamePiece.getName() <<" game pieces available." << endl;
	}
	else {
			r->addGamePiece(gamePiece);
			gamePieceVector->pop_back();
		}
}

void placeToken(vector<Token> * tokenVector, Region * r) {
	int size = tokenVector->size();
	Token token = tokenVector->front();

	if (size < 1) {
		cout << "\nThere are no more " << token.getRace().getName() << " race tokens available." << endl;
	}
	else {
		r->addToken(token);
		tokenVector->pop_back();
	}
}

vector<Token> * getTokenVector(Race r) {
	if (r.equals(amazonRace)) {
		return &amazons;
	}
	else if (r.equals(dwarfRace)) {
		return &dwarves;
	}
	else if (r.equals(elfRace)) {
		return &elves;
	}
	else if (r.equals(ghoulRace)) {
		return &ghouls;
	}
	else if (r.equals(giantRace)) {
		return &giants;
	}
	else if (r.equals(halflingRace)) {
		return &halflings;
	}
	else if (r.equals(humanRace)) {
		return &humans;
	}
	else if (r.equals(orcRace)) {
		return &orcs;
	}
	else if (r.equals(ratmanRace)) {
		return &ratmen;
	}
	else if (r.equals(skeletonRace)) {
		return &skeletons;
	}
	else if (r.equals(sorcererRace)) {
		return &sorcerers;
	}
	else if (r.equals(tritonRace)) {
		return &tritons;
	}
	else if (r.equals(trollRace)) {
		return &trolls;
	}
	else if (r.equals(wizardRace)) {
		return &wizards;
	}
	else if (r.equals(tribeRace)) {
		return &tribes;
	}
}

vector<GamePiece> * getGamePieceVector(string n) {
	if (n == "Troll Lair") {
		return &trollLairs;
	}
	else if (n == "Fortress") {
		return &fortresses;
	}
	else if (n == "Mountain") {
		return &mountains;
	}
	else if (n == "Encampment") {
		return &encampments;
	}
	else if (n == "Hole-in-the-Ground") {
		return &holes;
	}
	else if (n == "Hero") {
		return &heroes;
	}
	else if (n == "Dragon") {
		return &dragons;
	}
}

void returnToken(Region * r) {
	Token t = r->getTokens().front();
	Race rT = t.getRace();
	vector<Token> * tokenVector = getTokenVector(rT);
	tokenVector->push_back(Token(rT));//player and region id are reset (default null)
	r->removeToken();
}

void returnGamePiece(GamePiece g) {
	string n = g.getName();
	vector<GamePiece> * gamePieceVector = getGamePieceVector(n);
	gamePieceVector->push_back(GamePiece(n));
}

Player* findPlayerByID(int pID) {
	for (int i = 0; i < players.size(); i++) {
		if (players[i].getID() == pID) {
			return &players[i];
		}
	}
}

bool payBank(Player * p, int total) {
	p->countVictoryCoins();
	int remaining = total;
	if (p->getVictoryCoins() >= total) {
		while (remaining > 0) {
			if (remaining >= 10 && p->getCoins10().size() > 0) {
				p->removeCoin(Coin(10));
				coins10.push_back(Coin(10));
				remaining -= 10;
			}
			else if (remaining >= 5 && p->getCoins5().size() > 0) {
				p->removeCoin(Coin(5));
				coins5.push_back(Coin(5));
				remaining -= 5;
			}
			else if (remaining >= 3 && p->getCoins3().size() > 0) {
				p->removeCoin(Coin(3));
				coins3.push_back(Coin(3));
				remaining -= 3;
			}
			else if (p->getCoins1().size() > 0) {
				p->removeCoin(Coin(1));
				coins1.push_back(Coin(1));
				remaining -= 1;
			}
			//make change
			else {
				//changing a 10 coin
				if (p->getCoins10().size() > 0) {

					p->removeCoin(Coin(10));
					coins10.push_back(Coin(10));

					if (remaining >= 5) {
						for (int i = 0; i < 2; i++) {
							p->addCoin(Coin(5));
							coins5.pop_back();
						}
					}
					else if (remaining >= 3) {
						for (int i = 0; i < 3; i++) {
							p->addCoin(Coin(3));
							coins3.pop_back();
						}
						p->addCoin(Coin(1));
						coins1.pop_back();
					}
					else {
						for (int i = 0; i < 3; i++) {
							coins1.push_back(Coin(1));
						}
					}
				}
				//changing a 5 coin
				else if (coins5.size() > 0) {

					p->removeCoin(Coin(5));
					coins5.push_back(Coin(5));

					if (remaining >= 3) {
						p->addCoin(Coin(3));
						coins3.pop_back();
						for (int i = 0; i < 2; i++) {
							p->addCoin(Coin(3));
							coins3.pop_back();
						}
					}
					else {
						for (int i = 0; i < 5; i++) {
							p->addCoin(Coin(1));
							coins1.pop_back();
						}
					}
				}
				//changing a 3 coin
				else if (coins3.size() > 0) {

					p->addCoin(Coin(3));
					coins3.pop_back();

					for (int i = 0; i < 3; i++) {
						p->addCoin(Coin(1));
						coins1.pop_back();
					}
				}
			}
		}
		return true;
	}
	else {
		cout << "Insufficient funds. " << endl;
		return false;
	}
}

void payPlayer(Player * p, int total){
	int remaining = total;
	while(remaining > 0){
		if (remaining >= 10) {
			p->addCoin(Coin(10));
			coins10.pop_back();
			remaining -= 10;
		}
		else if (remaining >= 5) {
			p->addCoin(Coin(5));
			coins5.pop_back();
			remaining -= 5;
		}
		else if (remaining >= 3) {
			p->addCoin(Coin(3));
			coins3.pop_back();
			remaining -= 3;
		}
		else{
			p->addCoin(Coin(1));
			coins1.pop_back();
			remaining -= 1;
		}
	}
}

//Player function is in driver because it needs access to bank coins
void Player::scores() {
	int occupiedRegions = getOwnedRegions().size();
	payPlayer(this, occupiedRegions);

	int raceBadgeBenefits = getRaceBadgeBenefits();
	payPlayer(this, raceBadgeBenefits);

	cout << "Player " << getID() << " has scored " << occupiedRegions + raceBadgeBenefits << " Coins!" << endl;
}

//--DRIVER
int main()
{
	//---GAME BOARD SET UP
	//Set up map
	cout << "Welcome to Smallworld.\n" << "\nPlease type in the name of the map file to use. Here is a list of maps readily available for use:\n\n";
	for (int i = 0; i < mapDirectory.size(); i++) {
		cout << mapDirectory[i] << endl;
	}
	cout << endl;
	cin >> mapName;

	gameMap.loadMap(mapName);

	while (!gameMap.isValid()) {

		if (!gameMap.isValid()) {
			cout << "\nThe map you have entered was invalid. Please try again.\n";
			cin >> mapName;
			gameMap.loadMap(mapName);
		}
	}

	//Set up custom players
	cout << "\nWould you like to modify the number of players on this map? (Y/N)\n";
	char modifyPlayers = 'N';
	cin >> modifyPlayers;

	if (modifyPlayers == 'Y' || modifyPlayers == 'y') {
		cout << "\nPlease enter the number of players (2-5).\n";
		do {
			numPlayers = getIntegerInput();
			if (numPlayers < 2 || numPlayers > 5) {
				cout << "Please enter a number within the valid range (2-5).\n";
			}
		} while (numPlayers < 2 || numPlayers > 5);
		gameMap.setNumPlayers(numPlayers);
	}

	//Set up game pieces
	setUpGamePieces();
	raceDeck = createRaceDeck();

	//Set Lost Tribe tokens on map
	for (int r = 0; r < gameMap.mapRegions.size(); r++) {
		if (gameMap.mapRegions[r]->hasTribe()) {
			placeToken(&tribes, gameMap.mapRegions[r]);
			cout << "Setting tribe token on region " << gameMap.mapRegions[r]->getID() << endl;
		}
		if (gameMap.mapRegions[r]->hasMountain()) {
			placeGamePiece(&mountains, gameMap.mapRegions[r]);
			cout << "Setting mountain piece on region " << gameMap.mapRegions[r]->getID() << endl;
		}
	}

	//Give players starting coins
	for (int i = 0; i < gameMap.getNumPlayers(); i++) {
		Player newPlayer(i+1);//ID starts at 1
		giveCoins(&coins1, &newPlayer, 5);
		players.push_back(newPlayer);
	}

	//---GAME LOOP
	for(int i = 0; i < gameMap.getNumTurns(); i++) {//loop for turn indicator (game turn marker)
		for (int j = 0; j < players.size(); j++) {
			playerAction = 0; //Reset player action each turn
			playerAction = 0;
			validAction = false;
			endTurn = false;
			diceRolled = false;

			cout << "\n============================================" << endl;
			cout << "ROUND " << i + 1 << ": Player " << j + 1 << endl;
			cout << "============================================" << endl;

			 do { //=== PLAYER TURN ===

				 //First Turn
				 if (i == 0) {
					 bool canConquer = true;
					 cout << players[j].getActiveRaceTokens().size() << endl;

					 if (players[j].getActiveRaceTokens().size() == 0 && diceRolled) {
						canConquer = false;
					 }

					 if (players[j].getActiveRace().isNull()) {
						 playerAction = 1;
					 }	
					 else {
						 cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						 cout << "Please select one of the following options:" << endl;
						 cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						 cout << "Player" << endl;
						 cout << "-----------" << endl;
						 if (!diceRolled && canConquer) {
							 cout << "1. Conquer a Region" << endl;
						 }
						 else {
							 cout << "1. Redeploy Troops" << endl;
						 }
						 cout << "2. View Player Summary Sheet" << endl;

						 cout << endl;
						 cout << "Game Board" << endl;
						 cout << "-----------" << endl;
						 cout << "3. Display Map Contents" << endl;
						 cout << "4. List Region Connections" << endl;
						 cout << "5. Display Game Bank Contents" << endl;
						 //cout << "(6. Dice Rolling Facility)" << endl; //temporary option
						 cout << endl;
						 cout << "6. End Turn" << endl; 

						 playerAction = getIntegerInput();
						 if (playerAction == 1) {
							 if (!diceRolled) {
								 playerAction = 2; //conquer
							 }
							 else{
								 playerAction = 4; //redeploy
							 }
						 }
						 else if(playerAction > 1){
							 playerAction += 4; //shifted up by 2 for last 4 player actions
						 }
					 }
				 }

				 //Following Turns
				 else {
					 cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					 cout << "Please select one of the following options:" << endl;
					 cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					 cout << "Player" << endl;
					 cout << "-----------" << endl;
					 cout << "1. Choose a New Race" << endl;
					 if (!diceRolled) {
						 cout << "2. Conquer a Region" << endl;
						 cout << "3. Take Back Troops" << endl;
					 }
					 else {
						 cout << "2. - \n";
						 cout << "3. - \n";//remove options to conquer and take back once roll dice
					 }
					 cout << "4. Redeploy Troops" << endl;
					 cout << "5. Abandon a Region" << endl;
					 cout << "6. View Player Summary Sheet" << endl;
				
					 cout << endl;
					 cout << "Game Board" << endl;
					 cout << "-----------" << endl;
					 cout << "7. Display Map Contents" << endl;
					 cout << "8. List Region Connections" << endl;
					 cout << "9. Display Game Bank Contents" << endl;

					 //cout << "(7. Dice Rolling Facility)" << endl; //temporary option
					 cout << endl;
					 cout << "10. End Turn" << endl; 

					 do {
						 playerAction = getIntegerInput();
						 if ((playerAction == 2 || playerAction == 3) && diceRolled) {
							 cout << "Cannot conquer or take back troops once the reinforcement dice has been rolled." << endl;
						 }
					 } while ((playerAction == 2 || playerAction == 3) && diceRolled);
				 }

				 //--- RACE RELATED ACTION ---
				 if (playerAction == 1) {
					 bool selectingRace = true;
					 char declineChoice = 'N';

					 //First turn
					 if (players[j].getActiveRace().isNull()) {
						 cout << "\nWelcome, Player " << j + 1 << "!\nSelect a Race and Special Power combo from one of the following:" << endl;
						 cout << "Choosing at the top of the deck is free. Otherwise, a coin must be dropped on each skipped combo. Selecting a combo with coins on it will add those coins to your inventory.\n\n";
					 }

					 //Decline Race
					 else {

						 cout << "\n->Your current Race and Special Power combo is " << players[j].getActiveRace().getName() << " (" << players[j].getActiveRace().getTokens() << ") + " << players[j].getActiveBadge().getName() << " (" << players[j].getActiveBadge().getTokens() << ")" << endl;
						 cout << "Would you like to put this race in decline and select a new active Race and Special Power combo? (Y/N)\n";

						 cin >> declineChoice;

						 if (declineChoice != 'Y' && declineChoice != 'y') {
							 selectingRace = false;
						 }
					 }

					 //--Race Deck
					 if (selectingRace) { //applies for first turn or when player decides to decline current active race
						 int selectRace;

						 //Display Race Deck
						 for (int r = 0; r < 6; r++) {
							 pair<Race, Badge> * combo;
							 vector<Coin> * comboCoins;

							 combo = &raceDeck[r].first;
							 comboCoins = &raceDeck[r].second;

							 cout << "[+" << totalCoins(*comboCoins) << "]   ";
							 cout << r + 1 << ". " << combo->first.getName() << " (" << combo->first.getTokens() << ") + " << combo->second.getName() << " (" << combo->second.getTokens() << ")\n";
						 }

						 //Selecting Race
						 selectRace = getIntegerInput();

						 if (selectRace > 0 && selectRace <= 6) {
							 if (players[j].getCoins1().size() >= selectRace - 1) {
								 pair<Race, Badge> * chosenCombo;
								 vector<Coin> * chosenComboCoins;
								 int numRaceTokens;

								 chosenCombo = &raceDeck[selectRace - 1].first;
								 chosenComboCoins = &raceDeck[selectRace - 1].second;
								 numRaceTokens = chosenCombo->first.getTokens() + chosenCombo->second.getTokens();

								 //--Managing declined race tokens
								 if (!players[j].getActiveRace().isNull()) {

									 //Keep only one token placed on regions & return the rest to bank
									 for (int g = 0; g < players[j].getOwnedRegions().size(); g++) {
										 Region * reg = players[j].getOwnedRegions()[g];

										 while (reg->getTokens().size() > 1) {
											 returnToken(reg);
										 }
									 }

									 //Return the rest of tokens in hand
									 for (int t = 0; t < players[j].getActiveRaceTokens().size(); t++) {

									 }
								 }

								 //Adding old declined race & badge to discard piles
								 if (!players[j].getDeclinedRace().isNull()) {
									 Race * declinedRace;
									 Badge * declinedBadge;

									 declinedRace = &players[j].getDeclinedRace();
									 declinedBadge = &players[j].getDeclinedBadge();

									 discardedRaces.push_back(Race(declinedRace->getName(), declinedRace->getTokens()));
									 discardedBadges.push_back(Badge(declinedBadge->getName(), declinedBadge->getTokens()));
								 }

								 //Sets players active race
								 players[j].picks_race(*chosenCombo);

								 //Place coin on race x power combo for every "skipped-over" combo
								 for (int s = 0; s < selectRace - 1; s++) {
									 players[j].removeCoin(Coin(1));
									 raceDeck[s].second.push_back(Coin(1));
								 }

								 //Transfer coins ontop of combo to player inventory
								 for (int c = 0; c < raceDeck[selectRace - 1].second.size(); c++) {
									 players[j].addCoin(Coin(chosenComboCoins->front().getValue()));
									 chosenComboCoins->pop_back();
								 }

								 //Give player race tokens
								 vector<Token> * tPtr;
								 tPtr = getTokenVector(chosenCombo->first);
								 for (int t = 0; t < numRaceTokens; t++) {
									 if (tPtr->size() > 0) {
										 players[j].addActiveRaceToken(Token(tPtr->front().getRace(), players[j].getID(), NULL));
										 tPtr->pop_back();
									 }
									 else {
										 cout << "Bank has been depleted of " << chosenCombo->first.getName() << " tokens." << endl;
										 break;
									 }
								 }

								 raceDeck.erase(raceDeck.begin() + (selectRace - 1));//remove chosen combo from race deck

								//If chose to decline race, turn is ended
								 if (declineChoice == 'Y' || declineChoice == 'y') {
									 //TODO: Add Scores
									 endTurn = true;
								 }

							 }
							 else {
								 cout << "You do not have enough coins to select this race." << endl;
							 }
						 }
						 else {
							 cout << "Invalid selection." << endl;
						 }
					 }
				 }

				//--- CONQUERING RELATED ACTION ---
				else if (playerAction == 2 && players[j].getActiveRaceTokens().size() > 0) {
					int selectRegion;
					Region * conquerRegion;
					vector<Token> * regionTokens;
					vector<GamePiece> * regionGamePieces;
					int conquerCost;

					bool beginConquest = false;

					char rollDice = 'N';

					Player * challenger;

					//First conquest
					if (players[j].getOwnedRegions().size() <= 0) {
						cout << "\n->No Current Owned Regions. Enter one of the following region IDs:" << endl;
						for (int sR = 0; sR < gameMap.mapRegions.size(); sR++) {
							if (gameMap.mapRegions[sR]->isStart()) {
								gameMap.mapRegions[sR]->displayContentsInline();
								cout << endl;
							}
						}
						
						do {
							selectRegion = getIntegerInput();
							conquerRegion = gameMap.findRegionByID(selectRegion);
							if (!conquerRegion->isStart()) {
								cout << "Invalid start region chosen. Try again. ";
							}
							else {
								beginConquest = true;
							}
						} while (!conquerRegion->isStart());

					}
					//Adjacent regions to conquer
					else{
						cout << "\n->Select one of the following adjacent regions to the ones you own. Enter the region you wish to conquer by region ID:" << endl;
						for (int o = 0; o < players[j].getOwnedRegions().size(); o++) {
							gameMap.showConquerableRegions(players[j].getOwnedRegions()[o]);
						}
							selectRegion = getIntegerInput();
							conquerRegion = gameMap.findRegionByID(selectRegion);
							if (!gameMap.isConquerable(conquerRegion, &players[j])) {
								cout << "Cannot conquer this region." << endl;
							}
							else {
								beginConquest = true;
							}
					}

					//Conquest algorithm
					if (beginConquest) {

						regionTokens = &conquerRegion->getTokens();
						regionGamePieces = &conquerRegion->getGamePieces();

						conquerCost = conquerRegion->getConquerCost();
						cout << "Region " << conquerRegion->getID() << " costs " << conquerCost << " Race Tokens to conquer." << endl;

						//Conquering Region
						if (conquerRegion->getPlayerID() == players[j].getID()) {
							cout << "You already own this region." << endl;
						}
						else if (players[j].getActiveRaceTokens().size() >= conquerCost) { //if player has enough coins

							if (conquerRegion->getPlayerID() != NULL) { //battle player
								challenger = findPlayerByID(conquerRegion->getPlayerID());

								while (regionTokens->size() > 1) {
									Token giveBack(challenger->getActiveRace());
									challenger->addActiveRaceToken(giveBack); //return all except 1 to challenged player's hand
									regionTokens->pop_back();
								}
								returnToken(conquerRegion);//return 1 to bank storage
							}
							else if (conquerRegion->getTokens().size() > 0) {//lost tribe
								returnToken(conquerRegion);
								conquerRegion->setTribe(false);
							}

								players[j].conquers(conquerRegion);

								//placing player race tokens on region
								for (int t = 0; t < conquerCost; t++) {
									players[j].placeActiveToken(conquerRegion);
								}
						}
						//Roll reinforcement dice
						else if(players[j].getActiveRaceTokens().size() > 0 && !diceRolled){ //need to have at least 1 token
							cout << "You currently do not have enough tokens to conquer this region. Would you like to roll the reinforcement die and try to conquer it? (Y/N)" << endl;
							cin >> rollDice;

							if (rollDice == 'Y' || rollDice == 'y') {
								int roll = players[j].diceFacility.roll();
								cout << "\n->You have rolled a " << roll << "!" << endl;

								if (roll + players[j].getActiveRaceTokens().size() >= conquerCost) {
									players[j].conquers(conquerRegion);

									for (int t = 0; t < players[j].getActiveRaceTokens().size()+1; t++) {
										players[j].placeActiveToken(conquerRegion);
									}
								}
								diceRolled = true;//final conquest
							}
						}
					}
					
				}
				else if (playerAction == 2 && players[j].getActiveRaceTokens().size() <= 0) {
					cout << "No race tokens left. " << endl;
				}
				//--- TAKING BACK RELATED ACTION ---
				else if (playerAction == 3) {
					char takeBack = 'N';
					int amountTakeBack;

					cout << "Here is a summary of your conquests.\n\nOwned Regions:" << endl;
					for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {

						players[j].getOwnedRegions()[r]->displayContentsInline();
						cout << endl;
					}
					cout << "\nActive Race Tokens in Hand: " << players[j].getActiveRaceTokens().size() << endl;

					cout << "Would you like to take back some tokens from the regions you own? (Y/N)" << endl;
					cin >> takeBack;

					if (takeBack == 'Y' || takeBack == 'y') {
						for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {
							cout << "Region " << players[j].getOwnedRegions()[r]->getID() << ": ";
							do {
								amountTakeBack = getIntegerInput();
								if (amountTakeBack >= players[j].getOwnedRegions()[r]->getTokens().size()) {
									cout << "Must leave at least one token in this owned region. " << endl;
									cout << "Region " << players[j].getOwnedRegions()[r]->getID() << ": ";
								}
							} while (amountTakeBack >= players[j].getOwnedRegions()[r]->getTokens().size());

							for (int b = 0; b < amountTakeBack; b++) {
								players[j].takeMapToken(players[j].getOwnedRegions()[r]);
							}
						}
					}
				}

				//--- REDEPLOYMENT RELATED ACTION ---
				else if (playerAction == 4) {
					int totalTokens = 0;
					char redeploy = 'N';
					bool tryAgain = true;
					int amountRedeploy;
					int sum = 0;

					cout << "Here is a summary of your conquests.\n\nOwned Regions:" << endl;
					for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {

						players[j].getOwnedRegions()[r]->displayContentsInline();
						cout << endl;
						totalTokens += players[j].getOwnedRegions()[r]->getTokens().size();
					}
					cout << "\nActive Race Tokens in Hand: " << players[j].getActiveRaceTokens().size() << endl;
					totalTokens += players[j].getActiveRaceTokens().size();

					while (players[j].getActiveRaceTokens().size() > 0) {
						int deployRegionID;
						cout << "\nPlease select one of your owned regions to deploy a token in hand: ";
						
						deployRegionID = getIntegerInput();
						Region * deployRegion = gameMap.findRegionByID(deployRegionID);
						if (players[j].ownsRegion(deployRegion)) {
							players[j].placeActiveToken(deployRegion);
							cout << "You have deployed a token to region " << deployRegion->getID() << endl;
						}
						else {
							cout << "You do not own that region. " << endl;
						}
					}

					cout << "\nWould you like to redeploy your tokens? (Y/N)" << endl;
					cin >> redeploy;

					if (redeploy == 'Y' || redeploy == 'y') {
						cout << "Please select how you would like to redeploy your " << totalTokens <<  " tokens on the map. " << endl;
						while (tryAgain) {
							vector<int> compareTokens;
							for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {
								cout << "Region " << players[j].getOwnedRegions()[r]->getID() << ": ";
								do {
									amountRedeploy = getIntegerInput();
									if (amountRedeploy < 1) {
										cout << "Must leave at least one token in this owned region. " << endl;
										cout << "Region " << players[j].getOwnedRegions()[r]->getID() << ": ";
									}
									else if (amountRedeploy >  players[j].getOwnedRegions()[r]->getTokens().size()) {
										cout << "Please ensure that you have enough free tokens to reassign to this region. " << endl;
									}
								} while (amountRedeploy < 1 && amountRedeploy > players[j].getActiveRaceTokens().size());
								compareTokens.push_back(amountRedeploy);
							}
							for (int c = 0; c < compareTokens.size(); c++) {
								sum += compareTokens[c];
							}
							if (sum != totalTokens) {
								cout << "\nTroops incorrectly redistributed. Sum of tokens = " << sum << ". Try again." << endl;
								vector<int> compareTokens;
								sum = 0;
							}
							else {
								for (int c = 0; c < compareTokens.size(); c++) {
									if (players[j].getOwnedRegions()[c]->getTokens().size() > compareTokens[c]) {
										players[j].takeMapToken(players[j].getOwnedRegions()[c]);
										cout << "Token from region " << players[j].getOwnedRegions()[c]->getID() << " has been returned to player. " << endl;
									}
									else if (players[j].getOwnedRegions()[c]->getTokens().size() < compareTokens[c] && players[j].getActiveRaceTokens().size() > 0) {
											players[j].placeActiveToken(players[j].getOwnedRegions()[c]);
									}
								}
								cout << "\nTroops have been redistributed as follows: " << endl;
								for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {
									players[j].getOwnedRegions()[r]->displayContentsInline();
									cout << endl;
								}
								tryAgain = false;
							}
						}
					}
					else {
						if (players[j].getActiveRaceTokens().size() > 0) {
							cout << "You must place all tokens in hand on regions that you own. " << endl;
						}
						endTurn = true; //end turn
					}
				}
				
				//--- ABANDONING REGION ---
				else if (playerAction == 5) {
					char abandon = 'N';
					int regionID;
					Region * abandonedRegion;
					cout << "Owned Regions:" << endl;
					for (int r = 0; r < players[j].getOwnedRegions().size(); r++) {
						players[j].getOwnedRegions()[r]->displayContentsInline();
						cout << endl;
					}
					cout << "Would you like to abandon one of these regions and collect your active race tokens? (Y/N)" << endl;
					if (abandon == 'Y' || abandon == 'y') {
						do {
							regionID = getIntegerInput();
							abandonedRegion = gameMap.findRegionByID(regionID);

							if (!players[j].ownsRegion(abandonedRegion)) {
								cout << "You do not own this region." << endl;
							}

						} while (!players[j].ownsRegion(abandonedRegion));
						players[j].abandonRegion(abandonedRegion);
					}
				}
				//--- GAME STATS RELATED ACTION ---
				else if (playerAction == 6) {
					players[j].summarySheet();
				}

				//--- MAP CONTENTS RELATED ACTION ---
				else if (playerAction == 7) {
					gameMap.showMapContents();
				}

				//--- EDGES RELATED ACTION ---
				else if (playerAction == 8) {
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

							if (regionID > 0 && regionID <= gameMap.getNumRegions()) {
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
				
				//--- BANK CONTENTS RELATED ACTION ---
				else if (playerAction == 9) {
					showGameBankContents();
				}

				/*
				//--- DICE RELATED ACTION (TEMP) ---
				else if (playerAction == 7) {
					int roll = players[j].diceFacility.roll();
					cout << "\n->You have rolled a " << roll << "!" << endl;
				}*/

				//--- END TURN ---
				else if (playerAction == 10) {
					endTurn = true;
				}
				else {
					cout << "This is an invalid action." << endl;
				}

				// Calcute score at the end of round
				if (endTurn) {
					players[j].scores();
				}
			 } while (!endTurn);

			 players[j].countVictoryCoins(); //count coins at end of turn
		}
	}

	cout << "Game Over!" << endl;
	cout << "============================================" << endl;
	cout << "SCOREBOARD" << endl;
	cout << "============================================" << endl;

	void displayScoreboard();


    return 0;
}


