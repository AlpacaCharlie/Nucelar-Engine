#include "src\Engine\AEX.h"
#include <iostream>
#include "Simple Demo\SimpleDemo.h"
#include "JsonDemo\JsonDemo.h"
#include "Imgui Demo\ImGuiDemo.h"
#include "GraphicsDemo\GraphicsDemo.h"

void main(void)
{
	aexEngine->Initialize();
	aexEngine->Run(new GraphicsDemo);
	AEX::AEXEngine::ReleaseInstance();
}
