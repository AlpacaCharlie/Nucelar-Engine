#include "src\Engine\AEX.h"
#include <iostream>
#include "Simple Demo\SimpleDemo.h"
#include "JsonDemo\JsonDemo.h"
#include "Imgui Demo\ImGuiDemo.h"

std::stringstream console;

void main(void)
{

	auto* coutbuf = std::cout.rdbuf();
	auto old_buf = std::cout.rdbuf(console.rdbuf());


	aexEngine->Initialize();
	aexEngine->Run(new ImGuiDemo);
	AEX::AEXEngine::ReleaseInstance();

	std::cout.rdbuf(coutbuf);
}
