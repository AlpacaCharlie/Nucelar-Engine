#include "Json.h"

Factory::Factory() :ISystem() {}

void ToJsonVec2(json & val, const AEVec2 & in) {
	val["x"] = in.x;
	val["y"] = in.y;
}

void SaveObjectToJson(GameObject * go, json & val){
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

void LoadObjectFromJson(GameObject * obj, json & val){
	obj->Shutdown(); // clear everything before loading. 
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