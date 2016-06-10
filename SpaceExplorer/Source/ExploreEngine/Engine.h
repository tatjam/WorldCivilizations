#pragma once
#include <string>

namespace Explore
{

	class Engine
	{

	public:


		//Updates everything, returns false if program finishes
		bool update();

		//Renders everything
		void draw();

		//Initializes the game engine, loads all data, and starts the game
		void setup();

		Engine();
		~Engine();


	};

}