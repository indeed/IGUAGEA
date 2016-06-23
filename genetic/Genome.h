#pragma once
#include <vector>

namespace Genome
{
	static const int BIG = 10000000;
	static int MAX_POLYGONS = 50;
	static int ADDPOLY_CHANCE = BIG/700;
	static int SHIFTPOLY_CHANCE = BIG/700;
	static int REMOVEPOLY_CHANCE = BIG/10500;
	static int RECOLOR_CHANCE = BIG/1500;
	static int MOVEPOINT_CHANCE = BIG/1500;
	void mutate(std::vector<int*>* dna, int w, int h);
	bool addPoly(std::vector<int*>* dna, int w, int h);
	bool shiftPoly(std::vector<int*>* dna);
	bool removePoly(std::vector<int*>* dna);
	bool recolor(std::vector<int*>* dna, int i, int value);
	bool movePoint(std::vector<int*>* dna, int i, int w, int h);
}


