#include "stdafx.h"
#include "Game.h"
#include "Ai.h"

#include <iostream>

Game::Game()
{
	_board = { {0} };
	_gameWindow = new sf::RenderWindow(sf::VideoMode(G_WIDTH * G_SCALE, G_HEIGHT * G_SCALE), "Competitive Snake");
	// Create player character
	_players.push_back(new Player(5, 5));
	_players[0]->setHuman(true);
	_players.push_back(new Player(5, 20));
	_players.push_back(new Player(40, 5));
	_players.push_back(new Player(40, 20));
}

sf::RenderWindow* Game::getWindow() {
	return _gameWindow;
}

std::array<std::array<int, G_HEIGHT>, G_WIDTH>* Game::getBoard() {
	return &_board;
}

void Game::run() {

	_gameWindow->setFramerateLimit(G_TICKSPERSECOND);

	for (int i = 0; i < G_FOODNUMBER; i++) {
		spawnFood();
	}
	
	// Main game window loop
	while (_gameWindow->isOpen())
	{
		sf::Event event;
		while (_gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_gameWindow->close();
			}
			// Handle Keypress events w/ SFML
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					if (_inputDirection != Direction::DOWN)
					_inputDirection = Direction::UP;
					break;
				case sf::Keyboard::S:
					if (_inputDirection != Direction::UP)
					_inputDirection = Direction::DOWN;
					break;
				case sf::Keyboard::A:
					if (_inputDirection != Direction::RIGHT)
					_inputDirection = Direction::LEFT;
					break;
				case sf::Keyboard::D:
					if (_inputDirection != Direction::LEFT)
					_inputDirection = Direction::RIGHT;
					break;
				}
			}
		}
		// Call stuff
		step();
		render();
		_gameWindow->display();
	}
}

// Run once per tick to render all rectangles on grid
void Game::render() {
	_gameWindow->clear();
	// Decorate food to make it stand out
	sf::CircleShape decor(G_SCALE/2-2);
	decor.setFillColor(sf::Color(250,120,100,160));
	sf::RectangleShape tile; // Rectangular tiles to copy and render over board
	tile.setSize(sf::Vector2f(G_SCALE, G_SCALE));
	tile.setOutlineColor(sf::Color(0, 0, 0, 150));
	tile.setOutlineThickness(-1);

	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			if (!Globals::withinBounds(i, j)) {
				// Danger tiles
				tile.setFillColor(sf::Color(0,0,0, 255));
			}
			else if (_board[i][j] == 0) {
				// Set to default dark grey if tile is empty
				tile.setFillColor(sf::Color(32, 32, 32, 255));
			}
			else {
				tile.setFillColor(sf::Color(
					_board[i][j] / (256 * 256),
					(_board[i][j] / 256) % (256),
					_board[i][j] % 256, 255));
				//Set color to BASE 256 encoded id of player on that tile
			}
			tile.setPosition(i * G_SCALE, j * G_SCALE);
			_gameWindow->draw(tile);
			if (_board[i][j] == FOOD_ID) {
				decor.setPosition(i * G_SCALE+2, j * G_SCALE+2);
				_gameWindow->draw(decor);
			}
		}
	}
}

// Main loop to process game events
void Game::step() {
	std::array<std::array<int, G_HEIGHT>, G_WIDTH> _temp;
	for (int i = 0; i < _players.size(); i++) {
		if (!_players[i]->isDead()) {
			// Grab position of the head block
			int headX = _players[i]->getHeadPos()[0];
			int headY = _players[i]->getHeadPos()[1];

			if (_players[i]->isHuman()) {
				_players[i]->move(_inputDirection);
			}
			else {
				_players[i]->move(bestMove(headX, headY));
			}

			headX = _players[i]->getHeadPos()[0];
			headY = _players[i]->getHeadPos()[1];
			
			// Check if player is within the game bounds
			if (Globals::withinBounds(headX, headY) && (_board[headX][headY] == 0 || _board[headX][headY] == NULL || _board[headX][headY] == FOOD_ID)) {
				if (_board[headX][headY] == FOOD_ID) {
					_players[i]->addLength(G_FOODVALUE);
					spawnFood();
				}
				for (int j = 0; j < _players[i]->getLength(); j++) {
					// Set each tile on the board to the corresponding player it belongs to
					int x = (_players[i]->getSegment(j))[0];
					int y = (_players[i]->getSegment(j))[1];
					_board[x][y] = _players[i]->getId();
					_temp[x][y] = 1;
				}
			}
			else {
				_players[i]->death();
				for (int j = 0; j < _players[i]->getLength() - 1; j += 3) {
					// Spawn food where player died
					int x = (_players[i]->getSegment(j))[0];
					int y = (_players[i]->getSegment(j))[1];
					_board[x][y] = FOOD_ID;
				}
			}
		}
	}
	// Clean up board for next tick
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			if (_temp[i][j] != 1 && _board[i][j] != FOOD_ID) {
				_board[i][j] = 0;
			}
		}
	}
}

void Game::spawnFood() {
	bool done = false;
	int x, y;
	// Randomly find a place to spawn food
	while (!done) {
		x = rand() % (G_WIDTH - 2) + 1;
		y = rand() % (G_HEIGHT - 2) + 1;
		if (_board[x][y] == 0 || _board[x][y] == NULL) {
			done = true;
			_board[x][y] = FOOD_ID;
		}
	}
}

Direction Game::bestMove(int x, int y) {
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
				if ((_board)[x][y - 1] == 0 || (_board)[x][y - 1] == FOOD_ID || (_board)[x][y - 1] == NULL) {
					return Direction::UP;
				}
			}
			break;
		case 1:
			if (y < G_HEIGHT) {
				if ((_board)[x][y + 1] == 0 || (_board)[x][y + 1] == FOOD_ID || (_board)[x][y + 1] == NULL) {
					return Direction::DOWN;
				}
			}
			break;
		case 2:
			if (x > 0) {
				if ((_board)[x - 1][y] == 0 || (_board)[x - 1][y] == FOOD_ID || (_board)[x - 1][y] == NULL) {
					return Direction::LEFT;
				}
			}
			break;
		case 3:
			if (x < G_WIDTH) {
				if ((_board)[x + 1][y] == 0 || (_board)[x + 1][y] == FOOD_ID || (_board)[x + 1][y] == NULL) {
					return Direction::RIGHT;
				}
			}
			break;
		}
	}
}

Game::~Game()
{
	for (int i = 0; i < _players.size(); i++) {
		delete _players[i];
	}
}