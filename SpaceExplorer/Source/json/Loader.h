#pragma once
#include <iostream>

#include <string>
#include <fstream>
#include <sstream>

#include "json/json.h"


//This class can parse a .json file from the filename
//It simply wraps jsoncpp methods!

static class JSONLoader
{
public:

	//Will laod a file and output it to the out value!
	//Returns false if something went wrong, otherwise it returns true
	static bool loadFile(std::string path, Json::Value& out, bool collectComments = false)
	{
		std::ifstream file = std::ifstream(path);
		//Check if we did it
		if (!file.is_open())
		{
			std::cout << "[JSON_LOADER->Error]" << path << ": FILE NOT FOUND" << std::endl;
			return false; //Error!
		}
		std::stringstream buf;
		buf << file.rdbuf();
		//Now buf contains the json file!

		Json::Reader reader = Json::Reader();
		if (!reader.parse(buf.str(), out, collectComments))
		{
			std::cout << reader.getFormattedErrorMessages() << std::endl;
			return false; //Error! (File was actually placed at out, so beware!)
		}

		


		return true;
	}

	JSONLoader()
	{
		return;
	}
};