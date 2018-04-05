#pragma once
#include "StatisticDecorator.h"

class VictoryCoinsView : public StatisticDecorator
{
public:
	VictoryCoinsView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		return StatisticDecorator::display() + "\nVictory Coins View TEST";
		// add stuff

		//cout << "Victory Coins View: TEST DECORATOR" << endl;
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

