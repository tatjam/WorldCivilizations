#include "WorldRenderer.h"

void WorldRenderer::loadData()
{
	AssetManager* manager = &engine->manager;
	landCache = manager->getAllTextures();

	//Load tile information from the JSON file
	std::cout << "Loading tile size" << std::endl;

	JSONLoader loader = JSONLoader();
	Json::Value root;
	loader.loadFile("res/tiledata.json", root, false);
	
	tSide = root["side"].asInt();
	std::cout << "Tiles are: " << tSide << "px side" << std::endl;

	loader.loadFile("res/data/tilesettings.json", root, false);
	forestThresold = root["forestThresold"].asInt();
}


void WorldRenderer::renderUnits(sf::FloatRect viewRect, std::vector<Unit*> units)
{
	RenderLayer unitLayer = RenderLayer();
	unitLayer.z = 5;



	for (Unit* u : units)
	{
		//TODO: Only draw if outside fog of war

		int sX = u->x * tSide - (int)viewRect.left * tSide - 1;
		int sY = u->y * tSide - ((int)viewRect.top) * tSide - 1;

		//Check if unit (left or right) is visible

		if (((u->x + 1 >= viewRect.left && u->x + 1 <= viewRect.left + viewRect.width)
			&& (u->y + 1 >= viewRect.top && u->y + 1 <= viewRect.top + viewRect.height))

			|| ((u->x + world->width + 1 >= viewRect.left && 
				u->x + world->width + 1<= viewRect.left + viewRect.width)
				&& (u->y + 1 >= viewRect.top && u->y + 1 <= viewRect.top + viewRect.height)))
		{

			//Put the unit into the renderlayer
			Sprite s = Sprite();

			sf::Sprite sS = sf::Sprite();

			//We assume sprite is limited to world
			sS.setPosition(sX, sY);
			sS.setTexture(landCache[u->id]);

			sS.setScale(1, 1);

			s.s = sS;

			unitLayer.sprites.push_back(s);

			sS.setPosition(sX + world->width * tSide, sY);
			s.s = sS;
			unitLayer.sprites.push_back(s);
		}
		
	}

	//Send layer into scene for render
	scene->layers[unitLayer.z] = unitLayer;
}

