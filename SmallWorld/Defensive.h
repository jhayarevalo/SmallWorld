#pragma once

class Defensive : public Strategy {
public:
	//Declines when less active tokens than cheapest region conquest owned by a player in game.
	char executePicksRace(Player * thisPlayer, vector<Player*> players) {
		Region * cheapestRegion = NULL;
		int cheapestCost;

		for (int i = 0; i < players.size(); i++) {
			//Only checks for regions owned by other players
			if (players[i]->getID() != thisPlayer->getID()) {
				for (int j = 0; j < players[i]->getOwnedRegions().size(); j++) {
					//Choose cheapest region owned by another player
					if (cheapestRegion == NULL || players[i]->getOwnedRegions()[j]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge()) < cheapestCost) {
						cheapestRegion = players[i]->getOwnedRegions()[j];
						cheapestCost = players[i]->getOwnedRegions()[j]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge());
					}
				}
			}
		}
		if (thisPlayer->getActiveRaceTokens().size() < cheapestCost) {
			cout << "\nNow is a good time to change races as you do not have enough Active Race Tokens to take over a region from another player." << endl;
			return 'Y';
		}
		else {
			cout << "\nNow is not a good time to change races as you still have enough Active Race Tokens to take over a region from another player." << endl;
			return 'N';
		}

	};

	//Always picks cheapest region owned by a player
	int executeConquers(vector<Region*> conquerableRegions, Player * thisPlayer) {
		Region * cheapestRegion = NULL;
		int cheapestCost;

		for (int i = 0; i < conquerableRegions.size(); i++) {
			//Only checks conquerable regions that are owned by other players
			if (conquerableRegions[i]->getPlayerID() != NULL && conquerableRegions[i]->getPlayerID() != thisPlayer->getID()) {
				//Choose cheapest region owned by another player
				if (cheapestRegion == NULL || conquerableRegions[i]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge()) < cheapestCost) {
					cheapestRegion = conquerableRegions[i];
					cheapestCost = conquerableRegions[i]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge());
				}
			}
		}
		//If still null, get first available region
		if (cheapestRegion == NULL) {
			for (int i = 0; i < conquerableRegions.size(); i++) {
				//Only check for regions unowned by the player
				if (conquerableRegions[i]->getPlayerID() != thisPlayer->getID()) {
					//Get cheapest empty region
					if (cheapestRegion == NULL || conquerableRegions[i]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge()) < cheapestCost) {
						cheapestRegion = conquerableRegions[i];
						cheapestCost = conquerableRegions[i]->getConquerCost(thisPlayer->getActiveRace(), thisPlayer->getActiveBadge());
					}
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