#include "stdafx.h"
#include "Globals.h"

std::vector<int> Globals::_usedId;

int Globals::uniqueId() {
	// Generate base 256 number for unique color "ID". Doesn't include 255, 255, 255 because white is for food.
	int id;
	bool taken = true;
	while (taken) {
		taken = false;
		id = (rand() % 155 + 100) * 256 * 256 + (rand() % 155 + 100) * 256 + (rand() % 155 + 100);
		for (int i = 0; i < _usedId.size(); i++) {
			if (_usedId[i] == id) {
				taken = true;
			}
		} 
	}
	// Add to vector of used ids so it is no longer reused
	_usedId.push_back(id);
	return id;
}

// Check whether or not a tile coordinate is within the board limits
bool Globals::withinBounds(int x, int y) {
	if (x < 1 || y < 1 || x >= G_WIDTH - 1 || y >= G_HEIGHT - 1) {
		return false;
	} else {
		return true;
	}
}