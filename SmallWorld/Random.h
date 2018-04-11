#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Random : public Strategy {
public:
	//Randomly Declines
	char executePicksRace(Player * thisPlayer, vector<Player*> players) {
		srand((unsigned)time(0));

		int value = rand() % 2;

		cout << "\nRandomly selecting Y or N" << endl;
		if (value == 0) {
			return 'Y'; 
		}
		else {
			return 'N';
		}
	};

	//Chooses random region to conquer
	int executeConquers(vector<Region*> conquerableRegions, int playerID) {
		srand((unsigned)time(0));
		int value;

		do {
			value = rand() % conquerableRegions.size();
		} while (conquerableRegions[value]->getPlayerID() == playerID);

		return conquerableRegions[value]->getID();
	};

};