#pragma once

class Individual
{
private:
	sf::Image image;
	int genome;
	sf::Vector2u size;
	int *colorData;
	int BASE = 256;
	sf::RenderWindow window;
public:
	Individual();
	int getFitness(int* sourceData, int size);

	~Individual();
};

