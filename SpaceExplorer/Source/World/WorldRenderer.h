#pragma once
#include "../ExploreEngine/Scene/Scene.h"
#include "World.h"
#include "../ExploreEngine/Asset/AssetManager.h"
#include "../ExploreEngine/Engine.h"
#include "../Unit/Unit.h"


using namespace Explore;

class WorldRenderer
{
private:
	void renderGround(sf::FloatRect view);
	void renderUnits(sf::FloatRect view, std::vector<Unit*> units);
public:

	int tSide = 16;

	int camX = 0;
	int camY = 0;
	float camZoom = 1.0f;

	Scene* scene;
	Engine* engine;
	RenderLayer ground;
	RenderLayer overlay;
	World*  world;
	sf::View* view;

	std::map<std::string, sf::Texture> landCache = std::map<std::string, sf::Texture>();
	std::map<std::string, sf::Texture> unitCache = std::map<std::string, sf::Texture>();

	//Uploads all sprites into the scene (use scene.render())
	void setup(sf::FloatRect viewRect, std::vector<Unit*> units);

	void loadData();

	WorldRenderer(Scene* scene, Engine* engine, World* world, sf::View* view);
	~WorldRenderer();

};

