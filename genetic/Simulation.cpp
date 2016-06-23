#include "stdafx.h"
#include "Simulation.h"

#include <iostream>

Simulation::Simulation()
{
	if (!_source.loadFromFile("meme.jpg")) {
		exit(0);
	}

	_size = _source.getSize();
	_colorData = new int[_size.x * _size.y];

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) {
			// Store pixel data in 1D array for contiguous memory access
			// Colors stored as RGB in base 256 by default, as an int from 0 to 256^3
			_colorData[i*_size.y + j] = _source.getPixel(i, j).r * BASE * BASE
				+ _source.getPixel(i, j).g * BASE
				+ _source.getPixel(i, j).b;
		}
	}

	_window_gen = new sf::RenderWindow(sf::VideoMode(_size.x, _size.y), "");
	_window_disp = new sf::RenderWindow(sf::VideoMode(_size.x * _scale, _size.y * _scale), "Generated Image");
	_window_gen->setVisible(false);

	_fittest = new Individual(_size, _scale, _window_gen);
	_challenger = new Individual(_size, _scale, _window_gen);
	_fittest->mutate();
	_maxFitness = _fittest->getFitness(_colorData);

}

sf::RenderWindow* Simulation::getWindow() {
	return _window_gen;
}

int* Simulation::getColorData() {
	return _colorData;
}

void Simulation::run() {
	while (_window_disp->isOpen())
	{
		sf::Event event;
		while (_window_disp->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window_disp->close();
		}
		
		sf::Texture texture;
		texture.loadFromImage(_source);
		//_window_gen->clear();

		// Assign it to a sprite
		sf::Sprite sprite;
		sprite.setTexture(texture);
		// Draw the textured sprite
		_window_disp->draw(sprite);
		step();
		
		_fittest->render(_window_disp);
		_window_disp->display();
	}
}

void Simulation::step() {
	_generation += 1;
	_challenger->mutate();
	_c = _challenger->getFitness(_colorData);

	if (_c < _maxFitness) {
		_maxFitness = _c;
		_fittest->copyDNA(_challenger->getDNA());
		std::cout << _c << " " << _generation << std::endl;
	}
	else {
		_challenger->copyDNA(_fittest->getDNA());
	}
	
	// MUTATE AND EVALUATE INDIVIDUALS
}

Simulation::~Simulation()
{
	delete[] _colorData;
	delete _window_gen;
	delete _window_disp;
	delete _fittest;
}
