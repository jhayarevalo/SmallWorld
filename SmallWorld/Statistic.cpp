#include "stdafx.h"
#include "Statistic.h"

Statistic::Statistic()
{
}

Statistic::Statistic(Game* s) {
	//Attaches itself to a Game upon instantiation
	_subject = s;
	_subject->Attach(this);
}

Statistic::~Statistic()
{
	//Detaches itself from its Game upon destruction
	_subject->Detach(this);
}

void Statistic::Update() {
	//Called by Notify() when state of Subject changes
	display();
}

string Statistic::display() {
	//Minimum Turn Numbe
	int currentRound = _subject->getCurrentRound();
	Player * player = _subject->getCurrentPlayer();

	string toReturn = "";
	toReturn += "\n============================================\n";
	toReturn += "ROUND ";
	toReturn += to_string(currentRound);
	toReturn += ": Player ";
	toReturn +=	to_string(player->getID());
	toReturn += "\n============================================\n";

	return toReturn;
}