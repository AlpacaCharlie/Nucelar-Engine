#include "src\Engine\AEX.h"
#include <iostream>
#include "Simple Demo\SimpleDemo.h"
#include "JsonDemo\JsonDemo.h"
#include "Imgui Demo\ImGuiDemo.h"
#include "src\Engine\GSM\GameStateList.h"
#include "src\Engine\GSM\GameStateManager.h"
#include "src\Engine\GSM\IbaiLevel1.h"

void main(void)
{
	GSM_AddGameState(GS_LEVEL_1, Ibai1_Load, Ibai1_Init, Ibai1_Update, Ibai1_Render, Ibai1_Free, Ibai1_Unload);
	GSM_Init(GS_LEVEL_1);
	GSM_GameLoop();
	/*aexEngine->Initialize();
	aexEngine->Run(new ImGuiDemo);
	AEX::AEXEngine::ReleaseInstance();*/
}
