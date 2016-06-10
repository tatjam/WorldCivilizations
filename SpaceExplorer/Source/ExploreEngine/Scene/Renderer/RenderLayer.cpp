#include "RenderLayer.h"

using namespace Explore;

void RenderLayer::draw(sf::RenderWindow* w)
{
	for (sf::Sprite* s : sprites)
	{
		w->draw(*s);
	}
}

RenderLayer::RenderLayer()
{
}


RenderLayer::~RenderLayer()
{
}
