#include "stdafx.h"
#include "Game.h"

#include <iostream>

Game::Game()
{
	_board = { {0} };
	_gameWindow = new sf::RenderWindow(sf::VideoMode(G_WIDTH * _scale, G_HEIGHT * _scale), "Generated Image");
	_players.push_back(new Player(20, 20));
}

sf::RenderWindow* Game::getWindow() {
	return _gameWindow;
}

std::array<std::array<int, G_HEIGHT>, G_WIDTH>* Game::getBoard() {
	return &_board;
}

void Game::run() {
	_gameWindow->setFramerateLimit(24);

	spawnFood();

	while (_gameWindow->isOpen())
	{
		sf::Event event;
		while (_gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_gameWindow->close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					_inputDirection = Direction::UP;
					break;
				case sf::Keyboard::S:
					_inputDirection = Direction::DOWN;
					break;
				case sf::Keyboard::A:
					_inputDirection = Direction::LEFT;
					break;
				case sf::Keyboard::D:
					_inputDirection = Direction::RIGHT;
					break;
				}
			}
		}
		step();
		render();
		_gameWindow->display();
	}
}

void Game::render() {
	_gameWindow->clear();

	sf::RectangleShape tile; // Rectangular tiles to copy and render over board
	tile.setSize(sf::Vector2f(_scale, _scale));
	tile.setOutlineColor(sf::Color(0, 0, 0, 100));
	tile.setOutlineThickness(-1);

	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			if (_board[i][j] == 0) {
				tile.setFillColor(sf::Color(32, 32, 32, 255));
				// Set to default dark grey if tile is empty
			}
			else {
				tile.setFillColor(sf::Color(
					_board[i][j] / (256 * 256),
					(_board[i][j] / 256) % (256),
					_board[i][j] % 256, 255));
				//Set color to BASE 256 encoded id of player on that tile
			}
			tile.setPosition(i * _scale, j * _scale);
			_gameWindow->draw(tile);
		}
	}
}

// Main loop to process game events
void Game::step() {
	std::array<std::array<int, G_HEIGHT>, G_WIDTH> _temp;
	for (int i = 0; i < _players.size(); i++) {
		_players[i]->move(_inputDirection);
		// Check if player is within the game bounds
		int headX = _players[i]->getHeadPos()[0];
		int headY = _players[i]->getHeadPos()[1];
		if (Globals::withinBounds(headX, headY)) {
			if (_board[headX][headY] == FOOD_ID) {
				_players[i]->addLength(G_FOODVALUE);
				spawnFood();
				std::cout << _players[i]->getLength();
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
			_players[0]->setLength(0);
		}
	}

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
		x = rand() % G_WIDTH;
		y = rand() % G_HEIGHT;
		if (_board[x][y] == 0 || _board[x][y] == NULL) {
			done = true;
			_board[x][y] = FOOD_ID;
		}
	}
}

Game::~Game()
{
	for (int i = 0; i < _players.size(); i++) {
		delete _players[i];
	}
}