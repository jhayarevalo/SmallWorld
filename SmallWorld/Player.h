#pragma once

#include <stack>

#include "Region.h"
#include "Dice.h"
#include "Race.h"
#include "Badge.h"
#include "Coin.h"
#include "Token.h"

class Player
{
private:
	int ID;

	//Victory Coins
	vector<Coin> coins1;
	vector<Coin> coins3;
	vector<Coin> coins5;
	vector<Coin> coins10;
	int victoryCoins;

	//Game Tokens
	vector<Token> activeRaceTokens;

	//Game Pieces
	vector<GamePiece*> gamePieces;

	vector<Region*> ownedRegions;
	vector<Region*> getActiveRegions();
	vector<Region*> getDeclinedRegions();

	Race activeRace;
	Race declinedRace;

	Badge activeBadge;
	Badge declinedBadge;

public:
	Dice diceFacility;

	Player(int pID);

	void addCoin(Coin c);
	void removeCoin(Coin c);

	void placeActiveToken(Region * r);
	void takeMapToken(Region * r);
	void takeAllMapTokens();

	void addActiveRaceToken(Token t);

	void countVictoryCoins();
	void picks_race(pair<Race,Badge> racePick);
	string displayRace();
	void conquers(Region * r);
	void loses(Region * r);
	void scores();

	void summarySheet();
	int getRaceBadgeBenefits();
	void abandonRegion(Region * r);

	bool operator<(const Player &other) const {
		return victoryCoins < other.victoryCoins;
	}

	bool ownsRegion(Region * r);

	//Getters
	int getID() { return ID; }

	vector<Coin> getCoins1() { return coins1; }
	vector<Coin> getCoins3() { return coins3; }
	vector<Coin> getCoins5() { return coins5; }
	vector<Coin> getCoins10() { return coins10; }
	int getVictoryCoins() { return victoryCoins; }

	vector<Token> getActiveRaceTokens() { return activeRaceTokens; }

	vector<Region*> getOwnedRegions() { return ownedRegions; }

	Race getActiveRace() { return activeRace; }
	Race getDeclinedRace() { return declinedRace; }

	Badge getActiveBadge() { return activeBadge; }
	Badge getDeclinedBadge() { return declinedBadge; }
	
};

