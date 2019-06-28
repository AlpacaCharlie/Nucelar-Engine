#include <string>
#include"json.hpp"
#include <vector>
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
	Object["Components"];
	for (unsigned i = 0; i < go.Components.size(); i++)
	{
		Object["Components"].push_back(i);
	}
	//Uses the name of the object as an output
	std::ofstream outFile(std::string("src/Levels/")+=LevelName+= std::string("/")+= (go.Name += ".json"));
	//Check if it has opened correctly
	if (outFile.good() && outFile.is_open())
	{
		//Prints the jason into the file
		outFile << std::setw(4) << Object;
		outFile.close();
	}
}


json Serializer::SerializeComponent(std::string CompName)
{
	//Create the json
	json Component;
	//We open the h with the component
	std::ifstream CompFile;
	CompFile.open(std::string("src/Components/")+= CompName += ".h");
	//Now we loop until we find the word [Property]
	std::string buffer;
	do {
		buffer = CompFile.getline;
		if (CompFile.eof != buffer)
			return;//If we are at the end of file we return
	} while (buffer != "[Property]");


}
