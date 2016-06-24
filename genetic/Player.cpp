#include "stdafx.h"
#include "Player.h"
#include "Globals.h"

Player::Player()
{
	std::array<std::array<int, G_HEIGHT>, G_WIDTH> _board;
}

int Player::getLength() {
	return _length;
}

int* Player::getHeadPos() {
	return _headPos;
}


Player::~Player()
{
}
