#include "stdafx.h"
#include "Individual.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h> // math
#include "Genome.h"

Individual::Individual() : Individual(sf::Vector2u(0, 0), 0, nullptr) {}

Individual::Individual(sf::Vector2u size, int scale, sf::RenderWindow* window)
{
	_width = size.x;
	_height = size.y;
	_scale = scale;
	_window = window;

	/*for (int i = 0; i < 10; i++) {
		int *poly = new int[10];
		// Generate vertices
		poly[0] = std::rand() % ((_width * 3)/2) - _width / 4;
		poly[1] = std::rand() % ((_height * 3)/2) - _height / 4;
		poly[2] = std::rand() % ((_width * 3)/2) - _width / 4;
		poly[3] = std::rand() % ((_height * 3)/2) - _height / 4;
		poly[4] = std::rand() % ((_width * 3)/2) - _width / 4;
		poly[5] = std::rand() % ((_height * 3)/2) - _height / 4;
		// Generate colors
		for (int j = 6; j < 10; j++) {
			poly[j] = std::rand() % 256;
		}
		_dna.push_back(poly);
	}*/
	generate();
}

void Individual::generate() {
	
	render(_window);

	// TODO: DRAW ON WINDOW

	_image = _window->capture();
	delete[] _colorData;
	_colorData = new int[_width * _height];

	for (int i = 0; i < _width; i ++) {
		for (int j = 0; j < _height; j ++) {
			// Store pixel data in 1D array for contiguous memory access
			// Colors stored as RGB in base 256 by default, as an int from 0 to 256^3
			_colorData[i*_height + j] = _image.getPixel(i, j).r * BASE * BASE
				+ _image.getPixel(i, j).g * BASE
				+ _image.getPixel(i, j).b;
		}
	}
}

void Individual::render(sf::RenderWindow* window) {
	window->clear();
	for (int i = 0; i < _dna.size(); i++) {
		// Define triangle
		sf::ConvexShape poly;
		poly.setPointCount(3);
		// Set vertices
		poly.setPoint(0, sf::Vector2f(_dna[i][0] * _scale, _dna[i][1] * _scale)); // { x1, y1 }
		poly.setPoint(1, sf::Vector2f(_dna[i][2] * _scale, _dna[i][3] * _scale)); // { x2, y2 }
		poly.setPoint(2, sf::Vector2f(_dna[i][4] * _scale, _dna[i][5] * _scale)); // { x3, y3 }
		// Set color
		poly.setFillColor(sf::Color(_dna[i][6], _dna[i][7], _dna[i][8], _dna[i][9]));
		window->draw(poly);
	}
}

long long Individual::getFitness(int* sourceData) {
	long long fitness = 0;
	int pfit = 0;
	for (int i = 0; i < _height * _width; i++) {
		pfit = abs(sourceData[i] / (BASE * BASE) - _colorData[i] / (BASE * BASE)) // Red difference
			+ abs((sourceData[i] / (BASE)) % BASE - (_colorData[i] / (BASE)) % BASE) // Green difference
			+ abs(sourceData[i] % BASE - _colorData[i] % BASE); // Blue difference
		
		fitness += pfit * pfit;
	}
	return fitness;
}

void Individual::mutate() {
	Genome::mutate(&_dna, _width, _height);
	generate();
}

void Individual::copyDNA(std::vector<int*>* dna) {
	_dna.clear();
	for (int i = 0; i < dna->size(); i++) {
		int *o = new int[10];
		for (int j = 0; j < 10; j++) {
			o[j] = (*dna)[i][j];
		}
		_dna.push_back(o);
	}
}

std::vector<int*>* Individual::getDNA() {
	return &_dna;
}

Individual::~Individual()
{
	delete[] _colorData;
	for (int i = 0; i < _dna.size(); i++) {
		delete[] _dna[i];
	}
}
