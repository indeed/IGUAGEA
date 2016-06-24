#pragma once
#include <vector>

#define G_WIDTH 64
#define G_HEIGHT 48
#define G_SCALE 12
#define G_FOODVALUE 1
#define G_FOODNUMBER 10
#define G_TICKSPERSECOND 20
#define FOOD_ID (255 * 256 * 256 + 255 * 256 + 255)
#define MATH_HUGE 1000000000

class Globals
{
private:
	static std::vector<int> _usedId;
public:
	static int uniqueId();
	static bool withinBounds(int x, int y);
};

enum class Direction { UP, DOWN, LEFT, RIGHT };