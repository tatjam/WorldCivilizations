#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "../World/World.h"

//Basic unit class, created from data
//in a .json file
class Unit
{
private:
	int heuristic(sf::Vector2u a, sf::Vector2u b)
	{
		return abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y);
	}
public:

	//For now only basic stuff, later more stuff will come

	//ID holds the unit id, used when rendering
	std::string id;
	
	int x;
	int y;

	//In tiles per turn
	int moveSpeed = 2;

	//Is the unit naval
	bool naval = false;

	//Can the unit embark?
	//Should change upon technological discovery
	bool canEmbark = true;

	//List of moves to do in following turns
	//Move of [n]999, [n]999 means embark into
	//move([n]1, [n]1)
	std::vector<sf::Vector2u> moves;

	void setLocation(int nx, int ny);

	//A* path to location, will build move tree
	void pathTo(int x, int y, World* world);

	Unit();
	~Unit();
};

