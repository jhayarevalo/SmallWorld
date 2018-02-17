#include "stdafx.h"
#include "Badge.h"

Badge::Badge()
{
	name = "";
	tokens = NULL;
}
Badge::Badge(string n, int t)
{
	name = n;
	tokens = t;
}
