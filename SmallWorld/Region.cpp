#include "stdafx.h"
#include "Region.h"

using namespace std;

Region::Region(int n)
{
	ID = n;
	playerID = NULL;
	terrain = NULL;
	isStart = false;
	hasTribe = false;
	hasMine = false;
	hasCavern = false;
	hasMagic = false;
	
}

void Region::addAdjacentRegion(int rID) {
	adjacentRegionIDs.push_back(rID);
}

