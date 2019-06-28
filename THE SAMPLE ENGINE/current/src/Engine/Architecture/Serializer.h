#pragma once
#ifndef SERIALIZER_H
#define SERIALIZER_H

class Gameobject
{
public:
	std::string Name;
	int ID;
};

class Serializer
{
public:
	void SerializeGameObject(Gameobject &go, std::string LevelName);
};

#endif // !SERIALIZER_H
