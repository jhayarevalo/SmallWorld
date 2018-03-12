#include "stdafx.h"
#include "Player.h"

#include <iostream>

using namespace std;

Player::Player(int pID)
{
	ID = pID;
	countVictoryCoins();
}

void Player::addCoin(Coin c) {
	int value = c.getValue();
	if (value == 1) {
		coins1.push_back(Coin(value));
	}
	else if (value == 3) {
		coins3.push_back(Coin(value));
	}
	else if (value == 5) {
		coins5.push_back(Coin(value));
	}
	else if (value == 10) {
		coins10.push_back(Coin(value));
	}
	else {
		cout << "\nCould not find a coin of value " << value << ".\n";
	}
}

void Player::removeCoin(Coin c) {
	int value = c.getValue();
	if (value == 1) {
		coins1.pop_back();
	}
	else if (value == 3) {
		coins3.pop_back();
	}
	else if (value == 5) {
		coins5.pop_back();
	}
	else if (value == 10) {
		coins10.pop_back();
	}
	else {
		cout << "\nCould not find a coin of value " << value << ".\n";
	}
}

void Player::countVictoryCoins() {
	victoryCoins = coins1.size() + coins3.size() * 3 + coins5.size() * 5 + coins10.size() * 10;
}


void Player::picks_race(pair<Race, Badge> racePick) {

	if (!activeRace.isNull()) {
		declinedRace = activeRace; //make previous active race declined
		declinedBadge = activeBadge; //make previous active badge declined
	}

	activeRace = racePick.first; //set new active race
	activeBadge = racePick.second; //set new active badge
}


void Player::conquers(Region * r) {
	r->setPlayerID(ID);
	ownedRegions.push_back(r);
	cout << "Player " << this->ID << " has conquered region " << r->getID() << "." << endl;
}

void Player::summarySheet() {
	countVictoryCoins();
	cout << endl << "###################################" << endl;
	cout << "Player " << this->ID << " Summary Sheet"<< endl;
	cout << "###################################" << endl;
	cout << coins1.size() << " x 1 Coins" << endl;
	cout << coins3.size() << " x 3 Coins" << endl;
	cout << coins5.size() << " x 5 Coins" << endl;
	cout << coins10.size() << " x 10 Coins" << endl << endl;
	cout << victoryCoins << " Total Victory Coins" << endl << endl;
	cout << ownedRegions.size() << " Owned Regions" << endl;
	if (!activeRace.isNull()) {
		cout << endl << "Active Race: " << activeRace.getName() << endl;
		cout << "Active Badge: " << activeBadge.getName() << endl;
		cout << "Active Race Tokens in Hand: " << activeRaceTokens.size() << endl;
	}
	if (!declinedRace.isNull()) {
		cout << endl << "Declined Race: " << declinedRace.getName() << endl;
		cout << "Declined Badge: " << declinedBadge.getName() << endl;
	}

	diceFacility.displayRollStats();
	cout << "###################################" << endl << endl;
}

void Player::addActiveRaceToken(Token t) {
	Race r = t.getRace();
	activeRaceTokens.push_back(Token(r,ID,NULL));//region is null because it returns to player hand
}

vector<Region*> Player::getActiveRegions() {

	vector<Region*> activeRegions;

	for (int i = 0; i < ownedRegions.size(); i++) {
		if (ownedRegions[i]->getTokens().front().getRace().equals(activeRace)) {
			activeRegions.push_back(ownedRegions[i]);
		}
	}

	return activeRegions;
}


vector<Region*> Player::getDeclinedRegions() {

	vector<Region*> declinedRegions;

	for (int i = 0; i < ownedRegions.size(); i++) {
		if (ownedRegions[i]->getTokens().front().getRace().equals(declinedRace)) {
			declinedRegions.push_back(ownedRegions[i]);
		}
	}

	return declinedRegions;
}

void Player::placeActiveToken(Region * r) {
	Token place(activeRaceTokens.front());
	r->addToken(place);
	activeRaceTokens.pop_back();
}

void Player::takeMapToken(Region * r) {
	Token take(r->getTokens().front());
	r->removeToken();
	take.setRegionID(NULL);
	activeRaceTokens.push_back(take);
}

bool Player::ownsRegion(Region * r) {
	bool owns = false;
	for (int i = 0; i < ownedRegions.size(); i++) {
		if (r->getID() == ownedRegions[i]->getID()) {
			owns = true;
			break;
		}
	}
	return owns;
}

int Player::getRaceBadgeBenefits() {
	cout << "Race & Badge Benefits Coming Soon!" << endl;
	return 0;
}

void Player::abandonRegion(Region * r) {
	for (int i = 0; i < r->getTokens().size(); i++) {
		takeMapToken(r);
	}
	r->setPlayerID(NULL);

	for (int j = 0; j < ownedRegions.size(); j++) {
		if (ownedRegions[j] == r) {
			ownedRegions.erase(ownedRegions.begin() + j);
		}
	}
}