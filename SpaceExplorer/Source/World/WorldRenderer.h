#pragma once
#include "../ExploreEngine/Scene/Scene.h"
#include "World.h"
#include "../ExploreEngine/Asset/AssetManager.h"
#include "../ExploreEngine/Engine.h"


using namespace Explore;

class WorldRenderer
{
private:

public:

	int camX = 0;
	int camY = 0;
	float camZoom = 1.0f;

	Scene* scene;
	Engine* engine;
	RenderLayer ground;
	World*  world;
	sf::View* view;

	std::map<std::string, sf::Texture> landCache = std::map<std::string, sf::Texture>();

	//Uploads all sprites into the scene.
	//To render use scene.render()
	void setup(sf::FloatRect viewRect);

	void loadData();

	WorldRenderer(Scene* scene, Engine* engine, World* world, sf::View* view);
	~WorldRenderer();

};

