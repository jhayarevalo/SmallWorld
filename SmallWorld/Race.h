#pragma once

#include <vector>

using namespace std;

class Race
{
public:

	string name;
	int tokens;

	Race();
	Race(string n, int t);
	bool isNull();
};

