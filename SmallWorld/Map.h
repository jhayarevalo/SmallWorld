#pragma once

#include "Region.h"
#include "GamePiece.h"
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
};

class Map {
public:
	vector<Edge> mapEdges;
	vector<Region> mapRegions;
	vector<int> startRegionIDs;
	int numPlayers;
	int numTurns;
	int numRegions;
	bool isValid;


	Map();
	void loadMap(string fileName);

	void addEdge(int a, int b);
	void addEdge(Edge c);

	void addRegion(int id);

	int findRegionIndex(int rID);

	void showAllEdges();
	void showRegionConnections(int rID);

	void addGamePieceToRegion(int rID);
};




