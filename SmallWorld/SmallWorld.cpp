// SmallWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Map.h"

using namespace std;

int main()
{
	string mapName;
	Map gameMap;
	bool validMap = false;

	cout << "Welcome to Smallworld.\n" << "Please type in the name of the map file to use.\n";
	cin >> mapName;

	while (!validMap) {
		gameMap.loadMap(mapName);

		if (!gameMap.loadMap(mapName)) {
			cout << "The map you have entered was invalid. Please try again.\n";
			cin >> mapName;
		}
		else {
			validMap = true;
		}
	}

    return 0;
}

