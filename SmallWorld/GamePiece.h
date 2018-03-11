#pragma once

#include <string>

using namespace std;

class GamePiece
{
private:
	string name;
	int playerID;
	int regionID;

public:
	GamePiece();
	GamePiece(string n);

	//Getters

	string getName() { return name; }
	int getPlayerID() { return playerID; }
	int getRegionID() { return regionID; }
};

