#include "Scene.h"

using namespace Explore;


bool Scene::insertLayer(RenderLayer layer)
{
	return Scene::insertLayer(layer, layer.z);
}

bool Scene::insertLayer(RenderLayer layer, int z)
{
	if (layers.count(z) >= 1)
	{
		//Return false if the layer already contains key
		return false;
	}

	//Otherwise add it
	layers[z] = layer;
}


RenderLayer* Scene::getLayer(int z)
{
	return &layers[z];
}


void Scene::deleteLayer(int z)
{
	layers.erase(z);
}

Scene::Scene()
{
}


Scene::~Scene()
{
}
