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

	unsigned int seed = 1241;
	int width = 128;
	int height = 128;
	int detail = 1.4;
	float connection = 1.4;
	float mountains = 2.5;
	int seaLevel = 60;
	bool smooth = true;
	float islands = 0.15;
	int polarCap = 10;
	int polarCapRand = 10;


	//Generates map to images from given data
	void generate();

	//Writes file data to a ASCII file
	void saveToFile(std::string path);

	//Loads a world file and prepares for game usage
	bool load(std::string path);

	World();
	~World();
};

