#include "stdafx.h"
#include "Dice.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

Dice::Dice()
{
	totalRolls = 0;
	rollCount[0] = 0; //roll empty
	rollCount[1] = 0; //roll 1
	rollCount[2] = 0; //roll 2
	rollCount[3] = 0; //roll 3
}

int Dice::roll() {

	srand((unsigned)time(0));
	int value = rand()%6;

	totalRolls = totalRolls + 1;

	if (value > 2) { //if random integer is greater than 2, i.e. 3,4,5
		rollCount[0] = rollCount[0] + 1;
		return 0;
	}
	else { 
		rollCount[value + 1] = rollCount[value + 1] + 1;
		return value + 1;
	}
}

void Dice::displayRollStats() {
	cout << "\nDice Roll Statistics:" << endl;
	if (totalRolls > 0) {
		cout << "Dice Roll 1: " << ((float)rollCount[1] / (float)totalRolls) * 100.0 << "%" << endl;
		cout << "Dice Roll 2: " << ((float)rollCount[2] / (float)totalRolls) * 100.0 << "%" << endl;
		cout << "Dice Roll 3: " << ((float)rollCount[3] / (float)totalRolls) * 100.0 << "%" << endl;
		cout << "Dice Roll Empty: " << ((float)rollCount[0] / (float)totalRolls) * 100.0 << "%" << endl;
	}
	else {
		cout << "You have not rolled the dice yet." << endl;
	}
}
