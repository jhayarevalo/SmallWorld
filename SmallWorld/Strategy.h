#pragma once
class Player;

class Strategy {
public:
	~Strategy() {};
	virtual char executePicksRace(Player * thisPlayer, vector<Player*> players) {
		return 0;
	};
	virtual int executeConquers(vector<Region*> conquerableRegions, int playerID) {
		return 0;
	};
protected:
	Strategy() {};
};