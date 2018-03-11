#include "stdafx.h"
#include "Region.h"
#include <iostream>

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
	gamePieces.push_back(GamePiece(name));
}

void Region::addToken(Token tk) {
	Race race = tk.getRace();
	int pID = tk.getPlayerID();
	tokens.push_back(Token(race,pID,ID));//token on map belongs to a player
}

void Region::removeToken() {
	tokens.pop_back();
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
	cout << ";\tTotal Game Pieces: " << gamePieces.size();
	cout << ";\tTotal Race Tokens: " << tokens.size();
	cout << "]";
}

int Region::getConquerCost() {
	int cost = 2;
	for (int i = 0; i < tokens.size(); i++) {
		cost += 1;
	}
	for (int j = 0; j < gamePieces.size(); j++) {
		cost += 1;
	}
	return cost;
}