#include "stdafx.h"
#include "GamePiece.h"
#include <iostream>

using namespace std;

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

void GamePiece::display() {
	cout << "[Name: " << name << "]" << endl;
}