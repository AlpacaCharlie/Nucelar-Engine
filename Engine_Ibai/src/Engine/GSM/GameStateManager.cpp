
//for some defines
#include "GameStateList.h"
//for function pointers
#include "GameStateManager.h"
//for utils redfile etc
#include "Utils.h"
//for fopen_s
#include <errno.h>
//for printing into console
#include <iostream>
//for the input handle
#include "Input.h"
// Max states in the game
#define MAX_GAME_STATES 64

// ---------------------------------------
// Globals
//helper
//helper function, just to read or write text without messy code
void ReadFileAndWrite(const char* filename, const char* mode, const char* thingtowrite)
{
	FILE *filepoint;
	errno_t err;
	if (err = fopen_s(&filepoint, filename, mode) != 0)
	{
		std::cout << "could not open file" << std::endl;
	}
	else
	{
		FIO_WriteLine(filepoint, thingtowrite);
		fclose(filepoint);
	}
}
/*!------------------------------------------------------------------------------------------------
	\brief This structure holds the id of the gamestate and the 6 function pointers for the state.
-------------------------------------------------------------------------------------------------*/
struct GameStateInfo
{
	unsigned GameStateId;
	
	fp Load;
	fp Unload;
	fp Init;
	fp Free;
	fp Update;
	fp Render;
};

// Stores the current, previsou and next states along with the initialize state
unsigned gGameStateInit;
unsigned gGameStateCurrent;
unsigned gGameStatePrevious;
unsigned gGameStateNext;
// Game State functions
fp GameStateInit = 0;
fp GameStateLoad = 0;
fp GameStateUnload = 0;
fp GameStateFree = 0;
fp GameStateUpdate = 0;
fp GameStateRender = 0;


// An array of GameStateInfo to hold all the game state information.
GameStateInfo	gGameStates[MAX_GAME_STATES];

// The number of actual game states.
unsigned			gGameStatesCount = 0;

/*!------------------------------------------------------------------------------------------------
 \brief This is a dummy function that doesn't do anything.
 \details
 	Use this function as a substitute if one of the function pointers passed to the 
	GSM_AddGameState function is NULL.
-------------------------------------------------------------------------------------------------*/
void dummy()
{}

