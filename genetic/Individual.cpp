#include "stdafx.h"
#include "Individual.h"

#include <SFML/Graphics.hpp>
#include <stdlib.h> // math

Individual::Individual()
{

	image = window.capture();

	size = image.getSize();
	colorData = new int[size.x * size.y];

	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			// Store pixel data in 1D array for contiguous memory access
			// Colors stored as RGB in base 256 by default, as an int from 0 to 256^3
			colorData[i*size.y + j] = image.getPixel(i, j).r * BASE * BASE
				+ image.getPixel(i, j).g * BASE
				+ image.getPixel(i, j).b;
		}
	}
}

int Individual::getFitness(int* sourceData, int size) {
	sf::Image image;
	long fitness = 0;
	int pfit;
	for (int i = 0; i < size; i++) {
		pfit = abs(sourceData[i] / (BASE * BASE) - colorData[i] / (BASE * BASE)) // Red difference
			+ abs((sourceData[i] / (BASE)) % BASE - (colorData[i] / (BASE)) % BASE) // Green difference
			+ abs(sourceData[i] % BASE - colorData[i] % BASE); // Blue difference
		pfit = pfit * pfit; // Difference squared
		fitness += pfit;
	}
	return fitness / 1000;
}

Individual::~Individual()
{
}
