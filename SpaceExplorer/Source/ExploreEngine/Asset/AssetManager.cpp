#include "AssetManager.h"


using namespace Explore;

bool checkString(std::string data, std::string check)
{
	if (data.find(check) == std::string::npos)
	{
		return false;
	}

	return true;
}

Sprite AssetManager::getSprite(std::string s)
{
	Sprite sp = Sprite();
	sf::Texture tex = sf::Texture();
	tex.loadFromImage(images[s]);
	sp.t = tex;
	sp.s = sf::Sprite();
	sp.s.setTexture(sp.t);

	return sp;
}

sf::Texture AssetManager::getTexture(std::string s)
{
	sf::Texture tex = sf::Texture();
	tex.loadFromImage(images[s]);
	return tex;
}

void AssetManager::load()
{

	DIR* dir = NULL;
	struct dirent* pent = NULL;
	dir = opendir("res/art");
	if (dir == NULL)
	{
		std::cout << "[AssetLoader->Error] Could not open res/art directory!" << std::endl;
		std::cout << "Press ENTER to exit the program" << std::endl;
		std::cin.get();
		//We cannot run without assets so fatal exit
		exit(1);
	}

	std::cout << "[AssetLoader] Reading files..." << std::endl;

	while (pent = readdir(dir))
	{
		if (pent == NULL)
		{
			std::cout << "[AssetLoader->Error] Error loading data in directory!" << std::endl;
			std::cout << "Press ENTER to exit the program" << std::endl;
			std::cin.get();
			//We cannot run without assets so fatal exit
			exit(1);
		}

		if (checkString(pent->d_name, ".json"))
		{
			std::cout << "[AssetLoader] Found " << pent->d_name << std::endl;
			//Read file:
			JSONLoader loader = JSONLoader();
			std::string comp = "res/art/";
			comp += pent->d_name;

			Json::Value root;

			loader.loadFile(comp, root, false);

			for (Json::Value v : root)
			{
				for (int i = 0; i < v.getMemberNames().size(); i++)
				{
					Json::Value va = v[v.getMemberNames()[i]];
					sf::Image ni = sf::Image();
					ni.loadFromFile(va.asString());
					images[v.getMemberNames()[i]] = ni;
					std::cout << "Loaded file: " << v.getMemberNames()[i] << std::endl;
				}
			}
		}
	}

	closedir(dir);

}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}