/*------------------------------------------------------------------------------------------------
 \brief This function adds a state to the game state manager.
 \param gameStateIdx
 	Represents the ID of the state. This id is declared in GameStateList.h
 \param Load,Init,Update,Render,Free,Unload 
	Function pointers to the game states functions

 \details:
	The function adds a state to the GameStateManager by storing the passed arguments in the
	gGameStates array (declared above). It must first make sure that the current count of game
	states is not over the MAX_GAME_STATES macro(defined above). Then it must go through all 
	the previouly added game states and make sure that we are not adding a duplicate; if we are 
	we simply return. For example:
	
	GSM_AddGameState(GS_LEVEL1,Level1Load, Level1Init, Level1Update, Level1Render, Level1Free, Level1Unload); 
		-> GS_LEVEL1 has not been added, we add the state to the array.
	GSM_AddGameState(GS_LEVEL1,....) 
		-> This time GS_LEVEL1 exists, we don't add a duplicate, return.

	Adding a state is simply storing the gameStateIdx and all the function pointers in the gGameStates array
	of GameStateInfo structure. If one of the passed function pointer is NULL, then you MUST store
	the address of dummy. this will insure that you don't try to call a function using a NULL pointer.
	For Example:

		GSM_AddGameState(GS_LEVEL1, Level1Load, NULL, Level1Update, Level1Render, NULL, Level1Unload);
			-> Here the Init and Free function pointers are pointing to dummy.
-------------------------------------------------------------------------------------------------*/
void GSM_AddGameState(unsigned gameStateIdx, fp Load, fp Init, fp Update, fp Render, fp Free, fp Unload)
{
    // TODO
	//this boolean will tell if we already put a gamestate
	//in order to not copy it
	bool isgamestateinthere = false;
	//first we make wure we haven't surpassed the maximum
	//States
	if (gGameStatesCount < MAX_GAME_STATES)
	{
		//first we see if there is already the same gamestate implemented
		//to overwrite it in the same place
		for (unsigned int i = 0; i < gGameStatesCount; i++)
		{
			//if that happens, we update the pointers to the ones passed
			if (gGameStates[i].GameStateId == gameStateIdx)
			{
				isgamestateinthere = true;
				gGameStates[i].GameStateId = gameStateIdx;
				gGameStates[i].Load = Load;
				gGameStates[i].Unload = Unload;
				gGameStates[i].Init = Init;
				gGameStates[i].Update = Update;
				gGameStates[i].Render = Render;
				gGameStates[i].Free = Free;
				//to avoid crashes, we gotta make nulls empty functions
				if (Load == NULL)
					gGameStates[i].Load = &dummy;
				if (Init == NULL)
					gGameStates[i].Init = &dummy;
				if (Update == NULL)
					gGameStates[i].Update = &dummy;
				if (Render == NULL)
					gGameStates[i].Render = &dummy;
				if (Free == NULL)
					gGameStates[i].Free = &dummy;
				if (Unload == NULL)
					gGameStates[i].Unload = &dummy;
				return;
			}
		}
		//in most of the cases, the gamestate will not be already in the 
		//array
		if (isgamestateinthere == false)
		{
			//we equal the functions and the id in the last empty space, defined by
			//gGamestatescount
			gGameStates[gGameStatesCount].GameStateId = gameStateIdx;
			gGameStates[gGameStatesCount].Load = Load;
			gGameStates[gGameStatesCount].Unload = Unload;
			gGameStates[gGameStatesCount].Init = Init;
			gGameStates[gGameStatesCount].Update = Update;
			gGameStates[gGameStatesCount].Render = Render;
			gGameStates[gGameStatesCount].Free = Free;

			if (Load == NULL)
				gGameStates[gGameStatesCount].Load = dummy;
			if (Init == NULL)
				gGameStates[gGameStatesCount].Init = dummy;
			if (Update == NULL)
				gGameStates[gGameStatesCount].Update = dummy;
			if (Render == NULL)
				gGameStates[gGameStatesCount].Render = dummy;
			if (Free == NULL)
				gGameStates[gGameStatesCount].Free = dummy;
			if (Unload == NULL)
				gGameStates[gGameStatesCount].Unload = dummy;
			//and we increment gGameStatesCount to be the next empty
			//place in the array
			gGameStatesCount++;
			return;
		}
	}
}

/*------------------------------------------------------------------------------------------------
 \brief	This function initializes the game state manager.
 \param	gameStateInit 
 	Represents the ID of the initial state. This id is declared in GameStateList.h
	Note that the state must be added previous to the initialization.

 \details
	- Simply store this state as the initial state by storing it into gamestaeinit, next previous and current.
	- Call GameStateManagerUpdate to change the pointers. 
	- Remember that you must write to "Output.txt" in this function. (Use the FileIOManager).
-------------------------------------------------------------------------------------------------*/
// Call this to initialize the game state manager
void GSM_Init(unsigned gameStateInit)
{
	// TODO
	//when we initialize the GSM,
	//we equall all game states to the 
	//first level passed
	
	gGameStateInit = gameStateInit;
	gGameStatePrevious = gameStateInit;
	gGameStateCurrent = gameStateInit;
	gGameStateNext = gameStateInit;
	GSM_UpdatePtrs();
}


