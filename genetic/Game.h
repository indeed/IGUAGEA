#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Player.h"
#include "Globals.h"

class Game
{
private:
	sf::RenderWindow *_gameWindow;
	sf::Image _source;
	sf::Vector2u _size;
	int _scale = 16;
	std::array<std::array<int, G_HEIGHT>, G_WIDTH> _board;
	std::vector<Player> _players;
public:
	Game();
	sf::RenderWindow* getWindow();
	std::array<std::array<int, G_HEIGHT>, G_WIDTH>* getBoard();
	void run();
	void step();
	void render();
	~Game();
};