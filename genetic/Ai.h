#pragma once
#include "Player.h"
#include "Game.h"
#include "Globals.h"

// Nice 4 var set struct for BFS
struct xy {
	int x;
	int y;
	int a;
	int b;
};

class Ai
{
private:
	static Game *_game;
	static std::vector<xy> _queue;
	static std::vector<xy> _visited;
public:
	static void attachGame(Game* g);
	static Direction bestMove(int x, int y);
	static xy possibleMoves(int x, int y);
	static bool visited(xy a);
	static bool equal(xy a, xy b);
	static int minDistToFood(int x, int y);
};

