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

	void display();

	//Getters
	string getName() { return name; }
	int getPlayerID() { return playerID; }
	int getRegionID() { return regionID; }

	//Setters
	void setPlayerID(int pID) { playerID = pID; }
	void setRegionID(int rID) { regionID = rID; }
};

