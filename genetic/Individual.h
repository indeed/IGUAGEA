#pragma once
#include <SFML/Graphics.hpp>
#include "Genome.h"

class Individual
{
private:
	sf::Image _image;
	int genome;
	int _height;
	int _width;
	int _scale;
	int *_colorData;
	int BASE = 256;
	sf::RenderWindow *_window;
	// DNA is composed of a series of triangles denoted by a 10 length array:
	// [x1, y1, x2, y2, x3, y3, r, g, b, alpha]
	std::vector<int*> _dna;
public:
	Individual();
	Individual(sf::Vector2u size, int scale, sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void mutate();
	long long getFitness(int* sourceData);
	void generate();
	void copyDNA(std::vector<int*>* dna);
	std::vector<int*>* getDNA();
	~Individual();
};

