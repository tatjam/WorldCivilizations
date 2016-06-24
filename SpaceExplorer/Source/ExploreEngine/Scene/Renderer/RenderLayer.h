#pragma once
#include "../../Entity/Entity.h"
#include "../../Sprite.h"

#include <vector>
#include "SFML/Graphics.hpp"

namespace Explore
{

	//Very simple class to store a lot of sprites in a single layer
	class RenderLayer
	{
	public:

		std::vector<Sprite> sprites;

		//Z is used only when inserting, changing it will do nothing
		int z = 0;

		//Call this to render all entities
		void draw(sf::RenderWindow* window);

		RenderLayer();
		~RenderLayer();
	};
}

