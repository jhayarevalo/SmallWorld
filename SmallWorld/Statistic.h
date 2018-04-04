#pragma once
#include "Observer.h"
#include "Game.h"

#include <iostream>

using namespace std;

class Statistic : public Observer
{
private:
	Game *_subject;
public:
	Statistic();
	Statistic(Game* s);
	~Statistic();
	void Update();
	void display();
};

