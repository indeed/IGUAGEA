#pragma once
#include <vector>

#define G_WIDTH 48
#define G_HEIGHT 32

class Globals
{
private:
	static std::vector<int> _usedId;
public:
	static int uniqueId();
};