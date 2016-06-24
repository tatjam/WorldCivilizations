#pragma once
#include <string>

#include "../json/Loader.h"
#include "../json/json/json.h"
#include "../dirent/dirent.h"

#include <string>
#include "Asset/AssetManager.h"

namespace Explore
{

	class Scene;

	class Engine
	{

	public:

		sf::RenderWindow* window;

		Scene* scene;

		//Updates everything, returns false if program finishes
		bool update();

		//Renders everything
		void draw();

		//Initializes the game engine, loads all data, and starts the game
		void setup();

		AssetManager manager;

		Engine();
		~Engine();


	};

}