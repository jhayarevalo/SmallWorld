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

bool Race::equals(Race r) {
	if (name == r.name && tokens == r.tokens) {
		return true;
	}
	else {
		return false;
	}
}
