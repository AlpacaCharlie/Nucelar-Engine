/*!
*	\file		System.cpp
*	\brief		Implementation of the as 1 functions.
*	\details	Contains the system functions
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		23/01/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
//for defines
#include "System.h"
//for writing in files etc
#include "Utils.h"
//for printing into console
#include <iostream>

//helper
//helper function, just to read or write text without messy code
void ReadFileSystem(const char* filename, const char* mode, const char* thingtowrite)
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


// Simply write to the "Output.txt" file here (use the FIO functions)
void System_Initialize()
{
	// TODO
	ReadFileSystem("Output.txt", "wt", "System:Initialize");
}

// Simply write to the "Output.txt" file here (use the FIO functions)
void System_Free()
{
	// TODO
	ReadFileSystem("Output.txt", "at", "System:Exit");
}
