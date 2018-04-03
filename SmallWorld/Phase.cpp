#include "stdafx.h"
#include "Phase.h"
#include <iostream>
using namespace std;

Phase::Phase()
{
}

Phase::Phase(Game* s) {
	//Attaches itself to a Game upon instantiation
	_subject = s;
	_subject->Attach(this);
}

Phase::~Phase()
{
	//Detaches itself from its Game upon destruction
	_subject->Detach(this);
}

void Phase::Update() {
	//Called by Notify() when state of Subject changes
	display();
}

void Phase::display() {
	int playerTurn = _subject->getPlayerTurn();
	int playerAction = _subject->getPlayerAction();

	cout << "[Player " << playerTurn << ": ";
	if (playerAction == 1) {
		cout << "Choosing a New Race";
	}
	else if (playerAction == 2) {
		cout << "Conquering a Region";
	}
	else if (playerAction == 3) {
		cout << "Taking Back Troops";
	}
	else if (playerAction == 4) {
		cout << "Redeploying Troops";
	}
	else if (playerAction == 5) {
		cout << "Abandoning Region";
	}
	else if (playerAction == 6) {
		cout << "Viewing Player Summary Sheet";
	}
	else if (playerAction == 7) {
		cout << "Displaying Map Contents";
	}
	else if (playerAction == 8) {
		cout << "Listing Region Connections";
	}
	else if (playerAction == 9) {
		cout << "Displaying Game Bank Contents";
	}
	else if (playerAction == 10) {
		cout << "Ending Turn";
	}
	cout << "]\n";
}