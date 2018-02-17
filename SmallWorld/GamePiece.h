#pragma once

#include <string>

using namespace std;

class GamePiece
{
public:

	string name;
	int regionID;

	GamePiece();
	GamePiece(string n, int rID);
};

