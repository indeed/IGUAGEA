#pragma once
#include "Globals.h"
#include <vector>
#include <array>

class Player
{
private:
	int _length;
	int _id;
	std::array<int, 2> _headPos;
	std::vector<std::array<int,2>> _body;
	bool _isDead = false;
	bool _isHuman = false;
public:
	Player();
	Player(int x, int y);
	int getLength();
	std::array<int, 2> getHeadPos();
	int getId();
	bool isDead();
	bool isHuman();
	std::array<int,2> getSegment(int i);
	void setLength(int l);
	void addLength(int l);
	void setHuman(bool n);
	void move(Direction dir);
	void death();
	~Player();
};

