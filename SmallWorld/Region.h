#pragma once

#include <vector>

#include "GamePiece.h"
#include "Token.h"
#include "Badge.h"

using namespace std;

class Region{
private:
	int ID;
	int playerID;
	char terrain;
	bool start;
	bool tribe;
	bool mountain;
	bool mine;
	bool cavern;
	bool magic;

	vector<GamePiece> gamePieces;
	vector<Token> tokens;
public:

	Region();
	Region(int n);

	void addGamePiece(GamePiece gp);
	void addToken(Token tk);
	vector<GamePiece> removeGamePieces(int pID);
	void removeToken();
	void displayContents();
	void displayContentsInline();
	int getConquerCost(Race r, Badge b);

	bool hasGamePiece(string name);

	string getTerrainName();

	//Getters
	int getID() { return ID; }
	int getPlayerID() { return playerID; }
	char getTerrain() { return terrain; }
	bool isStart() { return start; }
	bool hasTribe() { return tribe; }
	bool hasMountain() { return mountain; }
	bool hasMine() { return mine; }
	bool hasCavern() { return cavern; }
	bool hasMagic() { return magic; }

	vector<Token> getTokens() { return tokens; }
	vector<GamePiece> getGamePieces(){ return gamePieces; }

	//Setters
	void setID(int x) { ID = x; }
	void setPlayerID(int x) { playerID = x; }
	void setTerrain(char c) { terrain = c; }
	void setStart(bool b) { start = b; }
	void setTribe(bool b) { tribe = b; }
	void setMountain(bool b) { mountain = b; }
	void setMine(bool b) { mine = b; }
	void setCavern(bool b) { cavern = b; }
	void setMagic(bool b) { magic = b; }
};

