// genetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Simulation.h"
#include <ctime>

int main()
{
	std::srand(std::time(0));
	Simulation sim;
	sim.run();
	return 0;
}

