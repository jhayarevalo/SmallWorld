#pragma once
#include "StatisticDecorator.h"

class WorldControl : public StatisticDecorator
{
public:
	WorldControl(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	void display() {
		StatisticDecorator::display();
		// add stuff
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
		cout << "Region Control: TEST DECORATOR" << endl;
	}
};

