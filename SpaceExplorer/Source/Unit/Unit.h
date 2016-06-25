#pragma once
#include <string>

//Basic unit class, created from data
//in a .json file
class Unit
{
public:

	//For now only basic stuff, later more stuff will come

	//ID holds the unit id, used when rendering
	std::string id;
	
	int x;
	int y;

	void setLocation(int nx, int ny);

	Unit();
	~Unit();
};

