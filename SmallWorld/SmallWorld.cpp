// SmallWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Map.h"

using namespace std;

string mapName;
Map gameMap;
bool validMap = false;
bool endGame = false;
bool validAction;
bool endTurn;

int playerAction;
int playerAction2;
int regionID;

int getIntegerInput() {
	int x = 0;
	while (!(cin >> x)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input. Try Again: ";
	}
	return x;
}

int main()
{
	cout << "Welcome to Smallworld.\n" << "Please type in the name of the map file to use.\n";
	cin >> mapName;

	gameMap.loadMap(mapName);

	while (!gameMap.isValid) {

		if (!gameMap.isValid) {
			cout << "\nThe map you have entered was invalid. Please try again.\n";
			cin >> mapName;
			gameMap.loadMap(mapName);
		}
	}

	while (!endGame) {
		for (int i = 0; i < gameMap.numPlayers; i++) {
			playerAction = 0; //Reset player action each turn
			playerAction = 0;
			validAction = false;
			endTurn = false;

			cout << "----------------------------------" << endl;
			cout << "\nPlayer " << i + 1 << "'s turn." << endl;
			cout << "----------------------------------" << endl;

			 do {
				cout << "Please select one of the following options: " << endl;
				cout << "1. List Region Connections" << endl;
				cout << "2. Pick a Race" << endl;
				cout << "3. Conquer a Region" << endl;
				cout << "4. View Player Summary Sheet" << endl;

				playerAction = getIntegerInput();

				if (playerAction == 1) {
					cout << "\n->List Region Connections: " << endl;
					cout << "1. List All Map Edges" << endl;
					cout << "2. List Connections of a Specific Region" << endl;
					cout << "Return to Options with Any Other Integer Value" << endl;

					playerAction2 = getIntegerInput();

					if (playerAction2 == 1) {
						gameMap.showAllEdges();
					}
					else if (playerAction2 == 2) {
						cout << "Enter Region ID: ";
						do {
							regionID = getIntegerInput();

							if (regionID > 0 && regionID <= gameMap.numRegions) {
								gameMap.showRegionConnections(regionID);
								validAction = true;
							}
							else {
								cout << "\nEntered Invalid Region ID. Please Try Again: ";
							}
							
						} while (!validAction);
					}
					else {
						cout << "This is an invalid action." << endl;
					}
					
				}
				else if (playerAction == 2) {

				}
				else if (playerAction == 3) {

				}
				else if (playerAction == 4) {

				}
				else if (playerAction == 5) {
					endTurn = true;
				}
				else {
					cout << "This is an invalid action." << endl;
				}
			 } while (!endTurn);
		}
	}

    return 0;
}

