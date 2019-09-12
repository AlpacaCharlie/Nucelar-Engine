#include "Utils.h"
//for printing into console
#include <iostream>
/*!
*	\file		Input.cpp
*	\brief		Implementation of the as 1 functions.
*	\details	Contains the implementation for input_handle
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		23/01/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
//helper
//helper function, just to read or write text without messy code
void ReadFileInput(const char* filename, const char* mode, const char* thingtowrite)
{
	FILE *filepoint;
	errno_t err;
	if (err = fopen_s(&filepoint, filename, mode) != 0)
	{
		std::cout << "ERROR: Input_Handle()" << std::endl;
	}
	else
	{
		FIO_WriteLine(filepoint, thingtowrite);
		fclose(filepoint);
	}
}

// Simply write to the "Output.txt" file here (use the FIO functions)
void Input_Handle()
{
	// TODO
	ReadFileInput("Output.txt", "at", "Input:Handle");
}