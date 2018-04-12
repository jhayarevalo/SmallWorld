#pragma once

#include <stack>

#include "Region.h"
#include "Dice.h"
#include "Race.h"
#include "Badge.h"
#include "Coin.h"
#include "Token.h"
#include "Strategy.h"

class Player
{
private:
	int ID;
	Strategy * strategy;

	//Victory Coins
	vector<Coin> coins1;
	vector<Coin> coins3;
	vector<Coin> coins5;
	vector<Coin> coins10;
	int victoryCoins;

	//Game Tokens
	vector<Token> activeRaceTokens;

	//Game Pieces
	vector<GamePiece> gamePieces;

	vector<Region*> ownedRegions;

	Race activeRace;
	Race declinedRace;

	Badge activeBadge;
	Badge declinedBadge;

public:
	Dice diceFacility;

	Player(int pID);
	Player(int pID, Strategy *initS);

	void addCoin(Coin c);
	void removeCoin(Coin c);

	void placeActiveToken(Region * r);
	void takeMapToken(Region * r);
	void takeAllMapTokens();

	void addActiveRaceToken(Token t);

	void placeGamePiece(string n, Region * r);
	void addGamePiece(GamePiece g);
	void removeGamePieces(string n);

	//Assignment Required Functions
	void picks_race(pair<Race, Badge> racePick);
	void conquers(Region * r);
	void scores();

	//Strategy
	char executePicksRace(vector<Player*> players);
	int executeConquers(vector<Region*> conquerableRegions);

	void countVictoryCoins();
	string displayRace();
	void loses(Region * r);

	void summarySheet();
	int getRaceBadgeBenefits();
	void abandonRegion(Region * r);

	bool operator<(const Player &other) const {
		return victoryCoins < other.victoryCoins;
	}

	bool ownsRegion(Region * r);

	void placeGamePieceInRegion(string n, Region * r);
	void emptyActiveRaceTokens();

	//Getters
	int getID() { return ID; }

	vector<Coin> getCoins1() { return coins1; }
	vector<Coin> getCoins3() { return coins3; }
	vector<Coin> getCoins5() { return coins5; }
	vector<Coin> getCoins10() { return coins10; }
	int getVictoryCoins() { return victoryCoins; }

	vector<Token> getActiveRaceTokens() { return activeRaceTokens; }

	vector<Region*> getOwnedRegions() { return ownedRegions; }
	vector<Region*> getActiveRegions();
	vector<Region*> getDeclinedRegions();

	Race getActiveRace() { return activeRace; }
	Race getDeclinedRace() { return declinedRace; }

	Badge getActiveBadge() { return activeBadge; }
	Badge getDeclinedBadge() { return declinedBadge; }

	Strategy * getStrategy() { return strategy; }
	
	//Setter
	void setStrategy(Strategy *newStrategy) {
		strategy = newStrategy;
	}
};

