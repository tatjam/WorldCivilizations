#pragma once
#include "SFML/Graphics.hpp"


//Keeps a sprite with a texture
class Sprite
{
public:

	sf::Texture t;
	sf::Sprite s;

	Sprite(sf::Texture tex)
	{
		s = sf::Sprite();
		t = tex;
		s.setTexture(t);
	}
	Sprite()
	{

	}
	~Sprite()
	{

	}
};

