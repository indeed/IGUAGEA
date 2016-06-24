#include "stdafx.h"
#include "Ai.h"
#include <iostream>

Game* Ai::_game;
std::vector<xy> Ai::_queue;
std::vector<xy> Ai::_visited;

// Set pointer to game instance to process board on
void Ai::attachGame(Game* g) {
	_game = g;
}

xy Ai::possibleMoves(int x, int y) {
	xy possible = xy{0,0,0,0};
	if (y > 1) {
		if (_game->getBoardPos(x, y - 1) == 0 || _game->getBoardPos(x, y - 1) == FOOD_ID || _game->getBoardPos(x, y - 1) == NULL) {
			possible.x = 1;
		}
	}
	if (y < G_HEIGHT - 1) {
		if (_game->getBoardPos(x, y + 1) == 0 || _game->getBoardPos(x, y + 1) == FOOD_ID || _game->getBoardPos(x, y + 1) == NULL) {
			possible.y = 1;
		}
	}
	if (x > 1) {
		if (_game->getBoardPos(x - 1, y) == 0 || _game->getBoardPos(x - 1, y) == FOOD_ID || _game->getBoardPos(x - 1, y) == NULL) {
			possible.a = 1;
		}
	}
	if (x < G_WIDTH - 1) {
		if (_game->getBoardPos(x + 1, y) == 0 || _game->getBoardPos(x + 1, y) == FOOD_ID || _game->getBoardPos(x + 1, y) == NULL) {
			possible.b = 1;
		}
	}
	return possible;
}

bool Ai::equal(xy a, xy b) {
	return (a.x == b.x && a.y == b.y && a.a == b.a && a.b == b.b);
}

bool Ai::visited(xy a) {
	for (int i = 0; i < _visited.size(); i++) {
		if (equal(_visited[i], a)) {
			return true;
		}
	}
	return false;
}

// BFS a little wonky
/*Direction Ai::bestMove(int x, int y) {
	
	_queue.push_back(xy{ 0, 0, x, y - 1 });
	_queue.push_back(xy{ 1, 0, x, y + 1 });
	_queue.push_back(xy{ 2, 0, x - 1, y });
	_queue.push_back(xy{ 3, 0, x + 1, y });
	while (!_queue.empty()) {
		xy n = _queue[0];
		_visited.push_back(n);
		xy possible = possibleMoves(n.a, n.b);
		xy next;
		if (_game->getBoardPos(n.a, n.b) == FOOD_ID) {
			switch (n.x) {
			case 0:
				return Direction::UP;
			case 1:
				return Direction::DOWN;
			case 3:
				return Direction::LEFT;
			case 4:
				return Direction::RIGHT;
			}
		}
		if (possible.x == 1) { // CAN GO UP
			next = n;
			next.b = n.b - 1;
			if (!visited(next)) {
				_queue.push_back(next);
			}
		}
		if (possible.y == 1) { // CAN GO DOWN
			next = n;
			next.b = n.b + 1;
			if (!visited(next)) {
				_queue.push_back(next);
			}
		}
		if (possible.a == 1) { // CAN GO LEFT
			next = n;
			next.a = n.a - 1;
			if (!visited(next)) {
				_queue.push_back(next);
			}
		}
		if (possible.b == 1) { // CAN GO RIGHT
			next = n;
			next.a = n.a + 1;
			if (!visited(next)) {
				_queue.push_back(next);
			}
		}
		_queue.erase(_queue.begin());
	}

	return Direction::UP;

}*/

int Ai::minDistToFood(int x, int y) {
	int minDist = MATH_HUGE;
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			if (_game->getBoardPos(i, j) == FOOD_ID) {
				int n = abs(x - i) + abs(y - j);
				minDist = (n < minDist) ? n : minDist;
			}
		}
	}
	return minDist;
}

Direction Ai::bestMove(int x, int y) {

	int bestmove[4][2] = { {0, MATH_HUGE}, {1, MATH_HUGE}, {2,MATH_HUGE}, {3, MATH_HUGE} };

	bestmove[0][1] = minDistToFood(x, y - 1);
	bestmove[1][1] = minDistToFood(x, y + 1);
	bestmove[2][1] = minDistToFood(x - 1, y);
	bestmove[3][1] = minDistToFood(x + 1, y);


	for (int i = 0; i < 4; ++i)
	{
		int min = i;
		for (int j = i + 1; j < 4; ++j)
		{
			if (bestmove[j][1] < bestmove[min][1])
			{
				min = j;
			}
		}

		if (min != i)
		{
			int temp[2] = { bestmove[min][0], bestmove[min][1] };
			bestmove[min][0] = bestmove[i][0];
			bestmove[min][1] = bestmove[i][1];
			bestmove[i][0] = temp[0];
			bestmove[i][1] = temp[1];
		}
	}

	xy possible = possibleMoves(x, y);
	for (int i = 0; i < 4; i++) {
		if (possible.x == 1 && bestmove[i][0] == 0) { // CAN GO UP
			return Direction::UP;
		}
		else if (possible.y == 1 && bestmove[i][0] == 1) { // CAN GO DOWN
			return Direction::DOWN;
		}
		else if (possible.a == 1 && bestmove[i][0] == 2) { // CAN GO LEFT
			return Direction::LEFT;
		}
		else if (possible.b == 1 && bestmove[i][0] == 3) { // CAN GO RIGHT
			return Direction::RIGHT;
		}
	}

	// Easy AI for now
	return Direction::RIGHT;
	// Semi RNG with a chance of making a mistake

}


