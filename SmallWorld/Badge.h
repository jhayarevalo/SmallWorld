#pragma once

#include <string>

using namespace std;

class Badge
{
public:
	string name;
	int tokens;

	Badge();
	Badge(string n, int t);
};

