#pragma once

#include "SFML/Graphics.hpp"
#include "noise/noise.h"
#include "../json/json/json.h"
#include "../json/Loader.h"
#include <iostream>
#include <fstream>

enum WorldType
{
	SYMETRY,
	TERRA
};

class World
{
private:
	void generateGeneric(noise::module::RidgedMulti ridged,
		noise::module::Perlin perlin, noise::module::Perlin perlin2);
public:

	sf::Image elevation;
	sf::Image rainfall;
	sf::Image biome;
	sf::Image resources;
	sf::Image climate;

	std::string name = "NOT_SET";

	WorldType type = WorldType::TERRA;
	unsigned int seed = 1241;
	int width = 128;
	int height = 128;
	float detail = 1.4f;
	float connection = 1.4;
	float mountains = 2.5;
	int seaLevel = 60;
	bool smooth = true;
	float islands = 0.15;
	int polarCap = 10;
	int polarCapRand = 10;
	float rivers = 10;
	bool invert = false;

	//Generates map to images from given data
	void generate(WorldType type = WorldType::TERRA);

	//Generates map to images from given data
	//(Type A, Symetric, deprecated)
	void generateA();
	//Generates map to images from given data
	//(Type B, Earth like, does not
	//wrap around, but just has oceans around)
	void generateB();


	//Writes file data to a ASCII file
	void saveToFile(std::string path);

	//Loads a world file and prepares for game usage
	bool load(std::string path);

	World();
	~World();
};

