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

bool Edge::equals(Edge e) {
	if (r1 == e.r1 && r2 == e.r2) {
		return true;
	}
	else {
		return false;
	}
}

Map::Map() {
	numPlayers = 0;
	numRegions = 0;
	numTurns = 0;
	valid = false;
}

void Map::loadMap(string fileName) {//Parse .map file

	string line;
	ifstream mapFile(fileName);

	bool validMap = true;
	string connectingMessage = "";

	if (mapFile.is_open()) {
		cout << "Reading file " << fileName << endl;
		while (!mapFile.eof()) {
			getline(mapFile, line);
			size_t colon = line.find_last_of(":");
			string param = line.substr(0, colon+1);
			string args = line.substr(colon+1);

			//cout << param << " | " << args << endl; //Display contents of text file
			if (param == "PLAYERS:") {
				validMap = setNumAs("Players", args);
			}
			else if (param == "TURNS:") {
				validMap = setNumAs("Turns", args);
			}
			else if (param == "REGIONS:") {
				validMap = setNumAs("Regions", args);
			}
			else if (param == "START:") {
				validMap = setRegionsAs("Start", args);
			}
			else if (param == "TRIBE:") {
				validMap = setRegionsAs("Tribe", args);
			}
			else if (param == "MOUNTAIN:") {
				validMap = setRegionsAs("Mountain", args);
			}
			else if (param == "MINE:") {
				validMap = setRegionsAs("Mine", args);
			}
			else if (param == "CAVERN:") {
				validMap = setRegionsAs("Cavern", args);
			}
			else if (param == "MAGIC:") {
				validMap = setRegionsAs("Magic", args);
			}
			else if (param == "WATER_TERRAIN:") {
				validMap = setRegionsTerrainAs("Water", args);
			}
			else if (param == "FARM_TERRAIN:") {
				validMap = setRegionsTerrainAs("Farm", args);
			}
			else if (param == "HILL_TERRAIN:") {
				validMap = setRegionsTerrainAs("Hill", args);
			}
			else if (param == "FOREST_TERRAIN:") {
				validMap = setRegionsTerrainAs("Forest", args);
			}
			else if (param == "SWAMP_TERRAIN:") {
				validMap = setRegionsTerrainAs("Swamp", args);
			}
			else if (param == "MOUNTAIN_TERRAIN:") {
				validMap = setRegionsTerrainAs("Mountain", args);
			}
			else if (param.length() <= 3 && validMap) {
				try {
					int r1ID = stoi(param);
					int r2ID;
					istringstream edgeArgs(args);
					vector<string> r2IDs(istream_iterator<string>{edgeArgs}, istream_iterator<string>());
				
					for (int i = 0; i < r2IDs.size(); i++) {
						try {
							r2ID = stoi(r2IDs[i]);
							if (isValidRegion(r2ID) && isValidRegion(r1ID)) {
								addEdge(r1ID, r2ID);
								connectingMessage.append("\nConnecting Regions: ");
								connectingMessage.append(to_string(r1ID));
								connectingMessage.append(" & ");
								connectingMessage.append(to_string(r2ID));
							}
							else {
								cerr << "\nA listed region to connect does not exist.\n";
								validMap = false;
								break;
							}
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
		if (validMap && isConnectedGraph()) {
			setValid(validMap);
			cout << connectingMessage;
			cout << "\n\nMap loaded successfully.\n";
		}
	}
	else {
		cerr << "Unable to open file.\n";
		validMap = false;
	}
}
bool Map::setNumAs(string element, string args) {
	bool validMap = true;
	try {
		if (element == "Players") {
			this->numPlayers = stoi(args); //Set number of players
		}
		else if (element == "Turns") {
			numTurns = stoi(args); //Set number of players
		}
		else if (element == "Regions") {
			this->numRegions = stoi(args); //Set number of regions
			for (int i = 0; i < numRegions; i++) {
				addRegion(i + 1); //Add all the regions in the game to the map
			}
		}
		cout << "Number of " << element << ": " << stoi(args) << endl;
	}
	catch (...) {
		cerr << "Invalid argument for the Number of " << element << ".\n";
		validMap = false;
	}
	return validMap;
}

bool Map::setRegionsAs(string element, string args) {
	bool validMap = true;

	istringstream elementArgs(args);
	vector<string> elementRegionIDs(istream_iterator<string>{elementArgs}, istream_iterator<string>());
	cout << element << " Regions: ";
	for (int i = 0; i < elementRegionIDs.size(); i++) {
		try {
			int regionID = stoi(elementRegionIDs[i]); //turn text into int
			if (isValidRegion(regionID)) {
				if (element == "Start") {
					findRegionByID(regionID)->setStart(true);//Set the region in the map as a start region
				}
				else if (element == "Tribe") {
					findRegionByID(regionID)->setTribe(true);//Set the region in the map as a tribe region
				}
				else if (element == "Mountain") {
					findRegionByID(regionID)->setMountain(true);//Set the region in the map as a mountain region
				}
				else if (element == "Mine") {
					findRegionByID(regionID)->setMine(true);//Set the region in the map as a mine region
				}
				else if (element == "Cavern") {
					findRegionByID(regionID)->setCavern(true);//Set the region in the map as a cavern region
				}
				else if (element == "Magic") {
					findRegionByID(regionID)->setMagic(true);//Set the region in the map as a magic region
				}
				cout << regionID << " ";
			}
			else {
				cerr << "\nA listed "<< element <<" Region does not exist.\n";
				validMap = false;
				break;
			}
		}
		catch (...) {
			cerr << "Invalid argument for a " << element << " Region.\n";
			validMap = false;
		}
	}
	cout << endl;

	return validMap;
}
bool Map::setRegionsTerrainAs(string element, string args) {
	bool validMap = true;

	istringstream elementArgs(args);
	vector<string> elementRegionIDs(istream_iterator<string>{elementArgs}, istream_iterator<string>());
	cout << element << " Terrain Regions: ";
	for (int i = 0; i < elementRegionIDs.size(); i++) {
		try {
			int regionID = stoi(elementRegionIDs[i]); //turn text into int
			if (isValidRegion(regionID)) {
				if (element == "Water") {
					findRegionByID(regionID)->setTerrain('w');//Set the region in the map as a water terrain region
				}
				else if (element == "Farm") {
					findRegionByID(regionID)->setTerrain('f');//Set the region in the map as a farm terrain region
				}
				else if (element == "Hill") {
					findRegionByID(regionID)->setTerrain('h');//Set the region in the map as a hill terrain region
				}
				else if (element == "Forest") {
					findRegionByID(regionID)->setTerrain('t');//Set the region in the map as a forest terrain region
				}
				else if (element == "Swamp") {
					findRegionByID(regionID)->setTerrain('s');//Set the region in the map as a swamp terrain region
				}
				else if (element == "Mountain") {
					findRegionByID(regionID)->setTerrain('m');//Set the region in the map as a mountain terrain region
				}
				cout << regionID << " ";
			}
			else {
				cerr << "\nA listed " << element << " Region does not exist.\n";
				validMap = false;
				break;
			}
		}
		catch (...) {
			cerr << "Invalid argument for a " << element << " Region.\n";
			validMap = false;
		}
	}
	cout << endl;

	return validMap;
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
	Region * rPtr;
	rPtr = new Region(rID);
	mapRegions.push_back(rPtr);
}

Region* Map::findRegionByID(int rID) {
	for (int i = 0; i < mapRegions.size(); i++) {
		if (mapRegions[i]->getID() == rID) {
			return mapRegions[i];
		}
	}
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

bool Map::isValidRegion(int rID) {
	if (rID < mapRegions.size() + 1 && rID >= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Map::areRegionsConnected(int a, int b) {
	Edge temp = Edge(a, b);
	bool foundEdge = false;
	for (int i = 0; i < mapEdges.size(); i++) {
		if (mapEdges[i].equals(temp)) {
			foundEdge = true;
			break;
		}
	}
	return foundEdge;
}

bool Map::isConnectedGraph() {

	vector<int> foundRegions;
	foundRegions.push_back(1);//push region 1 as first found region by default

	for (int i = 0; i < mapRegions.size(); i++) {
		for (int j = 0; j < foundRegions.size(); j++) {
			if (areRegionsConnected(foundRegions[j], mapRegions[i]->getID())) {
				if (!(find(foundRegions.begin(), foundRegions.end(), mapRegions[i]->getID()) != foundRegions.end())) {
					foundRegions.push_back(mapRegions[i]->getID());
				}
			}
		}
	}

	if (foundRegions.size() == numRegions) {
		return true;
	}
	else {
		cerr << "\nMap is not a connected graph." << endl;
		return false;
	}
}

void Map::showMapContents() {
	for (int i = 0; i < mapRegions.size(); i++) {
		mapRegions[i]->displayContentsInline();
		cout << endl;
	}
}

void Map::showConquerableRegions(Region * r) {
	cout << "\nAdjacent to Region " << r->getID() << "\n";
	for (int i = 0; i < mapEdges.size(); i++) {
		if (mapEdges[i].r1 == r->getID()) {
			Region * r2 = findRegionByID(mapEdges[i].r2);
			r2->displayContentsInline();
			cout << endl;
		}
	}
}

vector<Region*> Map::getConquerableRegions(Region * r) {
	vector<Region*> connectedRegions;

	for (int i = 0; i < mapEdges.size(); i++) {
		if (mapEdges[i].r1 == r->getID()) {
			Region * r2 = findRegionByID(mapEdges[i].r2);
			connectedRegions.push_back(r2);
		}
	}

	return connectedRegions;
}

bool Map::isConquerable(Region * r, Player * p) {
	bool conquerable = false;
	for (int i = 0; i < p->getOwnedRegions().size(); i++) {
		if (areRegionsConnected(p->getOwnedRegions()[i]->getID(), r->getID())) {
			conquerable = true;
			break; //region found, no longer need to be in loop
		}
	}
	return conquerable;
}