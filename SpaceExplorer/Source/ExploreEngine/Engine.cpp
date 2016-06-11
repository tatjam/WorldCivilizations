#include "Engine.h"

using namespace Explore;


bool Engine::update()
{
	scene->update();
	return true;
}

void Engine::draw()
{
	scene->draw(&window);
}

void Engine::setup()
{
	//Load from default settings.json file
	/*Json::Value root;

	//Read file into string

	std::ifstream in("/res/settings.json");
	std::string settingsFile((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());*/
}

Engine::Engine()
{
}


Engine::~Engine()
{
}
