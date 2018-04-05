#pragma once
#include "Player.h"

class Strategy : public Player {
public:
	virtual void picksRace(pair<Race, Badge> racePick) = 0;
	virtual void conquers(Region * r);
	virtual void scores();
};