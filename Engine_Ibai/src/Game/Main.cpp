// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	Main.cpp
// Author			:	Thomas Komair
// Creation Date	:	2013/04/26
// Purpose			:	The entry point of the progrma
// History			:
// ---------------------------------------------------------------------------
#include <AEEngine.h>
#include <GAM150.h>
#include "..\Engine\Engine.h"
#include "Sandbox.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "Level_4.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
{
	// Initialize the alpha engine
	if(AESysInit() == false)
		return 0;

	// Add a game state to the game state manager
	AEGameStateMgrAdd(
		GS_LEVEL_1,
		Level_1_Load,
		Level_1_Init,
		Level_1_Update,
		Level_1_Render,
		Level_1_Free,
		Level_1_Unload);
	AEGameStateMgrAdd(
		GS_LEVEL_2,
		Level_2_Load,
		Level_2_Init,
		Level_2_Update,
		Level_2_Render,
		Level_2_Free,
		Level_2_Unload);
	AEGameStateMgrAdd(
		GS_LEVEL_3,
		Level_3_Load,
		Level_3_Init,
		Level_3_Update,
		Level_3_Render,
		Level_3_Free,
		Level_3_Unload);
	AEGameStateMgrAdd(
		GS_LEVEL_4,
		Level_4_Load,
		Level_4_Init,
		Level_4_Update,
		Level_4_Render,
		Level_4_Free,
		Level_4_Unload);
	AEGameStateMgrAdd(
		GS_LEVEL_SANDBOX,
		Sandbox_Load,
		Sandbox_Init,
		Sandbox_Update,
		Sandbox_Draw,
		Sandbox_Free,
		Sandbox_Unload);

	// Initialize the game state manager
	AEGameStateMgrInit(GS_LEVEL_1);

	// Initialize the Object Manager
	gObjMgr.Initialize();

	// Initialize the collision system
	gCollisionSystem.Init();

	// Gameloop
	AESysGameLoop();

	// shutdown the collision system
	gCollisionSystem.Shutdown();

	gObjMgr.Shutdown();

	AESysExit();

	return 0;
}