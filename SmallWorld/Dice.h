#pragma once

class Dice
{
public:
	int totalRolls;
	int rollCount[4];

	Dice();

	int roll(); //roll between 0-3
	void displayRollStats(); //percentage of all individual rolls of a dice
};

