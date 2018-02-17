#include "stdafx.h"
#include "Race.h"

Race::Race()
{
	name = "";
	tokens = NULL;
}
Race::Race(string n, int t)
{
	name = n;
	tokens = t;
}

bool Race::isNull(){
	if (name == "" || tokens == NULL) {
		return true;
	}
	else {
		return false;
	}
}
