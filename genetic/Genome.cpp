#include "stdafx.h"
#include "Genome.h"
#include <iostream>

namespace Genome
{
	void Genome::mutate(std::vector<int*>* dna, int w, int h) {
		bool mutated = false;
		while (!mutated) {
			if (std::rand() % BIG < ADDPOLY_CHANCE) {
				if (addPoly(dna, w, h)) {
					mutated = true;
				}
			}
		if (std::rand() % BIG < REMOVEPOLY_CHANCE) {
				if (removePoly(dna)) {
					mutated = true;
				}
			}
			if (std::rand() % BIG < SHIFTPOLY_CHANCE) {
				if (shiftPoly(dna)) {
					mutated = true;
				}
			}
			
			for (int i = 0; i < dna->size(); i++) {
				if (std::rand() % BIG < MOVEPOINT_CHANCE) {
					if (movePoint(dna, i, w, h)) {
						mutated = true;
					}
				}
				if (std::rand() % BIG < RECOLOR_CHANCE) {
					if (recolor(dna, i, 0)) {
						mutated = true;
					}
				}
				if (std::rand() % BIG < RECOLOR_CHANCE) {
					if (recolor(dna, i, 1)) {
						mutated = true;
					}
				}
				if (std::rand() % BIG < RECOLOR_CHANCE) {
					if (recolor(dna, i, 2)) {
						mutated = true;
					}
				}
				if (std::rand() % BIG < RECOLOR_CHANCE) {
					if (recolor(dna, i, 3)) {
						mutated = true;
					}
				}
			}
		}
	};

	bool Genome::addPoly(std::vector<int*>* dna, int w, int h) {
		if (dna->size() < MAX_POLYGONS) {
			int *poly = new int[10];
			// Generate vertices
			poly[0] = std::rand() % w;
			poly[1] = std::rand() % h;
			poly[2] = std::rand() % w;
			poly[3] = std::rand() % h;
			poly[4] = std::rand() % w;
			poly[5] = std::rand() % h;
			// Generate colors
			for (int j = 6; j < 10; j++) {
				poly[j] = std::rand() % 256;
			}
			// Insert into meme
			//dna->insert(dna->begin() + ((dna->size() > 0) ? std::rand() % dna->size() : 0), poly);
			dna->push_back(poly);
			return true;
		}
		return false;
	}

	bool Genome::shiftPoly(std::vector<int*>* dna) {
		if (dna->size() > 1) {
			int i = std::rand() % dna->size();
			int j = std::rand() % dna->size();
			int *poly = (*dna)[i];
			dna->insert(dna->begin() + j, poly);
			if (i > j) {
				dna->erase(dna->begin() + i);
			}
			else {
				dna->erase(dna->begin() + i + 1);
			}
			
			return true;

		}
		return false;
	};


	bool Genome::removePoly(std::vector<int*>* dna) {
		if (dna->size() > 1) {
			dna->erase(dna->begin() + std::rand() % dna->size());
			return true;
		}
		return false;
	}

	// Recolor one of the color properties of the shape (0 = r, 1 = g, 2 = b, 3 = a)
	bool Genome::recolor(std::vector<int*>* dna, int i, int value) {
		if (dna->size() > i) {
			(*dna)[i][6 + value] = std::rand() % 256;
			return true;
		}
		return false;
	};

	bool Genome::movePoint(std::vector<int*>* dna, int i, int w, int h) {
		if (dna->size() > 0) {
			int *poly = (*dna)[i];
			poly[(std::rand() % 3) * 2] = std::rand() % w; // Move X
			poly[(std::rand() % 3) * 2 + 1] = std::rand() % h; // Move Y
			return true;
		}
		return false;
	};
}