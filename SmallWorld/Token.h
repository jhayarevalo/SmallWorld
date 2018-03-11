#pragma once

#include "Race.h"

class Token
{
private:
	Race race;
	int playerID;
	int regionID;

public:
	Token();
	Token(Race r);
	Token(Race r, int pID, int rID);

	Race getRace() { return race; }
	int getPlayerID() { return playerID; }
	int getRegionID() { return regionID; }
};