/*!------------------------------------------------------------------------------------------------
 \brief	This function adds a state to the game state manager.
 \details	
	This function updates the function pointers of the GameStateManager. It will look up the 
	value of gGameStateCurrent in the gGameStates array. If the value is equal to the id of one 
	of the added states (see GSM_AddGameState()function above), then it sets the GameStateManager
	function pointers to the corresponding functions (again added in the GSM_AddGameState function).

	if the value of gGameStateCurrent is equal to GS_RESTART or GS_QUIT then the GSM function pointers
	fill point to the dummy function.

	if the value of gGameStateCurrent is not either of the two above, then you must return and 
	print an error.

	- Remember that you must write to "Output.txt" in this function. (Use the FileIOManager)
-------------------------------------------------------------------------------------------------*/
void GSM_UpdatePtrs()
{
	// TODO
	//if the current state is restart or quit(special cases)
	//we equall all function pointers to nothing
	if (gGameStateCurrent == GS_RESTART || gGameStateCurrent == GS_QUIT)
		{
			GameStateInit = dummy;
			GameStateLoad = dummy;
			GameStateUnload = dummy;
			GameStateFree = dummy;
			GameStateUpdate = dummy;
			GameStateRender = dummy;
			ReadFileAndWrite("Output.txt", "at", "GSM:Update");
			return;
		}
	//in order to get the state to update...
	for (int i = 0; i < MAX_GAME_STATES; i++)
	{
		//we try to find in the array the current game state,
		//and update all pointer to its corresponding function
		//pointers
		if (gGameStateCurrent == gGameStates[i].GameStateId)
		{
			GameStateInit = gGameStates[i].Init;
			GameStateLoad = gGameStates[i].Load;
			GameStateUnload = gGameStates[i].Unload;
			GameStateFree = gGameStates[i].Free;
			GameStateUpdate = gGameStates[i].Update;
			GameStateRender = gGameStates[i].Render;
			ReadFileAndWrite("Output.txt", "at", "GSM:Update");
			return;
		}
	}
	std::cout << "ERROR: GSM_UpdatePtrs()" << std::endl;
	

}

/*!------------------------------------------------------------------------------------------------
	\brief Implements the gameloop seen in class. 
	\details
		Remember that the game loop is implemented using two loops: The inner loop calls Update and 
		Render as long as we're not changing game state (that is, the current game state and the next are
		still the same value). The outer loop handles game state changing. This implies game state
		loading/unloading, initialization and freeing, as well as handling the GS_QUIT and GS_RESTART 
		special game states. 
------------------------------------------------------------------------------------------------*/
void GSM_GameLoop()
{
	// TODO
	//the game loop goes, of course,
	//until we quit the game

	for (;gGameStateNext != GS_QUIT;)
	{
		//if we want to restart the level,
		if (gGameStateCurrent == GS_RESTART)
		{
			//we need to equal the current game state to the
			//previous(if we are in level 1, we want to go again
			//to it so the current state becomes the previous one to 
			//the restart
			gGameStateCurrent = gGameStatePrevious;
			//and the same with the next game state(we do not
			//want to restart it again)
			gGameStateNext = gGameStatePrevious;
		}
		else
		{
			//I honestly don't understand this, I just followed the
			//diagram here 
			GSM_UpdatePtrs();
			//if we exited the loop and we are not restarting it,
			//this means we are going to another level
			GameStateLoad();
		}
		//the game state needs to be initialized for entering the loop
		GameStateInit();
		while (gGameStateCurrent == gGameStateNext)
		{
			//to not have delay, we take the input before the update
			Input_Handle();
			GameStateUpdate();
			GameStateRender();
		}
		//when we exit the loop, we need to free the memory
		GameStateFree();
		if (gGameStateNext == GS_RESTART)
		{
			//if we exit and we restart, we have to update the game state
			gGameStatePrevious = gGameStateCurrent;
			gGameStateCurrent = gGameStateNext;

		}
		else
		{
			//if we exit and we don't restart, this means we are exiting or changing
			//the level
			GameStateUnload();
		}
		//lastly, we update the game state
		gGameStatePrevious = gGameStateCurrent;
		gGameStateCurrent = gGameStateNext;
	}

	
}
