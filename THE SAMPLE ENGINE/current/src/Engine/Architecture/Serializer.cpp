#include <string>
#include"json.hpp"
#include <fstream>
#include "Serializer.h"

using json = nlohmann::json;


//Saves all the information of one game object into a json file
//Parameter is the game object we will save
void Serializer::SerializeGameObject(Gameobject &go, std::string LevelName)
{
	//Create the json
	json Object;
	//Saves the name and the id
	Object["Name"] = go.Name;
	Object["ID"] = go.ID;
	//Uses the name of the object as an output
	std::ofstream outFile((go.Name +=".json") );
	if (outFile.good() && outFile.is_open())
	{
		outFile << std::setw(4) << Object;
		outFile.close();
	}
}
