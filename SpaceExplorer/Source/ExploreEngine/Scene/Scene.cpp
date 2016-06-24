#include "Scene.h"
#include <iostream>

using namespace Explore;


void Scene::update()
{
	return;
}

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

void Scene::draw(sf::RenderWindow* w)
{

	for (auto layer : layers)
	{
		layer.second.draw(w);
	}

}

Scene::Scene()
{

}


Scene::~Scene()
{
}
