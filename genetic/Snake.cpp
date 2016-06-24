// genetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include <ctime>

int main()
{
	std::srand(std::time(0));
	Game game;
	game.run();
	return 0;
}

