#include "stdafx.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	currentRound = NULL;
	playerTurn = NULL;
	playerAction = NULL;
}

Game::~Game()
{
}

//Setters
void Game::setCurrentRound(int cr) { 
	currentRound = cr; 
}

void Game::setPlayerTurn(int pt)
{ 
	playerTurn = pt; 
}

void Game::setPlayerAction(int pa) {
	playerAction = pa;
	Notify(); // for Phase Observer
}

void Game::setCurrentPlayer(Player * p) { 
	currentPlayer = p; 
	Notify(); // for Statistic Observer
}

void Game::setCurrentConquerRegion(Region * r) {
	currentConquerRegion = r;
}

void Game::setConquestInProcess(bool tf) {
	conquestInProcess = tf;
	if (tf) {
		Notify(); // for Phase Observer
	}
}

void Game::setCurrentMap(Map * m) {
	currentMap = m;
}

void Game::setPlayers(vector<Player*> vp) {
	players = vp;
}

