#pragma once
#include "Statistic.h"

class StatisticDecorator : public Statistic {
protected:
	Statistic *decoratedStatistic;
public:
	//Wraps Statistic object inside an object of one of StatisticDecorator's subclasses
	StatisticDecorator(Statistic *decoratedStatistic) {
		this->decoratedStatistic = decoratedStatistic;
	}
	//Provides wrapper with the Statistic interface and delegates its methods to the wrapped Statistic object
	void display() {
		decoratedStatistic->display();
	}
	void Update() {
		decoratedStatistic->Update();
	}
};