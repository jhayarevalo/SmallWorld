#include "stdafx.h"
#include "Player.h"

#include <iostream>
#include <vector>
using namespace std;

Player::Player(int pID)
{
	ID = pID;
	countVictoryCoins();
	strategy = NULL;
}

Player::Player(int pID, Strategy *initStrategy)
{
	ID = pID;
	countVictoryCoins();
	strategy = initStrategy;
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
	emptyActiveRaceTokens();

	if (!activeRace.isNull()) {
		declinedRace = activeRace; //make previous active race declined
		declinedBadge = activeBadge; //make previous active badge declined
	}

	activeRace = racePick.first; //set new active race
	activeBadge = racePick.second; //set new active badge
}


void Player::conquers(Region * r) {
	if (getActiveRace().getName() == "Halflings") {
		placeGamePieceInRegion("Hole-in-the-Ground", r);
	}
	else if (getActiveRace().getName() == "Trolls") {
		placeGamePieceInRegion("Troll Lair", r);	
	}
	if (getActiveBadge().getName() == "Bivouacking") {
		placeGamePieceInRegion("Encampment", r);
	}
	else if (getActiveBadge().getName() == "Fortified") {
		placeGamePieceInRegion("Fortress", r);
	}
	else if (getActiveBadge().getName() == "Dragon Master") {
		placeGamePieceInRegion("Dragon", r);
	}
	else if (getActiveBadge().getName() == "Heroic") {
		placeGamePieceInRegion("Hero", r);
	}

	r->setPlayerID(ID);
	ownedRegions.push_back(r);
	cout << "Player " << this->ID << " has conquered region " << r->getID() << "." << endl;
	cout << "\nActive Race Tokens Remaining: " << getActiveRaceTokens().size() << endl;
}

void Player::placeGamePieceInRegion(string n, Region * r) {
	for (int i = 0; i < gamePieces.size(); i++) {
		if (gamePieces[i].getName() == n) {
			cout << "Placing " << n <<" on Region " << ID+1 << endl;
			r->addGamePiece(gamePieces[i]);
			gamePieces.erase(gamePieces.begin() + i);
			break; //only put one game piece
		}
	}
}

void Player::loses(Region * r) {
	for (int j = 0; j < ownedRegions.size(); j++) {
		if (ownedRegions[j] == r) {
			ownedRegions.erase(ownedRegions.begin() + j);
		}
	}
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
	cout << ownedRegions.size() << " Owned Regions:" << endl;
	for (int i = 0; i < ownedRegions.size(); i++) {
		cout << "Region " << ownedRegions[i]->getID() << endl;
	}
	if (!activeRace.isNull()) {
		cout << endl << "Active Race: " << activeRace.getName() << endl;
		cout << "Active Badge: " << activeBadge.getName() << endl;
		cout << "Active Race Tokens in Hand: " << activeRaceTokens.size() << endl;
	}
	if (!declinedRace.isNull()) {
		cout << endl << "Declined Race: " << declinedRace.getName() << endl;
		cout << "Declined Badge: " << declinedBadge.getName() << endl;
	}
	if (gamePieces.size() > 0) {
		for (int i = 0; i < gamePieces.size(); i++) {
			cout << endl << "Game Pieces: ";
			gamePieces[i].display();
		}
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
	Token take(getActiveRace());
	r->removeToken();
	take.setPlayerID(ID);
	take.setRegionID(NULL);
	activeRaceTokens.push_back(take);
}

void Player::takeAllMapTokens() {
	for (int i = 0; i < ownedRegions.size(); i++) {
		if (ownedRegions[i]->getTokens().size() > 0) {
			if (ownedRegions[i]->getTokens().front().getRace().equals(activeRace)) {
				int rTokens = ownedRegions[i]->getTokens().size();//number of tokens of current region we are removing tokens from
				for (int j = 0; j < rTokens; j++) {
					takeMapToken(ownedRegions[i]);
				}
			}
		}
	}
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
	//cout << "Race & Badge Benefits Coming Soon!" << endl;
	int benefits = 0;
	int raceBenefits = 0;
	int badgeBenefits = 0;
	string playerActiveRace = getActiveRace().getName();
	string playerActiveBadge = getActiveBadge().getName();

	bool hasDeclinedRace = false;
	if (getDeclinedRace().isNull()) {
		hasDeclinedRace = true;
	}
	for (int i = 0; i < getOwnedRegions().size(); i++) {
		Region * ownedRegion = getOwnedRegions()[i];
		string regionRace = ownedRegion->getTokens().front().getRace().getName();
		char regionTerrain = ownedRegion->getTerrain();

		//RACE BENEFITS
		if ((regionRace == "Dwarves" && ownedRegion->hasMine())  
		|| (playerActiveRace == "Humans" && regionRace == "Humans" && regionTerrain == 'f')
		|| (playerActiveRace == "Orcs" && regionRace == "Orcs")
		|| (playerActiveRace == "Wizards" && regionRace == "Wizards" && ownedRegion->hasMagic())){
			raceBenefits++;
		}

		//BADGE BENEFITS
		if (playerActiveBadge == "Alchemist" && !hasDeclinedRace) {
			badgeBenefits += 2;
		}
		else if ((playerActiveBadge == "Forest" && regionTerrain == 't')
			|| (playerActiveBadge == "Hill" && regionTerrain == 'h')
			|| (playerActiveBadge == "Swamp" && regionTerrain == 's')
			|| (playerActiveBadge == "Merchant")) {
			badgeBenefits++;
		}
		else if (playerActiveBadge == "Fortified") {
			for (int j = 0; j < ownedRegion->getGamePieces().size(); j++) {
				if (ownedRegion->hasGamePiece("Fortress")) {
					badgeBenefits++;
				}
			}
		}
	}
	benefits = raceBenefits + badgeBenefits;
	return benefits;
}

void Player::abandonRegion(Region * r) {
	while (r->getTokens().size() != 0) {
		takeMapToken(r);
	}
	r->setPlayerID(NULL);

	for (int j = 0; j < ownedRegions.size(); j++) {
		if (ownedRegions[j] == r) {
			ownedRegions.erase(ownedRegions.begin() + j);
		}
	}
}

string Player::displayRace() {
	string race;
	race += "[" + getActiveRace().getName() + " + " + getActiveBadge().getName() + "]";
	return race;
}

char Player::executePicksRace(vector<Player*> players) {
	Player * thisPlayer = this;
	return this->strategy->executePicksRace(thisPlayer, players);
}

int Player::executeConquers(vector<Region*> conquerableRegions) {
	Player * thisPlayer = this;
	return this->strategy->executeConquers(conquerableRegions, thisPlayer);
}

void Player::placeGamePiece(string n, Region * r) {
	for (int i = 0; i < gamePieces.size(); i++) {
		if (n == gamePieces[i].getName()) {
			r->addGamePiece(gamePieces[i]);
			gamePieces.erase(gamePieces.begin() + i);
		}
	}
}

void Player::addGamePiece(GamePiece g) {
	GamePiece gp(g.getName());
	gp.setPlayerID(ID);
	gamePieces.push_back(gp);
}

void Player::removeGamePieces(string n) {
	for (int i = 0; i < gamePieces.size(); i++) {
		if (n == gamePieces[i].getName()) {
			gamePieces.erase(gamePieces.begin() + i);
		}
	}
}

void Player::emptyActiveRaceTokens() {
	while (activeRaceTokens.size() > 0) {
		activeRaceTokens.pop_back();
	}
}