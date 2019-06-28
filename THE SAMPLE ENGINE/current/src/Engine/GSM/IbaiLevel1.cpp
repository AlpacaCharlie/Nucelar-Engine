#include <iostream>
#include "GameStateManager.h"
#include "IbaiLevel1.h"
namespace KabenZotx
{
	int Life = 100;
}
void Ibai1_Load()
{

}

void Ibai1_Init()
{
	std::cout << KabenZotx::Life << std::endl;
}

void Ibai1_Update()
{
	std::cout << "HEEEYE KE PASA MAN" <<" Life:"<< KabenZotx::Life<< ::std::endl;
	KabenZotx::Life--;
	if (KabenZotx::Life<=0)
	{
		gGameStateNext = GS_QUIT;
	}
}

void Ibai1_Render()
{
	std::cout << "HEEEYE KE PASA RENDER" << ::std::endl;
}

void Ibai1_Free()
{
	std::cout << "HEEEYE KE PASA free" << ::std::endl;
}

void Ibai1_Unload()
{
	std::cout << "HEEEYE KE PASA unload" << ::std::endl;
}
