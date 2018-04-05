#pragma once
#include "StatisticDecorator.h"

class HandsView : public StatisticDecorator
{
public:
	HandsView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		return StatisticDecorator::display() + "\nHands View TEST:";
		vector<Player*> players = _subject->getAllPlayers();
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

