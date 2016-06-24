#include "RenderLayer.h"
#include <iostream>

using namespace Explore;

void RenderLayer::draw(sf::RenderWindow* w)
{
	for (Sprite s : sprites)
	{
		w->draw(s.s);
	}
}

RenderLayer::RenderLayer()
{
}


RenderLayer::~RenderLayer()
{
}
