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
	int getLength();
	int* getHeadPos();
	~Player();
};

