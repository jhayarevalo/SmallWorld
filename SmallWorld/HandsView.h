#pragma once
#include "StatisticDecorator.h"

class HandsView : public StatisticDecorator
{
public:
	HandsView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		//StatisticDecorator::display();
		// add stuff

		//cout << "Hands View: TEST DECORATOR" << endl;
		return StatisticDecorator::display() + "\nHands View TEST";
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

