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
	Unit testUnit = Unit();
	testUnit.id = "unitWorker";
	testUnit.setLocation(5, 5);

	std::vector<Unit*> units;
	units.push_back(&testUnit);

	sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
	window.setFramerateLimit(60);

	AssetManager manager = AssetManager();



	std::cout << "Starting asset load" << std::endl;

	manager.load();

	Scene scene = Scene();
	Engine engine = Engine();
	engine.manager = manager;

	sf::View view = sf::View();

	World world = World();
	world.width = 128;
	world.height = 64;
	world.seaLevel = 130;
	world.detail = 90;
	world.connection = 23;
	world.polarCap = 1;
	world.islands = 0.35;
	world.polarCapRand = 2;
	world.seed = 123456789;
	world.rivers = 10;
	world.invert = false;


	world.generate(WorldType::TERRA);

	world.load("./testoutput.json");

	WorldRenderer render = WorldRenderer(&scene, &engine, &world, &view);
	sf::FloatRect testView = sf::FloatRect();
	testView.top = 0;
	testView.left = 0;
	testView.width = view.getSize().x / 24;
	testView.height = view.getSize().y / 24;
	render.loadData();
	render.setup(testView, units);


	sf::Sprite sp = sf::Sprite();
	sf::Texture tex = sf::Texture();

	tex.loadFromImage(world.biome);
	sp.setTexture(tex);
	sp.setScale(2, 2);
	tex.setSmooth(false);


	sf::RectangleShape rect = sf::RectangleShape();
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(23 * 2, 23 * 2));
	rect.setPosition(0 * 2, 0 * 2);
	rect.setOutlineThickness(2.0f);

	sf::Clock dc = sf::Clock();
	sf::Time dt = sf::Time();

	sp.setPosition(0, 0);

	view.setSize(testView.width * 23, testView.height * 23);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::Resized)
			{
				view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
			}
		}

		if (testView.left < 0)
		{
			testView.left = world.width;
		}

		if (testView.top < 0)
		{
			testView.top = 0;
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
		
	

		if(testView.left)

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			testView.width -= 10.0f * dt.asSeconds();
			testView.height -= 10.0f * dt.asSeconds();
			view.move(-120 * dt.asSeconds(), -120 * dt.asSeconds());
			view.setSize(testView.width*24, testView.height*24);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			testView.width += 10.0f * dt.asSeconds();
			testView.height += 10.0f * dt.asSeconds();
			view.move(120 * dt.asSeconds(), 120 * dt.asSeconds());
			view.setSize(testView.width*24, testView.height*24);
		}

		//view.zoom(0.9999f);

		render.setup(testView, units);



		float rX = fmod(testView.left, world.biome.getSize().x);
		float rY = fmod(testView.top, world.biome.getSize().y);

		testView.top = rY;


		if (testView.top + testView.height >= world.height + 1)
		{
			testView.top = world.height - testView.height + 1;
		}


		testView.left = rX;

		rect.setSize(sf::Vector2f(testView.width * 2, testView.height * 2));
		rect.setPosition(testView.left * 2, testView.top * 2);

		window.setView(view);
		window.clear();
		scene.draw(&window);
		window.setView(window.getDefaultView());
		window.draw(sp);
		window.draw(rect);
		window.display();


		dt = dc.restart();
		//std::cout << dt.asSeconds() << "s" << "," << 1 / dt.asSeconds() << "fps" << std::endl;
	}

	return 0;
}