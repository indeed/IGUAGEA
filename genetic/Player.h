#pragma once
#include <array>

class Player
{
private:
	int _length;
	int _id;
	int _headPos[2];
public:
	Player();
	Player(int x, int y);
	int getLength();
	int* getHeadPos();
	int getId();
	~Player();
};

