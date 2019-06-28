#pragma once
#ifndef SERIALIZER_H
#define SERIALIZER_H

class Gameobject
{
public:
	std::string Name;
	int ID;
	std::vector<int> Components;
};

class Serializer
{
public:
	void SerializeGameObject(Gameobject &go, std::string LevelName);
	json SerializeComponent(std::string CompName);
};

#endif // !SERIALIZER_H
