#pragma once

#include <string>

using namespace std;

class Badge
{
private:
	string name;
	int tokens;

public:
	Badge();
	Badge(string n, int t);

	string getName() { return name; }
	int getTokens() { return tokens; }
};

