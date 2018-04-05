#pragma once
#include "Strategy.h"

class DecisionMaker {
private:
	Strategy *strategy;

public:
	DecisionMaker() {};

	DecisionMaker(Strategy *initStrategy) {
		this->strategy = initStrategy;
	}

	void setStrategy(Strategy *newStrategy) {
		this->strategy = newStrategy;
	}

	void picksRace(pair<Race, Badge> racePick) {
		return this->strategy->picksRace(racePick);
	};

	void conquers(Region * r) {
		return this->strategy->conquers(r);
	};

	void scores() {
		return this->strategy->scores();
	};
};