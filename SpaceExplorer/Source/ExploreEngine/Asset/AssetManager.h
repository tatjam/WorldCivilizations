#pragma once
#include <map>
#include "SFML/Graphics.hpp"
#include "../../json/Loader.h"
#include "../../json/json/json.h"
#include "../../dirent/dirent.h"
#include "../Sprite.h"

namespace Explore
{

	class AssetManager
	{
	public:

		std::map<std::string, sf::Image> images;

		//Searches for all .json files in the root art directory and loads all given data
		void load();

		Sprite getSprite(std::string texture);

		sf::Texture getTexture(std::string s);

		AssetManager();
		~AssetManager();
	};

}
