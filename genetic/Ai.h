#pragma once
#include "Player.h"
#include "Globals.h"

class Ai
{
private:
	static std::array<std::array<int, G_HEIGHT>, G_WIDTH>* _board;
	//static std::vector<xy> _queue;
	//static std::vector<xy> _visited;
public:
	static void setBoard(std::array<std::array<int, G_HEIGHT>, G_WIDTH>* _board);
	static Direction bestMove(int x, int y);
};

// Nice tuple struct for BFS
struct xy {
	int x;
	int y;
};