#pragma once

#include "Player.h"
#include <vector>

using namespace std;

class Map {
public:
	bool loadMap(string fileName);
	vector<Edge> edges;
};

struct Edge {

	Region *origin, *destination;

	Edge(Region *o, Region *d) {
		origin = o;
		destination = d;
	}
};

struct Region {

	vector<Region*> connectedRegions;

	int id;
	int type;
	Player owner;
	int tokens;
	bool hasMountain;
};

