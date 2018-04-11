#include "stdafx.h"
#include "Phase.h"
#include <iostream>
using namespace std;

Phase::Phase()
{
}

Phase::Phase(Game* s) {
	//Attaches itself to a Game upon instantiation
	_subject = s;
	_subject->Attach(this);
}

Phase::~Phase()
{
	//Detaches itself from its Game upon destruction
	_subject->Detach(this);
}

void Phase::Update() {
	//Called by Notify() when state of Subject changes
	display();
}

void Phase::display() {
	int currentRound = _subject->getCurrentRound();
	int playerTurn = _subject->getPlayerTurn();
	int playerAction = _subject->getPlayerAction();
	Player * currentPlayer = _subject->getCurrentPlayer();
	Map * currentMap = _subject->getCurrentMap();
	bool conquestInProcess = _subject->isConquestInProcess();

	if(playerAction > 0) {
		cout << "\n---Player " << playerTurn << ": ";

		//--- RACE RELATED ACTION ---
		if (playerAction == 1) {
			cout << "Choosing a New Race---\n";

			//First turn
			if (currentPlayer->getActiveRace().isNull()) {
				cout << "\nWelcome, Player " << playerTurn << "!\nSelect a Race and Special Power combo from one of the following:" << endl;
				cout << "Choosing at the top of the deck is free. Otherwise, a coin must be dropped on each skipped combo. Selecting a combo with coins on it will add those coins to your inventory.\n\n";
			}
			//Decline Race
			else {
				cout << "\n->Your current Race and Special Power combo is " << currentPlayer->getActiveRace().getName() << " (" << currentPlayer->getActiveRace().getTokens() << ") + " << currentPlayer->getActiveBadge().getName() << " (" << currentPlayer->getActiveBadge().getTokens() << ")" << endl;				
			}
		}

		//--- CONQUERING RELATED ACTION ---
		else if (playerAction == 2) {
			cout << "Conquering a Region---\n";

			if (currentPlayer->getActiveRaceTokens().size() > 0 && !conquestInProcess) {
				displayActiveRaceTokens();
				if (currentPlayer->getOwnedRegions().size() <= 0) {
					cout << "->No Current Owned Regions. Enter one of the following region IDs:" << endl;
				}
				else {
					cout << "->Select one of the following adjacent regions to the ones you own. Enter the region you wish to conquer by region ID:" << endl;
				}
			}
			else if (conquestInProcess) {
				displayConquestStatus();
			}
			else {
				cout << "No race tokens left. " << endl;
			}
		}
		
		//--- TAKING BACK RELATED ACTION ---
		else if (playerAction == 3) {
			cout << "Taking Back Troops---\n";
			displayOwnedRegions();
			cout << endl;
			displayActiveRaceTokens();
		}

		//--- REDEPLOYMENT RELATED ACTION ---
		else if (playerAction == 4) {
			cout << "Redeploying Troops---\n";
			displayOwnedRegions();
			cout << endl;
			displayActiveRaceTokens();
		}

		//--- ABANDONING REGION ---
		else if (playerAction == 5) {
			cout << "Abandoning Region---\n";
			if (currentPlayer->getOwnedRegions().size() > 0) {
				displayOwnedRegions();
			}
			else {
				cout << "You do not own any regions.\n";
			}
		}

		//--- GAME STATS RELATED ACTION ---
		else if (playerAction == 6) {
			cout << "Viewing Player Summary Sheet---\n";
		}

		//--- MAP CONTENTS RELATED ACTION ---
		else if (playerAction == 7) {
			cout << "Displaying Map Contents---\n";
		}

		//--- EDGES RELATED ACTION ---
		else if (playerAction == 8) {
			cout << "Listing Region Connections---\n";
		}

		//--- BANK CONTENTS RELATED ACTION ---
		else if (playerAction == 9) {
			cout << "Displaying Game Bank Contents---\n";
		}

		//--- GAME STATISTICS RELATED ACTION ---
		else if (playerAction == 10) {
			cout << "Toggling Game Statistics---\n";
		}

		//--- END TURN ---
		else if (playerAction == 11) {
			cout << "Ending Turn---\n";
			displayActiveRaceTokens();
			displayPlayerSummary();
		}
	}
}

void Phase::displayConquestStatus() {
	int currentRound = _subject->getCurrentRound();
	int playerTurn = _subject->getPlayerTurn();
	int playerAction = _subject->getPlayerAction();
	Player * currentPlayer = _subject->getCurrentPlayer();
	Region * currentConquerRegion = _subject->getCurrentConquerRegion();

	int conquerCost;
	conquerCost = currentConquerRegion->getConquerCost();

	//Conquering Region
	if (currentConquerRegion->getPlayerID() == currentPlayer->getID()) {
		cout << "You already own this region." << endl;
	}
	else {
		cout << "Region " << currentConquerRegion->getID() << " costs " << conquerCost << " Race Tokens to conquer." << endl;

		if (currentPlayer->getActiveRaceTokens().size() >= conquerCost) {
			if (currentConquerRegion->getPlayerID() != NULL) {
				cout << "Player " << playerTurn << " has taken Region " << currentConquerRegion->getID() << " from Player " << currentConquerRegion->getPlayerID() << "!\n";
			}
			else if (currentConquerRegion->getTokens().size() > 0) {
				cout << "Player " << playerTurn << " has taken Region " << currentConquerRegion->getID() << " from a Lost Tribe!\n";
			}
		}
		else {
			cout << "You currently do not have enough tokens to conquer this region." << endl;
		}
	}	
}

void Phase::displayOwnedRegions() {
	Player * currentPlayer = _subject->getCurrentPlayer();

	cout << "Here is a summary of your conquests.\n\nOwned Regions:" << endl;
	for (int r = 0; r < currentPlayer->getOwnedRegions().size(); r++) {
		currentPlayer->getOwnedRegions()[r]->displayContentsInline();
		cout << endl;
	}
}

void Phase::displayActiveRaceTokens() {
	Player * currentPlayer = _subject->getCurrentPlayer();

	cout << "Active Race Tokens in Hand: " << currentPlayer->getActiveRaceTokens().size() << endl << endl;
}

void Phase::displayPlayerSummary() {
	Player * currentPlayer = _subject->getCurrentPlayer();

	cout << currentPlayer->getOwnedRegions().size() << " Owned Regions" << endl;
}