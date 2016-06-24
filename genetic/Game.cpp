#include "stdafx.h"
#include "Game.h"

#include <iostream>

Game::Game()
{
	_board = {{0}};
	_gameWindow = new sf::RenderWindow(sf::VideoMode(G_WIDTH * _scale, G_HEIGHT * _scale), "Generated Image");
}

sf::RenderWindow* Game::getWindow() {
	return _gameWindow;
}

std::array<std::array<int, G_HEIGHT>, G_WIDTH>* Game::getBoard() {
	return &_board;
}

void Game::run() {
	_gameWindow->setFramerateLimit(30);
	while (_gameWindow->isOpen())
	{
		sf::Event event;
		while (_gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_gameWindow->close();
		}
		step();
		render();
		_gameWindow->display();
	}
}

void Game::render() {
	_gameWindow->clear();
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			//if (_board[i][j] == 1) {
			sf::RectangleShape tile;
			tile.setSize(sf::Vector2f(_scale, _scale));
			tile.setOutlineColor(sf::Color(255,255,255,50));
			tile.setFillColor(sf::Color::Transparent);
			tile.setOutlineThickness(-1);
				tile.setPosition(i * _scale, j * _scale);
				_gameWindow->draw(tile);
			//}
		}
	}
}

void Game::step() {

}

Game::~Game()
{

}