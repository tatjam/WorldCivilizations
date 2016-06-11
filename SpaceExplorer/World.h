#pragma once

#include "SFML/Graphics.hpp"
#include "noise/noise.h"

class World
{
public:

	sf::Image elevation;
	sf::Image rainfall;
	sf::Image biome;
	sf::Image resources;
	sf::Image climate;

	unsigned int seed;
	int width;
	int height;
	int detail;
	float connection;
	float mountains;
	int seaLevel;
	unsigned int seed;
	bool smooth = true;
	float islands = 0.15;



	//Generates map to images from given data
	void generate();

	//Writes file data to a ASCII file
	void saveToFile(std::string path);

	//Loads a world file and prepares for game usage
	bool load(std::string path);

	World();
	~World();
};

