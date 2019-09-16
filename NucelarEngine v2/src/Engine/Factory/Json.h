#pragma once
#include "../../Extern/glm/glm.hpp"
#include "../AEX/AEXCore.h"
#include "json.hpp"
#include "../Engine/BasicTypes/NComponent.h"

using namespace AEX;

using json = nlohmann::json;

#define aexFactory (Factory::Instance())

struct ISerializable
{
	virtual void ToJson(json & val) = 0;
	virtual void FromJson(json & val) = 0;
};

void ToJsonVec2(json & val, const vec2 & in);

class MyTransform : public IComp
{
	AEX_RTTI_DECL(MyTransform, IComp);
public:
	MyTransform() :IComp() {}

	void ToJson(json & val) {
		ToJsonVec2(val["position"], mPosition);
		ToJsonVec2(val["scale"], mScale);
		val["rotation"] = mRotation;
	}
	void FromJson(json & val) {
		// sanity
		if (auto it = val.find("rotation") != val.end())
			mRotation = val["rotation"];
	}

public:
	vec2 mPosition, mScale;
	f32 mRotation = 0.0f;
};


struct ICreator {
	virtual IBase * Create() = 0; // pure virtual 
};
template<typename T>
struct TCreator : public ICreator {
	virtual IBase * Create()
	{
		return new T();
	}
};
class Factory : public ISystem
{
	AEX_RTTI_DECL(Factory, ISystem);
	AEX_SINGLETON(Factory);
private:
	std::map<std::string, ICreator*> mCreators;
public:
	void Register(const char * typeName, ICreator * creator)
	{
		if (mCreators.find(typeName) == mCreators.end()) // no duplicate
			mCreators[typeName] = creator;
	}
	IBase * Create(const char * typeName)
	{
		// IMPORTANT: FIND THE CREATOR HERE
		if (mCreators.find(typeName) != mCreators.end())
			return mCreators[typeName]->Create();
		// NO CREATOR REGISTERED
		return NULL;
	}

	template <typename T> 
	void Register() {
		Register(T::TYPE().GetName(), new TCreator<T>());
		// TODO: handle duplicate creator (avoid memory leaks)
	}
	template <typename T> 
	T* Create() {
		return dynamic_cast<T*>(Create(T::TYPE().GetName()));
	}
	
};




void SaveObjectToJson(NGameObject * go, json & val);

void LoadObjectFromJson(NGameObject * obj, json & val);