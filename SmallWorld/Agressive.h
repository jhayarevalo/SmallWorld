#pragma once

class Aggressive : public Strategy {
public:
	~Aggressive() {};
	Aggressive() {};
	//Declines only when no tokens and owned regions left.
	char executePicksRace(Player * thisPlayer, vector<Player*> players) {
		if (thisPlayer->getActiveRaceTokens().size() == 0 && thisPlayer->getOwnedRegions().size() == 0) {
			cout << "\nNow is a good time to change races as you have lost everything." << endl;
			return 'Y';
		}
		else {
			cout << "\nNow is not a good time to change races as you still have elements of this race to your posession." << endl;
			return 'N';
		}
	};

	//Always takes the first available cheapest region
	int executeConquers(vector<Region*> conquerableRegions, int playerID) {
		Region * cheapestRegion = NULL;
		int cheapestCost;

		for (int i = 0; i < conquerableRegions.size(); i++) {
			//Only check for regions unowned by the player
			if (conquerableRegions[i]->getPlayerID() != playerID) {
				//Choose cheapest unowned region
				if (cheapestRegion == NULL || conquerableRegions[i]->getConquerCost() < cheapestCost) {
					cheapestRegion = conquerableRegions[i];
					cheapestCost = conquerableRegions[i]->getConquerCost();
				}
			}
		}

		if (cheapestRegion != NULL) {
			return cheapestRegion->getID();
		}
		else {
			return 0;
		}
	};
};