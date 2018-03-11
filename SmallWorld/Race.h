#pragma once

#include <vector>

using namespace std;

class Race
{
private:
	string name;
	int tokens;

public:
	Race();
	Race(string n, int t);
	bool isNull();
	bool equals(Race r);

	string getName() { return name; }
	int getTokens() { return tokens; }
};

