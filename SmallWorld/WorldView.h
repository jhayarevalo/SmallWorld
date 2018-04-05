#pragma once
#include "StatisticDecorator.h"

class WorldView : public StatisticDecorator
{
public:
	WorldView(Statistic *decoratedStatistic) : StatisticDecorator(decoratedStatistic) {};
	string display() {
		string toReturn = StatisticDecorator::display() + "\nDomination View:";
		Map * map = _subject->getCurrentMap();
		vector<Player*> players = _subject->getAllPlayers();

		int totalRegions = map->getNumRegions();

		for (int i = 0; i < players.size(); i++) {
			int playerRegions;
			double percentageOwned;

			playerRegions = players[i]->getOwnedRegions().size();
			percentageOwned = ((double)playerRegions / (double)totalRegions) * 100;
			toReturn += "\nPlayer ";
			toReturn += to_string(players[i]->getID());
			toReturn += " [";

			for (int j = 0; j < playerRegions; j++) {
				toReturn += "#";
			}
			for (int k = 0; k < (totalRegions - playerRegions); k++) {
				toReturn += "-";
			}
			toReturn += "] ";
			toReturn += to_string(percentageOwned);
			toReturn += "%";
		}

		toReturn += "\n";

		return toReturn;
	}
	void Update() {
		StatisticDecorator::Update();
		// add stuff
	}
};

