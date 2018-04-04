#pragma once
#include "Observer.h"
#include "Game.h"

class Phase : public Observer
{
private:
	Game *_subject;
public:
	Phase();
	Phase(Game* s);
	~Phase();
	void Update();
	void display();
	void displayConquestStatus();
	void displayOwnedRegions();
	void displayActiveRaceTokens();
	void displayPlayerSummary();
};

