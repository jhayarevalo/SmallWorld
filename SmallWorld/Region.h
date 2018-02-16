#pragma once

#include <vector>

using namespace std;

class Region{
public:
	int ID;
	int playerID;
	char terrain;
	bool isStart;
	bool hasTribe;
	bool hasMine;
	bool hasCavern;
	bool hasMagic;

	vector<int> adjacentRegionIDs;

	Region(int n);
	void addAdjacentRegion(int rID);
};

