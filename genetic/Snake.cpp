// genetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include <ctime>
#include <iostream>

int main()
{
	std::srand(std::time(0));
	std::cout << "##############################################" << std::endl;
	std::cout << "#...._________........._________.............#" << std::endl;
	std::cout << "#.../+++++++++\\......./+++++++++\\............#" << std::endl;
	std::cout << "#../++/~~~~~\\++\\...../++/~~~~~\\++\\...........#" << std::endl;
	std::cout << "#..|++|.....|++|.....|++|.....|++|...........#" << std::endl;
	std::cout << "#..|++|.....|++|.....|++|.....|++|...........#" << std::endl;
	std::cout << "#..|++|.....|++|.....|++|.....|++|........./.#" << std::endl;
	std::cout << "#..|++|.....|++|.....|++|.....|++|...... //..#" << std::endl;
	std::cout << "#.(o++o)....\\++\\_____/++/.....\\++\\_____/+/...#" << std::endl;
	std::cout << "#..\\__/......\\+++++++++/.......\\++++++++/....#" << std::endl;
	std::cout << "#...|.........~~~~~~~~~.........~~~~~~~~.....#" << std::endl;
	std::cout << "#...^........................................#" << std::endl;
	std::cout << "##############################################" << std::endl;

	while (1) {
		std::cout << "WELCOME TO COMPETITIVE SNAKE" << std::endl << std::endl;
		std::cout << "ENTER NUMBER OF PLAYERS [4]: ";
		int players = 4;
		std::cin >> players;
		std::cout << std::endl << std::endl << "GAME STARTED!" << std::endl << "PRESS ESC TO EXIT CURRENT MATCH" << std::endl;
		Game game(players);
		game.run();
		std::cout << "GAME ENDED!" << std::endl << std::endl;
	}

	return 0;
}

