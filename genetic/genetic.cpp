// genetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{

	sf::Image source;
	int scale = 2;
	int *colorData;
	int BASE = 256;

	if (!source.loadFromFile("meme.jpg")) {
		return -1;
	}

	sf::Vector2u size = source.getSize();

	colorData = new int[size.x * size.y];

	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			// Store pixel data in 1D array for contiguous memory access
			// Colors stored as RGB in base 256 by default, as an int from 0 to 256^3
			colorData[i*size.y + j] = source.getPixel(i,j).r * BASE * BASE
				+ source.getPixel(i,j).g * BASE
				+ source.getPixel(i,j).b;
		}
	}

	sf::RenderWindow window_gen(sf::VideoMode(size.x*scale, size.y*scale), "Generated Image");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Image image = window_gen.capture();
	while (window_gen.isOpen())
	{
		sf::Event event;
		while (window_gen.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_gen.close();
		}

		window_gen.clear();
		window_gen.draw(shape);
		window_gen.display();
	}
	
	delete[] color_data;
	return 0;
}

