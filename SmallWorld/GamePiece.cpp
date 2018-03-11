#include "stdafx.h"
#include "GamePiece.h"


GamePiece::GamePiece()
{
	name = "";
	regionID = NULL;
}

GamePiece::GamePiece(string n)
{
	name = n;
	playerID = NULL;
	regionID = NULL;
}