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
	int turnNumber = _subject->getCurrentRound();
	/*cout << "---GAME STATISTICS---" << endl;
	cout << "Current Turn: " << turnNumber << endl;*/
	return "Current Turn: " + turnNumber;
}