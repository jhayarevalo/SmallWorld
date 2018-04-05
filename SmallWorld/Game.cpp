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
	Notify();
}

void Game::setCurrentPlayer(Player * p) { 
	currentPlayer = p; 
}

void Game::setCurrentConquerRegion(Region * r) {
	currentConquerRegion = r;
}

void Game::setConquestInProcess(bool tf) {
	conquestInProcess = tf;
	if (tf) {
		Notify();
	}
}

void Game::setCurrentMap(Map * m) {
	currentMap = m;
}


