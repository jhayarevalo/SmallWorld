#pragma once
#include "Subject.h"

class Game : public Subject
{
private:
	int playerTurn;
	char playerAction;
public:
	Game();
	~Game();

	//Getters
	int getPlayerTurn() { return playerTurn; };
	int getPlayerAction() { return playerAction; };

	//Setters
	int setPlayerTurn(int pt) { playerTurn = pt; };
	int setPlayerAction(int pa) { playerAction = pa; };
};
