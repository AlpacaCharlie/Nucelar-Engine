#include "Json.h"
#include "../BasicTypes/NGameObject.h"

Factory::Factory() :ISystem() {}

void ToJsonVec2(json & val, const vec2 & in) {
	val["x"] = in.x;
	val["y"] = in.y;
}

void SaveObjectToJson(NGameObject * go, json & val)
{
	val["name"] = go->GetName();
	json & comps = val["comps"];
	for (u32 i = 0; i < go->GetComps().size(); ++i)
	{
		json compVal;
		IComp * comp = go->GetComp(i);
		compVal["type"] = comp->GetType().GetName();
		// write the component 
		// TODO(implement ToJson in ALL components). 
		// comp->ToJson(compVal);
		// BIG HACK REMOVE ME!!!!
		if (auto tr = dynamic_cast<MyTransform *>(comp))
		{
			tr->ToJson(compVal);
		}
		comps.push_back(compVal);
	}
}

void LoadObjectFromJson(NGameObject * obj, json & val)
{
	obj->ShutDown(); // clear everything before loading. 
	obj->SetName(val["name"].get<std::string>().c_str());
	json & comps = *val.find("comps");
	for (auto it = comps.begin(); it != comps.end(); ++it)
	{
		json & compVal = *it;
		std::string typeName = compVal["type"].get<std::string>();
		IBase * newComp = aexFactory->Create(typeName.c_str());
		if (auto tr = dynamic_cast<MyTransform *>(newComp))
			tr->FromJson(compVal);
		obj->AddComp((IComp*)newComp);
	}
}