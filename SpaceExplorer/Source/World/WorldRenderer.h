#pragma once
#include "../ExploreEngine/Scene/Scene.h"
#include "World.h"
#include "../ExploreEngine/Asset/AssetManager.h"


using namespace Explore;

class WorldRenderer
{
public:

	int camX = 0;
	int camY = 0;
	float camZoom = 1.f;

	Scene* scene;
	RenderLayer ground;
	World*  world;

	//Uploads all sprites into the scene.
	//To render use scene.render()
	void setup();

	WorldRenderer(Scene* scene, World* world);
	~WorldRenderer();
};

