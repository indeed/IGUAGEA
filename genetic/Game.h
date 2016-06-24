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
	std::array<std::array<int, G_HEIGHT>, G_WIDTH> _board;
	std::vector<Player*> _players;
	std::vector<std::array<int, 2>> _food;
	Direction _inputDirection = Direction::RIGHT;
public:
	Game();
	sf::RenderWindow* getWindow();
	int getBoardPos(int x, int y);
	void run();
	void step();
	void render();
	void spawnFood();
	~Game();
};