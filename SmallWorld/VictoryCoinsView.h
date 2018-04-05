#pragma once
#include "StatisticDecorator.h"

class VictoryCoinsView : public StatisticDecorator
{
public:
	VictoryCoinsView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};

	string display() {
		string toReturn = StatisticDecorator::display() + "\nVictory Coins View:";
		vector<Player*> players = _subject->getAllPlayers();

		for (int i = 0; i < players.size(); i++) {
			int victoryCoins;
			players[i]->countVictoryCoins();
			victoryCoins = players[i]->getVictoryCoins();
			toReturn += "\nPlayer ";
			toReturn += to_string(players[i]->getID());
			toReturn += ": ";
			toReturn += to_string(victoryCoins);
			toReturn += " Total Coins";
		}

		toReturn += "\n";

		return toReturn;
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

