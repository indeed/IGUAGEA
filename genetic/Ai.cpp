#include "stdafx.h"
#include "Ai.h"

std::array<std::array<int, G_HEIGHT>, G_WIDTH>* Ai::_board;

void Ai::setBoard(std::array<std::array<int, G_HEIGHT>, G_WIDTH> *board) {
	_board = board;
}

Direction Ai::bestMove(int x, int y) {
	/*_queue.push_back(xy{x, y});
	while (!_queue.empty()) {
		int i = _queue.size() - 1;
		while (i >= 0) {
			xy n = _queue[i];
			_visited.push_back(n);
			_queue.erase(_queue.begin());
			i--;
		}
	}
	return */

	// Easy AI for now

	// Semi RNG with a chance of making a mistake
	for (int i = 0; i < 20; i++) {
		int chosen = rand() % 4;
		switch (chosen) {
		case 0:
			if (y > 0) {
				if ((*_board)[x][y - 1] == 0 || (*_board)[x][y - 1] == FOOD_ID || (*_board)[x][y - 1] == NULL) {
					return Direction::UP;
				}
			}
			break;
		case 1:
			if (y < G_HEIGHT) {
				if ((*_board)[x][y + 1] == 0 || (*_board)[x][y + 1] == FOOD_ID || (*_board)[x][y + 1] == NULL) {
					return Direction::DOWN;
				}
			}
			break;
		case 2:
			if (x > 0) {
				if ((*_board)[x - 1][y] == 0 || (*_board)[x - 1][y] == FOOD_ID || (*_board)[x - 1][y] == NULL) {
					return Direction::LEFT;
				}
			}
			break;
		case 3:
			if (x < G_WIDTH)  {
				if ((*_board)[x + 1][y] == 0 || (*_board)[x + 1][y] == FOOD_ID || (*_board)[x + 1][y] == NULL) {
					return Direction::RIGHT;
				}
			}
			break;
		}
	}
}
