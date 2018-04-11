#pragma once

#include "Region.h"
#include "Player.h"
#include <vector>

using namespace std;

class Edge {
public:
	int r1; //Region 1
	int r2; // Region 2

	Edge(int a, int b);

	Edge getInverse(); //Edges are bidirectional
	string toString();
	bool equals(Edge e);
};

class Map {
private:
	int numPlayers;
	int numTurns;
	int numRegions;
	bool valid;

public:
	vector<Edge> mapEdges;
	vector<Region*> mapRegions;

	Map();
	void loadMap(string fileName);

	void addEdge(int a, int b);
	void addEdge(Edge c);

	void addRegion(int id);

	Region* findRegionByID(int rID);

	void showAllEdges();
	void showRegionConnections(int rID);

	void showConquerableRegions(Region * r);
	vector<Region*> getConquerableRegions(Region * r);

	bool isConquerable(Region * r, Player * p);

	bool isValidRegion(int rID);

	bool areRegionsConnected(int a, int b);
	bool isConnectedGraph();

	void showMapContents();

	bool setNumAs(string element, string args);
	bool setRegionsAs(string element, string args);
	bool setRegionsTerrainAs(string element, string args);

	//Getters
	int getNumPlayers() { return numPlayers; }
	int getNumTurns() { return numTurns; }
	int getNumRegions(){ return numRegions; }
	bool isValid() { return valid; }

	//Setters
	void setNumPlayers(int x) { numPlayers = x; }
	void setNumTurns(int x) { numTurns = x; }
	void setNumRegions(int x) { numRegions = x; }
	void setValid(bool b) { valid = b; }
};




