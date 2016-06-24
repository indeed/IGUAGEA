#include "stdafx.h"
#include "Player.h"
#include "Globals.h"

Player::Player() : Player(0, 0){}

Player::Player(int x, int y) {
	_id = Globals::uniqueId();
	if (x < 0 || y < 0 || x >= G_WIDTH || y >= G_HEIGHT) {
		_headPos[0] = x;
		_headPos[1] = y;
	} else {
		_headPos[0] = 0;
		_headPos[1] = 0;
	};
}

int Player::getLength() {
	return _length;
}

int* Player::getHeadPos() {
	return _headPos;
}

int Player::getId() {
	return _id;
}

Player::~Player()
{
}
