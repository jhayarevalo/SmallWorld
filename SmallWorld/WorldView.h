#pragma once
#include "StatisticDecorator.h"

class WorldView : public StatisticDecorator
{
public:
	WorldView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		//StatisticDecorator::display();
		// add stuff

		//cout << "Region Control: TEST DECORATOR" << endl;
		return StatisticDecorator::display() + "\nRegion Control View TEST";
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

