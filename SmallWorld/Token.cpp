#include "stdafx.h"
#include "Token.h"


Token::Token()
{
}

Token::Token(Race r) {
	race = r;
}


Token::Token(Race r, int pID, int rID){
	race = r;
	playerID = pID;
	regionID = rID;
}