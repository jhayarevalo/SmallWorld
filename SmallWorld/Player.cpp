#include "stdafx.h"
#include "Player.h"

#include <iostream>

using namespace std;

Player::Player(int pID)
{
	ID = pID;
	coins1 = 5;
	countVictoryCoins();
}

void Player::countVictoryCoins() {
	victoryCoins = coins1 + coins3 * 3 + coins5 * 5 + coins10 * 10;
}

void Player::giveCoins(int type, int amount) {
	if (type == 1) {
		coins1 = amount;
	}
	else if (type == 3) {
		coins3 = amount;
	}
	else if (type == 5) {
		coins5 = amount;
	}
	else if (type == 10) {
		coins10 = amount;
	}
	else {
		cerr << "Invalid coin type." << endl;
	}
}

void Player::picks_race(pair<Race, Badge> racePick) {
	activeRace = racePick.first; //set active race
	activeBadge = racePick.second; //set active badge
}


void Player::conquers(int rID) {
	cout << "Player " << this->ID << " has conquered a region." << endl;
}

void Player::scores() {
	cout << "\nPlayer " << this->ID << " has.." << endl;
	cout << victoryCoins << " Victory Coins." << endl;
	cout << ownedRegionIDs.size() << " Owned Regions." << endl;
	if (!activeRace.isNull()) {
		cout << "Active Race: " << activeRace.name << endl;
		cout << "Active Badge: " << activeBadge.name << endl;
	}
	if (!declinedRace.isNull()) {
		cout << "Declined Race: " << declinedBadge.name << endl;
		cout << "Declined Race: " << declinedBadge.name << endl;
	}

	diceFacility.displayRollStats();

}
