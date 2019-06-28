#pragma once
#include "JsonDemo.h"
#include <iostream>
#include <fstream>
#include "src\Engine\Architecture\Serializer.h"
using namespace AEX;

#include "src\Engine\Json\Json.h"


void GettingStartedWithJson()
{
	json value;

	// write stuff in the json value

	// json value can be implicitly casted
	// to many different types. (ints, doubles, strings, etc...
	value["hello"] = "world";
	value["hI"] = PI;
	value["pI"] = PI;

	// the json::[] operator returns a new json
	value["complex_val"]["PI"] = PI;

	// a json value can also be an array
	json & array_val = value["array_val"];
	for (u32 i = 0; i < 5; ++i)
		array_val.push_back(i);

	// a json value can also be a mixed array
	json & mixed_array_val = value["mixed_array_val"];
	for (u32 i = 0; i < 5; ++i) {
		if (i % 2 == 0)// even -> push int
			mixed_array_val.push_back(i);
		else
			mixed_array_val.push_back(std::string("hello"));
	}

	// a json array keeps the order intact (i.e. no alphabetical ordering).
	json & string_array_val = value["string_array"];
	string_array_val.push_back("ff");
	string_array_val.push_back("aa");
	string_array_val.push_back("zz");
	string_array_val.push_back("bb");

	json delayed; delayed = "pene";
	value["test"] = delayed;

	// save to a file. 
	std::ofstream outFile("test.json");
	if (outFile.good() && outFile.is_open())
	{
		outFile << std::setw(4) << value;
		outFile.close();
	}
}

void TestReadWriteWithJson()
{
	MyTransform tr;

	// load
	{
		json value;
		std::ifstream inFile("input.json");
		if (inFile.good() && inFile.is_open())
		{
			inFile >> value;
			inFile.close();
			tr.FromJson(value);
		}
	}

	// save
	{
		json value;

		tr.ToJson(value);

		// save to a file. 
		std::ofstream outFile("test.json");
		if (outFile.good() && outFile.is_open())
		{
			outFile << std::setw(4) << value;
			outFile.close();
		}
	}
}

// ----------------------------------------------------------------------------
#pragma region GAMESTATE FUNCTIONS
void JsonDemo::Initialize()
{/*
	aexFactory->Register<GameObject>();
	aexFactory->Register<MyTransform>();
	aexFactory->Register<TransformComp>();
	
	GameObject go; 

	// load
	{
		json value;
		std::ifstream inFile("test.json");
		if (inFile.good() && inFile.is_open())
		{
			inFile >> value;
			inFile.close();
			LoadObjectFromJson(&go, value);
		}
	}
	// save
	{
		json value;
		SaveObjectToJson(&go, value);
		// save to a file. 
		std::ofstream outFile("copy.json");
		if (outFile.good() && outFile.is_open())
		{
			outFile << std::setw(4) << value;
			outFile.close();
		}
	}

	

	exit(1);*/

	/*GettingStartedWithJson();
	exit(1);*/

	Gameobject test;
	test.ID = 1;
	test.Name = "MyTestObjectHaha";
	test.Components.push_back(2);
	test.Components.push_back(34);
	test.Components.push_back(16);
	test.Components.push_back(32);
	test.Components.push_back(5);
	Serializer TestSerializer;
	TestSerializer.SerializeGameObject(test, "Level1");

}
void JsonDemo::LoadResources()
{
}
void JsonDemo::Update()
{
	/*// get main window dimensions
	auto mainWin = aexWindowMgr->GetMainWindow();
	auto winWH = AEVec2(f32(mainWin->GetWidth()), f32(mainWin->GetHeight()));

	// control the engine
	if (aexInput->KeyTriggered('B'))
		aexTime->LockFrameRate(!aexTime->FrameRateLocked());
	if (aexInput->KeyTriggered('V'))
		aexGraphics->SetVSyncEnabled(!aexGraphics->GetVSyncEnabled());
	if (aexInput->KeyPressed(VK_OEM_PLUS))
		aexTime->SetMaxFrameRate(aexTime->GetMaxFrameRate() + 1.0);
	if (aexInput->KeyPressed(VK_OEM_MINUS))
		aexTime->SetMaxFrameRate(aexTime->GetMaxFrameRate() - 1.0);
	if (aexInput->KeyTriggered('F'))
		mainWin->SetFullScreen(!mainWin->GetFullScreen());

	f32 fps = (f32)aexTime->GetFrameRate();
	std::string wintitle = "Simple Demo - FPS: "; wintitle += std::to_string(fps);
	if (aexTime->FrameRateLocked())	wintitle += "(LOCKED)";
	wintitle += " - VSYNC: ";	wintitle +=	aexGraphics->GetVSyncEnabled() ? "ON" : "OFF";
	wintitle += " - Controls: FPS: 'B', '+/-'. VSYNC: 'V'";
	aexWindowMgr->GetMainWindow()->SetTitle(wintitle.c_str());


	Logic::Instance()->Update();*/

}
void JsonDemo::Render()
{
	auto mainWin = aexWindowMgr->GetMainWindow();
	auto winWH = AEVec2(f32(mainWin->GetWidth()), f32(mainWin->GetHeight()));

	aexGraphics->SetViewport(0, 0, s32(winWH.x), s32(winWH.y));
	aexGraphics->SetClearColor(Color(0.7f,0.7f,0.7f,1.0f));
	aexGraphics->ClearFrameBuffer();

	auto mp = aexInput->GetMousePos();
	aexGraphics->DrawCircle(mp.x, mp.y, 50, Color(0,0,0,1));

	aexGraphics->Present();
}

#pragma endregion