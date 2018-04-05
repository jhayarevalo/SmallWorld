#pragma once
#include "Observer.h"
#include "Game.h"

#include <iostream>

using namespace std;

class Statistic : public Observer
{
public:
	Game *_subject;
	virtual string display();
	Statistic();
	Statistic(Game* s);
	~Statistic();
	void Update();
};

