#pragma once
class Coin
{

private:
	int value;

public:
	Coin();
	Coin(int v);

	int getValue() { return value; }
};

