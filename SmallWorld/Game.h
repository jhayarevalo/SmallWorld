#pragma once
#include "Subject.h"
#include "Map.h"

class Game : public Subject
{
private:
	int currentRound;
	int playerTurn;
	int playerAction;
	Player * currentPlayer;
	Region * currentConquerRegion;
	bool conquestInProcess;
	Map * currentMap;

public:
	Game();
	~Game();

	//Getters
	int getCurrentRound() { return currentRound; };
	int getPlayerTurn() { return playerTurn; };
	int getPlayerAction() { return playerAction; };
	Player * getCurrentPlayer() { return currentPlayer; };
	Region * getCurrentConquerRegion() { return currentConquerRegion; };
	bool isConquestInProcess() { return conquestInProcess; };
	Map * getCurrentMap() { return currentMap; };

	//Setters
	void setCurrentRound(int cr);
	void setPlayerTurn(int pt);
	void setPlayerAction(int pa);
	void setCurrentPlayer(Player * p);
	void setCurrentConquerRegion(Region * r);
	void setConquestInProcess(bool tf);
	void setCurrentMap(Map * m);
};
