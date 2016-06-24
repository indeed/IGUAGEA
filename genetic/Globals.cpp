#include "stdafx.h"
#include "Globals.h"

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

	return id;
}