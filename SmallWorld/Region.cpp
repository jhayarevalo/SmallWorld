#include "stdafx.h"
#include "Region.h"
#include <iostream>

class Player;

using namespace std;

Region::Region() {
	ID = NULL;
	playerID = NULL;
	terrain = NULL;
	start = false;
	tribe = false;
	mine = false;
	cavern = false;
	magic = false;
}

Region::Region(int n)
{
	ID = n;
	playerID = NULL;
	terrain = NULL;
	start = false;
	tribe = false;
	mine = false;
	cavern = false;
	magic = false;
}

void Region::addGamePiece(GamePiece gp) {
	string name = gp.getName();
	GamePiece newGP(name);
	newGP.setRegionID(ID);
	newGP.setPlayerID(gp.getPlayerID());
	gamePieces.push_back(newGP);
}

void Region::addToken(Token tk) {
	Race race = tk.getRace();
	int pID = tk.getPlayerID();
	tokens.push_back(Token(race,pID,ID));//token on map belongs to a player
}

void Region::removeToken() {
	tokens.pop_back();
}

vector<GamePiece> Region::removeGamePieces(int pID) {
	vector<GamePiece> removedPieces;
	for (int i = 0; i < gamePieces.size(); i++) {
		if (gamePieces[i].getPlayerID() == pID) {
			removedPieces.push_back(GamePiece(gamePieces[i].getName()));
			gamePieces.erase(gamePieces.begin() + i);
		}
	}
	return removedPieces;
}

void Region::displayContents() {
	cout << "----------------" << endl;
	cout << "Region " << ID << endl;
	cout << "----------------" << endl;
	cout << "Player Owner: " << (playerID ? to_string(playerID) : "-");
	//cout << "Terrain Type: " << terrain << endl;
	cout << "\nTribe: " << (tribe ? "Yes\n" : "No\n");
	cout << "Mountain: " << (mountain ? "Yes\n" : "No\n");
	cout << "Total Game Pieces: " << gamePieces.size() << endl;
	cout << "Total Race Tokens: " << tokens.size() << endl;
	cout << endl;
}

void Region::displayContentsInline() {
	cout << "Region " << ID << ": ";
	cout << "[Player Owner: " << (playerID ? to_string(playerID) : "- ");
	cout << ";\tTribe: " << (tribe ? "Yes" : "No");
	cout << ";\tMountain: " << (mountain ? "Yes" : "No");
	cout << ";\tMine: " << (mine ? "Yes" : "No");
	cout << ";\tCavern: " << (cavern ? "Yes" : "No");
	cout << ";\tMagic: " << (magic ? "Yes" : "No");
	cout << ";\tTotal Game Pieces: " << gamePieces.size();
	cout << ";\tTotal Race Tokens: " << tokens.size();
	cout << ";\tTerrain: " << getTerrainName();
	cout << "]";
}

int Region::getConquerCost(Race r, Badge b) {
	int cost = 2;
	for (int i = 0; i < tokens.size(); i++) {
		cost += 1;
	}
	for (int j = 0; j < gamePieces.size(); j++) {
		cost += 1;
	}
	if (cost > 1) {
		//Race discounts
		if ((r.getName() == "Giants" && getTerrain() == 'm')
		|| (r.getName() == "Tritons" && getTerrain() == 'w')) {
			cost--;
		}
		//Badge discounts
		if (cost > 1) {
			if ((b.getName() == "Commando") 
			|| (b.getName() == "Mounted" && (getTerrain() == 'h' || getTerrain() == 'f'))
			|| (b.getName() == "Underworld" && hasCavern())){
				cost--;
			}
		}
	}
	return cost;
}

bool Region::hasGamePiece(string name) {
	for (int i = 0; i < getGamePieces().size(); i++) {
		if (getGamePieces()[i].getName() == "Fortress") {
			return true;
			break;
		}
	}
}

string Region::getTerrainName() {
	if (terrain == 'w') {
		return "Water";
	}
	else if (terrain == 'f') {
		return "Farmland";
	}
	else if (terrain == 'h') {
		return "Hill";
	}
	else if (terrain == 't') {
		return "Forest";
	}
	else if (terrain == 's') {
		return "Swamp";
	}
	else if (terrain == 'm') {
		return "Mountanous";
	}
}