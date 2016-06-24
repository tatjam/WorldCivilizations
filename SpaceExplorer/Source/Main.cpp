#include <iostream>
#include <SFML/Graphics.hpp>
#include <noise/noise.h>
#include "World/World.h"
#include "World/WorldRenderer.h"
#include "ExploreEngine/Asset/AssetManager.h"
#include "ExploreEngine/Engine.h"

using namespace Explore;

int main()
{

	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML works!");
	window.setFramerateLimit(60);

	AssetManager manager = AssetManager();



	std::cout << "Starting asset load" << std::endl;

	manager.load();

	Scene scene = Scene();
	Engine engine = Engine();
	engine.manager = manager;

	sf::View view = sf::View();

	World world = World();
	world.width = 256;
	world.height = 128;
	world.seaLevel = 120;
	world.detail = 200;
	world.connection = 0;
	world.polarCap = 6;
	world.seed = 541353;
	world.rivers = 10;
	world.invert = false;
	world.generate();

	WorldRenderer render = WorldRenderer(&scene, &engine, &world, &view);
	sf::FloatRect testView = sf::FloatRect();
	testView.top = 0;
	testView.left = 0;
	testView.width = 15;
	testView.height = 15;
	render.loadData();
	render.setup(testView);


	sf::Sprite sp = sf::Sprite();
	sf::Texture tex = sf::Texture();

	tex.loadFromImage(world.biome);
	sp.setTexture(tex);
	sp.setScale(5, 5);
	tex.setSmooth(false);


	sf::RectangleShape rect = sf::RectangleShape();
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(15 * 5, 15 * 5));
	rect.setPosition(0 * 5, 0 * 5);
	rect.setOutlineThickness(2.0f);

	sf::Clock dc = sf::Clock();
	sf::Time dt = sf::Time();

	sp.setPosition(256, 256);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			testView.top -= 10.0f * dt.asSeconds();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			testView.left -= 10.0f * dt.asSeconds();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			testView.top += 10.0f * dt.asSeconds();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			testView.left += 10.0f * dt.asSeconds();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			testView.width -= 10.0f * dt.asSeconds();
			testView.height -= 10.0f * dt.asSeconds();
			view.zoom(0.99f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			testView.width += 10.0f * dt.asSeconds();
			testView.height += 10.0f * dt.asSeconds();
			view.zoom(1.01f);
		}

		//view.zoom(0.9999f);

		render.setup(testView);

		float rX = fmod(testView.left, world.biome.getSize().x);
		float rY = fmod(testView.top, world.biome.getSize().y);

		testView.top = rY;
		testView.left = rX;

		rect.setSize(sf::Vector2f(testView.width * 5, testView.height * 5));
		rect.setPosition(testView.left * 5 + 256, testView.top * 5 + 256);

		window.setView(view);
		window.clear();
		scene.draw(&window);
		window.draw(sp);
		window.draw(rect);
		window.display();

		dt = dc.restart();
		//std::cout << dt.asSeconds() << "s" << "," << 1 / dt.asSeconds() << "fps" << std::endl;
	}

	return 0;
}