#pragma once
#include "StatisticDecorator.h"

class HandsView : public StatisticDecorator
{
public:
	HandsView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		string toReturn = StatisticDecorator::display() + "\n--Hands View--";
		vector<Player*> players = _subject->getAllPlayers();

		for (int i = 0; i < players.size(); i++) {
			int activeTokens;
			activeTokens = players[i]->getActiveRaceTokens().size();
			toReturn += "\nPlayer ";
			toReturn += to_string(players[i]->getID());
			toReturn += ":\n";
			toReturn += players[i]->displayRace();
			toReturn += " Race Combo\n[";
			toReturn += to_string(activeTokens);
			toReturn += "] Active Race Tokens in Hand";
		}

		toReturn += "\n";

		return toReturn;
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

