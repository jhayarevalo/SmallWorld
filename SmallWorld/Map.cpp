#include "stdafx.h"
#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstddef>
#include <iterator>
#include <algorithm>

using namespace std;

Edge::Edge(int a, int b){
	r1 = a;
	r2 = b;
}

Edge Edge::getInverse() {
	return Edge(r2, r1);
}

string Edge::toString() {
	return '(' + to_string(r1) + ',' + to_string(r2) + ')';
}

Map::Map() {
	numPlayers = 0;
	numRegions = 0;
	numTurns = 0;
	isValid = false;
}

void Map::loadMap(string fileName) {//Parse .map file

	string line;
	ifstream mapFile(fileName);

	bool validMap = true;

	if (mapFile.is_open()) {
		cout << "Reading file " << fileName << endl;
		while (!mapFile.eof()) {
			getline(mapFile, line);
			size_t colon = line.find_last_of(":");
			string param = line.substr(0, colon+1);
			string args = line.substr(colon+1);

			//cout << param << " | " << args << endl; //Display contents of text file

			if (param == "PLAYERS:") {
				try {
					this->numPlayers = stoi(args); //Set number of players
					cout << "\nNumber of Players: " << numPlayers << endl;
				}
				catch (...) {
					cerr << "Invalid argument for the number of players.\n";
					validMap = false;
				}
			}
			else if (param == "TURNS:") {
				try {
					this->numTurns = stoi(args); //Set number of players
					cout << "\nNumber of Turns: " << numTurns << endl;
				}
				catch (...) {
					cerr << "Invalid argument for the number of turns.\n";
					validMap = false;
				}
			}
			else if (param == "REGIONS:") {
				try {
					this->numRegions = stoi(args); //Set number of regions
					for (int i = 0; i < numRegions; i++) {
						this->addRegion(i + 1); //Add all the regions in the game to the map
					}
					cout << "Number of Regions: " << numRegions << endl;
				}
				catch (...) {
					cerr << "Invalid argument for the number of regions.\n";
					validMap = false;
				}
			}
			else if (param == "START:") {
				istringstream startArgs(args);
				vector<string> startRegionIDs(istream_iterator<string>{startArgs}, istream_iterator<string>());
				cout << "Starting Regions: ";
				for (int i = 0; i < startRegionIDs.size(); i++) {
					try {
						int regionID = stoi(startRegionIDs[i]);
						int r = findRegionIndex(regionID);
						this->mapRegions[r].isStart = true;//Set the region in the map as a starting region
						this->startRegionIDs.push_back(regionID);
						cout << regionID << " ";
					}
					catch (...) {
						cerr << "Invalid argument for a start region.\n";
						validMap = false;
					}
				}
				cout << endl;
			}
			else if (param.length() <= 3) {
				try {
					int r1ID = stoi(param);
					int r2ID;
					istringstream edgeArgs(args);
					vector<string> r2IDs(istream_iterator<string>{edgeArgs}, istream_iterator<string>());

					for (int i = 0; i < r2IDs.size(); i++) {
						try {
							r2ID = stoi(r2IDs[i]);
							this->addEdge(r1ID, r2ID);
							cout << "\nConnecting Regions: " << to_string(r1ID) << " & " << to_string(r2ID);
						}
						catch (...) {
							cerr << "Invalid argument for the region edges.\n";
							validMap = false;
						}
					}
				}
				catch (...) {
					cout << "Invalid edge definition line.\n";
				}
			}
		}
		mapFile.close();
		this->isValid = validMap;
		cout << "\n\nMap loaded successfully.\n";
	}
	else {
		cerr << "Unable to open file.\n";
		validMap = false;
	}
}

void Map::addEdge(int a, int b) {

	Edge connection(a, b);
	mapEdges.push_back(connection);
	mapEdges.push_back(connection.getInverse());
}

void Map::addEdge(Edge c) {
	mapEdges.push_back(c);
	mapEdges.push_back(c.getInverse());
}

void Map::addRegion(int rID) {
	Region newRegion(rID);
	mapRegions.push_back(newRegion);
}

int Map::findRegionIndex(int rID) {
	auto it = find_if(mapRegions.begin(), mapRegions.end(), [&rID](const Region& obj) {return obj.ID == rID; }); //Find region ID in mapRegions
	auto index = distance(mapRegions.begin(), it); //Get index of mapRegions where region ID = rID

	return index;
}

void Map::showAllEdges() {
	cout << "\nAll Map Edges:" << endl;
	for (int i = 0; i < mapEdges.size(); i++) {
		cout << mapEdges[i].toString() << endl;
	}
}

void Map::showRegionConnections(int rID) {
	cout << "\nRegion " << rID << " Connections:"<< endl;
	for (int i = 0; i < mapEdges.size(); i++) {
		if (mapEdges[i].r1 == rID || mapEdges[i].r2 == rID) {
			cout << mapEdges[i].toString() << endl;
		}
	}

}





