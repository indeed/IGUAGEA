#pragma once
#include <SFML/Graphics.hpp>
#include "Individual.h"

class Simulation
{
private:
	sf::RenderWindow *_window_gen; // Hidden window to render successive generations
	sf::RenderWindow *_window_disp;
	sf::Image _source;
	sf::Vector2u _size;
	int _scale = 1;
	int *_colorData;
	int BASE = 256;
	Individual *_fittest;
	Individual *_challenger;
	long long _maxFitness;
	long long _c;
	int _generation = 0;
public:
	Simulation();
	sf::RenderWindow* getWindow();
	void run();
	int* getColorData();
	void step();
	~Simulation();
};

