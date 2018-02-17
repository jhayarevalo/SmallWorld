#pragma once

#include "Region.h"
#include "Dice.h"
#include "Race.h"
#include "Badge.h"

class Player
{
public:
	int ID;

	//Victory Coins
	int coins1;
	int coins3;
	int coins5;
	int coins10;
	int victoryCoins;

	//Game Tokens
	int activeRaceTokens;
	int declinedRaceTokens;

	vector<int> ownedRegionIDs;
	Dice diceFacility;

	Race activeRace;
	Race declinedRace;

	Badge activeBadge;
	Badge declinedBadge;

	Player(int pID);

	void countVictoryCoins();
	void giveCoins(int type, int amount);
	void picks_race(pair<Race,Badge> racePick);
	void displayRace();
	void conquers(int rID);
	void scores();

	bool operator<(const Player &other) const {
		return victoryCoins < other.victoryCoins;
	}
	
};