void WorldRenderer::renderGround(sf::FloatRect viewRect)
{

	int biome = 0;


	//Upload all sprite into scene
	ground = RenderLayer();
	ground.z = 1;

	overlay = RenderLayer();
	overlay.z = 2;

	//Get all assets from the asset system

	//Get part of the map viewed by the view
	Sprite nTile = Sprite();
	Sprite nOver = Sprite();

	int i = 0;

	int sX = 0;
	int sY = 0;

	float oldX = viewRect.left;
	float oldY = viewRect.top;
	float oldW = viewRect.width;
	float oldH = viewRect.height;
	viewRect.width = (int)viewRect.width;
	viewRect.height = (int)viewRect.height;
	for (int x = viewRect.left; x < viewRect.left + viewRect.width; x++)
	{
		sX++;
		sY = 0;
		for (int y = viewRect.top; y < viewRect.top + viewRect.height; y++)
		{
			//Get pixel, convert into sprite, send into renderlayer
			int aX = x;
			int aY = y;
			aX %= world->biome.getSize().x;
			aY %= world->biome.getSize().y;

			sf::Color c = world->biome.getPixel(aX, aY);

			sY++;

			srand(aX * aY + aX);

			//Generate biome map
			//BY RGB 
			//128 164 177  -  Ocean (elev <= seaLevel)
			//187 223 237  -  Shore (elev >= 25 && elev <= seaLevel)
			//213 201 160  -  Beach (elev == seaLevel + 1)
			//--------------------------------------------------------
			//130 160 109  -  Grassland (med temp, med rain, med< height)
			//139 196 131  -  Rain (-high temp, good rain, med< height)
			//198 237 198  -  Tundra (low temp, any rain, med< height)
			//201 190 153  -  Desert (>high temp, low rain, med< height)
			//235 235 235  -  Mountain (any temp, any rain, high height)
			//196 220 130  -  Savanna (high temp, low rain, med height)
			//136 191 106  -  Plains (everything else)
			//255 255 255  -  Pole
			//OTHER: Plains

			nTile.s = sf::Sprite();

			nTile.s.setPosition((sX - 1) * tSide +
				view->getCenter().x - (view->getCenter().x), (sY - 1) * tSide +
				view->getCenter().y - (view->getCenter().y));

			if (c == sf::Color(128, 164, 177))
			{

				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["oceanTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Ocean

				biome = 0;
			}
			else if (c == sf::Color(187, 223, 237))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["shoreTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Shore

				biome = 0;
			}
			else if (c == sf::Color(213, 201, 160))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["beachTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Beach

				biome = 1;
			}
			else if (c == sf::Color(130, 160, 109))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["forestTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Forest
				biome = 2;
			}
			else if (c == sf::Color(139, 196, 131))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["jungleTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Jungle
				biome = 1;
			}
			else if (c == sf::Color(198, 237, 198))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["tundraTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Tundra
				biome = 2;
			}
			else if (c == sf::Color(201, 190, 153))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["desertTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Desert
				biome = 3;
			}
			else if (c == sf::Color(235, 235, 235))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["mountainTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Mountain
				biome = 2;
			}
			else if (c == sf::Color(255, 255, 255))
			{
				nTile.s.setTexture(landCache["poleTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Pole
				biome = 0;
			}
			else if (c == sf::Color(196, 220, 130))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["savannaTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Savanna
				biome = 4;
			}
			else if (c == sf::Color(213, 234, 244))
			{
				nTile.s.setTexture(landCache["riverTile"]);
				ground.sprites.push_back(nTile);
				i++;
				biome = 0;
			}
			else
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["plainsTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Plains
				biome = 2;
			}

			//Overlays
			sf::Color e = world->elev.getPixel(aX, aY);
			nOver.s = sf::Sprite();

			nOver.s.setPosition((sX - 1) * tSide +
				view->getCenter().x - (view->getCenter().x), (sY - 1) * tSide +
				view->getCenter().y - (view->getCenter().y));


			if (e.r == 255)
			{
				nOver.s.setTexture(landCache["mountainOverlay"]);
				overlay.sprites.push_back(nOver);
				i++;
			}
			else if (e.r == 128)
			{
				nOver.s.setTexture(landCache["hillsOverlay"]);
				overlay.sprites.push_back(nOver);
				i++;
			}
			else if (e.r == 15 && biome != 0)
			{
				//Check surrounding
				if (world->elev.getPixel(aX + 1, aY).r == 15
					|| world->heightmap.getPixel(aX + 1, aY).r <= world->seaLevel)
				{
					//Right connection
					nOver.s.setTexture(landCache["riverRight"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				if (world->elev.getPixel(aX - 1, aY).r == 15
					|| world->heightmap.getPixel(aX - 1, aY).r <= world->seaLevel)
				{
					//Left connection
					nOver.s.setTexture(landCache["riverLeft"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				if (world->elev.getPixel(aX, aY + 1).r == 15
					|| world->heightmap.getPixel(aX, aY + 1).r <= world->seaLevel)
				{
					//Down connection
					nOver.s.setTexture(landCache["riverDown"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				if (world->elev.getPixel(aX, aY - 1).r == 15
					|| world->heightmap.getPixel(aX, aY - 1).r <= world->seaLevel)
				{
					//Up connection
					nOver.s.setTexture(landCache["riverUp"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				/*
				if (world->elev.getPixel(aX - 1, aY - 1).r == 15)
				{
					//Up connection
					nOver.s.setTexture(landCache["riverUpLeft"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				if (world->elev.getPixel(aX + 1, aY - 1).r == 15)
				{
					//Up connection
					nOver.s.setTexture(landCache["riverUpRight"]);
					overlay.sprites.push_back(nOver);
					i++;
				}

				if (world->elev.getPixel(aX - 1, aY + 1).r == 15)
				{
					//Up connection
					nOver.s.setTexture(landCache["riverDownLeft"]);
					overlay.sprites.push_back(nOver);
					i++;
				}*/

			}
			else
			{
				//Do nothing
			}

			//Forestry stuff (using nOver too!)
			if (world->resources.getPixel(aX, aY).g >= forestThresold)
			{
				if (rand() % 1000 >= 500)
				{
					if (biome == 2)
					{
						nOver.s.setTexture(landCache["forestOverlayA"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 1)
					{
						nOver.s.setTexture(landCache["jungleOverlayA"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 4)
					{
						nOver.s.setTexture(landCache["savannaOverlayA"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 3)
					{
						nOver.s.setTexture(landCache["desertOverlayA"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
				}
				else
				{
					if (biome == 2)
					{
						nOver.s.setTexture(landCache["forestOverlayB"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 1)
					{
						nOver.s.setTexture(landCache["jungleOverlayB"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 4)
					{
						nOver.s.setTexture(landCache["savannaOverlayB"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
					else if (biome == 3)
					{
						nOver.s.setTexture(landCache["desertOverlayB"]);
						overlay.sprites.push_back(nOver);
						i++;
					}
				}
			}

		}

	}

	viewRect.width = oldW;
	viewRect.height = oldH;
	scene->layers[ground.z] = ground;
	scene->layers[overlay.z] = overlay;
}

void WorldRenderer::setup(sf::FloatRect viewRect, std::vector<Unit*> units)
{
	renderGround(viewRect);
	renderUnits(viewRect, units);
}

WorldRenderer::WorldRenderer(Scene* s, Engine* nengine, World* w, sf::View* nview)
{
	scene = s;
	world = w;
	engine = nengine;
	view = nview;
	landCache = std::map<std::string, sf::Texture>();
}


WorldRenderer::~WorldRenderer()
{
}
