#pragma once
#include "Renderer/RenderLayer.h"

#include <vector>
#include <map>

namespace Explore
{
	class Scene
	{
	public:

		std::map<int, RenderLayer> layers;

		//If the layer is at the same z as another layer
		//or the operation fails it will return false
		bool insertLayer(RenderLayer layer);

		//This one allows you to feed the z
		bool insertLayer(RenderLayer layer, int z);

		//Get a layer from z
		RenderLayer* getLayer(int z);

		//Does nothing if layer does not exists
		void deleteLayer(int z);

		//Draw all renderlayers
		void draw(sf::RenderWindow* window);

		Scene();
		~Scene();
	};
}
