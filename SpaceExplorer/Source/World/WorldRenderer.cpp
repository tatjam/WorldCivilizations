#include "WorldRenderer.h"

void WorldRenderer::loadData()
{
	AssetManager* manager = &engine->manager;
	landCache["oceanTile"] = manager->getTexture("oceanTile");
	landCache["forestTile"] = manager->getTexture("forestTile");
	landCache["jungleTile"] = manager->getTexture("jungleTile");
	landCache["shoreTile"] = manager->getTexture("shoreTile");
	landCache["beachTile"] = manager->getTexture("beachTile");
	landCache["savannaTile"] = manager->getTexture("savannaTile");
	landCache["tundraTile"] = manager->getTexture("tundraTile");
	landCache["desertTile"] = manager->getTexture("desertTile");
	landCache["plainsTile"] = manager->getTexture("plainsTile");
	landCache["mountainTile"] = manager->getTexture("mountainTile");
	landCache["poleTile"] = manager->getTexture("poleTile");
}

void WorldRenderer::setup(sf::FloatRect viewRect)
{
	//Upload all sprite into scene
	ground = RenderLayer();
	ground.z = 1;

	//Get all assets from the asset system

	//Get part of the map viewed by the view
	Sprite nTile = Sprite();

	int i = 0;

	int sX = 0;
	int sY = 0;

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
			nTile.s.setPosition(sX * 16 + view->getCenter().x, sY * 16 + view->getCenter().y);
			if (c == sf::Color(128, 164, 177))
			{

				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["oceanTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Ocean
			}
			else if (c == sf::Color(187, 223, 237))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["shoreTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Shore
			}
			else if (c == sf::Color(213, 201, 160))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["beachTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Beach
			}
			else if (c == sf::Color(130, 160, 109))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["forestTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Forest
			}
			else if (c == sf::Color(139, 196, 131))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["jungleTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Jungle
			}
			else if (c == sf::Color(198, 237, 198))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["tundraTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Tundra
			}
			else if (c == sf::Color(201, 190, 153))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["desertTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Desert
			}
			else if (c == sf::Color(235, 235, 235))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["mountainTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Mountain
			}
			else if (c == sf::Color(255, 255, 255))
			{
				nTile.s.setTexture(landCache["poleTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Pole
			}
			else if (c == sf::Color(196, 220, 130))
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["savannaTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Savanna
			}
			else
			{
				//nTile.t = landCache["oceanTile"];
				nTile.s.setTexture(landCache["plainsTile"]);
				ground.sprites.push_back(nTile);
				i++;
				//Plains
			}
		
		}

	}
	viewRect.width = oldW;
	viewRect.height = oldH;
	scene->layers[ground.z] = ground;
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
