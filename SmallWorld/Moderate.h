#pragma once

class Moderate : public Strategy {
public:
	//If Ghouls already picked, declines.
	char executePicksRace(Player * thisPlayer, vector<Player*> players) {
		char declineChoice;

		if (thisPlayer->getActiveRace().getName() == "Ghouls") {
			cout << "\nNow is a good time to change races as you have the Ghouls race." << endl;
			return 'Y';
		}
		else {
			cout << "Would you like to put this race in decline and select a new active Race and Special Power combo? (Y/N)\n";
			cin >> declineChoice;
		}
	};

	//Manual input
	int executeConquers(vector<Region*> conquerableRegions, int playerID) {
		int choice;
		bool validChoice = false;
		do {
			cout << "Conquer Region: ";
			cin >> choice;
			for (int i = 0; i < conquerableRegions.size(); i++) {
				if (choice == conquerableRegions[i]->getID()) {
					validChoice = true;
					break;
				}
			}
			if (!validChoice) {
				cout << "Cannot conquer this region. Try again.\n";
			}
		} while (!validChoice);

		return choice;
	};

};