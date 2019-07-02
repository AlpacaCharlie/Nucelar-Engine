// ----------------------------------------------------------------------------
// Project Name		:	Game State Manager
// File Name		:	Utils.cpp
// Author			:	Thomas Komair
// Creation Date	:	January 20, 2013
// Purpose			:	Implements general purpose utility functions.
// ----------------------------------------------------------------------------
#include "Utils.h"

#define BS_INT 12		// default buffer size for reading string representing an int.
#define BS_FLOAT 16		// default buffer size for reading string representing a float.

//																			 //
//---------------------------FILE I/O----------------------------------------//
//																			 //

/*
	Writes an int to the file.

	Parameters: 
		- filename: a string representing the name of the file.
		- append: a boolean which specifies if the file should be overwritten 
					or if the value should be appended to the file.
		- towrite: integer value to write to the file. 
		- 
	
	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_WriteInt(FILE * pCurrFile, int towrite)
{
	if(pCurrFile)
	{
		// convert the int to 
		fprintf(pCurrFile, "%d", towrite);
		if(ferror(pCurrFile))
			return 0;
		return 1;
	}
	return 0;
}

/*
	Writes an float to the file.
	
	Parameters: 
		- filename: a string representing the name of the file.
		- append: a boolean which specifies if the file should be overwritten 
					or if the value should be appended to the file.
		- towrite: floating point value to write to the file. 

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_WriteFloat(FILE * pCurrFile, float towrite)
{
	if(pCurrFile)
	{
		// convert the int to 
		fprintf(pCurrFile, "%f", towrite);
		if(ferror(pCurrFile))
			return 0;
		return 1;
	}
	return 0;
}

/*
	Writes a string to a file and appends a null character after the string.

	Parameters: 
		- filename: a string representing the name of the file.
		- append: a boolean which specifies if the file should be overwritten 
					or if the value should be appended to the file.
		- towrite: String to write to the file. (String is equivalent to saying a char array).

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_WriteString(FILE * pCurrFile, const char * towrite)
{
	if(pCurrFile)
	{
		// write ther string to the file
		if(NULL != towrite)
		{
			fputs(towrite, pCurrFile);
			fputc('\0', pCurrFile);
		}

		if(ferror(pCurrFile))
			return 0;
		return 1;
	}
	return 0;
}
/*
	Writes a string to a file and adds a new line after the file.
	
	Parameters: 
		- filename: a string representing the name of the file.
		- append: a boolean which specifies if the file should be overwritten 
					or if the value should be appended to the file.
		- towrite: String to write to the file. (String is equivalent to saying a char array).

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_WriteLine(FILE * pCurrFile, const char * towrite)
{
	if(pCurrFile)
	{
		// write string and add new line character
		if(NULL != towrite)
		{
			fputs(towrite, pCurrFile);
			fputc('\n', pCurrFile);
		}

		if(ferror(pCurrFile))
			return 0;
		return 1;
	}
	return 0;
}

/*
	Writes a null character to the file. 
	
	Parameters: 
		- filename: a string representing the name of the file.
		- append: a boolean which specifies if the file should be overwritten 
					or if the value should be appended to the file.

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_WriteNULL(FILE * pCurrFile)
{
	if(pCurrFile)
	{
		// write the null character
		fputc('/0', pCurrFile);
		if(ferror(pCurrFile))
			return 0;
		return 1;
	}
	return 0;
}

/********************************************* Read Operations **************************************************/

/*
	this function should read the file one character at a time, and places them in a
	character array. Once it encounters a non digit character, we convert the character array
	to an integer using the atoi function.

	Parameters: 
		- filename: a string representing the name of the file.
		- toread: the address of the int to store the result of the read operation.

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_ReadInt(FILE * pCurrFile, int * toread)
{
	int tmpc, i , result;
	char number[BS_INT];

	if( NULL == pCurrFile)
		return 0;

	/*initialize the number counter to 0*/
	i = 0;

	/* Loop until we reach the end of the file or until the character we read is not a number */
	while(! feof(pCurrFile))
	{
		tmpc = fgetc(pCurrFile);
		if(ferror(pCurrFile))
			return 0;
		/*check if the character is not a number*/
		if (tmpc < 48 || tmpc > 57)
		{
				/*the first character is invalid return 0*/
				if (i == 0)
					return 0;
			break;
		}
		else
		{
			number[i++] = tmpc;
		}
	}
	
	//result = atoi(number);
	/*we are done break*/
	if(toread != NULL)
		*toread = result;
	return 1;
}

/*
	this function should read the file one character at a time, and places them in a
	character array. Once it encounters a non digit character OR a non '.',
	we convert the character array to a float using the atof function.

	Parameters: 
		- filename: a string representing the name of the file.
		- toread: the address of the float to store the result of the read operation.

	Returns 1 if successful, Returns 0 otherwise.
*/
int FIO_ReadFloat (FILE * pCurrFile, float * toread)
{
	int tmpc, i;
	char number[BS_FLOAT];
	float result;

	if( NULL == pCurrFile)
		return 0;

	/*initialize the number counter to 0*/
	i = 0;

	/* Loop until we reach the end of the file or until the character we read is not a number */
	while(! feof(pCurrFile))
	{
		tmpc = fgetc(pCurrFile);
		if(ferror(pCurrFile))
			return 0;
		/*check if the character is not a number or a point*/
		if (tmpc != 46 && (tmpc < 48 || tmpc > 57))
		{
			// first character was invalid return 0
			if(i == 0)
				return 0;
			else 
				break;
		}
		else
		{
			number[i++] = tmpc;
		}
	}
	//result = (float)atof(number);
	/*we are done break*/
	if(toread != NULL)
		*toread = result;
	return 1;
}

/*
	This function reads a line of text until it encounters a new line character '\n' OR a NULL character '\0'
	and stores the result in toread.

	parameters:
		- filename: a string representing the name of the file.
		- toread: A valid char * to store the string.
		- size: the size of the passed array.

	returns 1 if successful, Returns 0 otherwise.
*/
int FIO_ReadString(FILE* pCurrFile, char * toread, int size)
{
	// wrong input
	if(NULL == pCurrFile ||
		NULL == toread)
		return 0;

	int tmpc, i = 0;
	// Read until we reach a '\n' only.
	while( !feof(pCurrFile) && i < size)
	{
		// get the next character and check for 
		tmpc = fgetc(pCurrFile);
		if(ferror(pCurrFile))
			return 0;

		// Stop reading if its a new line character.
		if (tmpc == '\n' || tmpc == '\0')
		{
			// null terminate the string
			toread[i] = 0; 

			// success
			return 1;
		}

		// set the current character
		toread[i++] = tmpc;
	}

	// if we reached the end of file

	// error buffer too small
	if(i >= size)
		return -1;
	// null-terminate the string
	else
		toread[i] = 0;
	return 1;
}

/*
	This function reads a line of text until it encounters a new line character '\n' and stores the result 
	in toread.

	parameters:
		- pCurrFile: Pointer to a valide file.
		- toread: Address of the first element of a character array.
		- size: the size of the passed array.

	returns 1 if successful, 
			-1 if the buffer size is too small
			0 otherwise.
*/
int FIO_ReadLine(FILE * pCurrFile, char * toread, int size)
{
	// wrong input
	if(NULL == pCurrFile ||
		NULL == toread)
		return 0;

	int tmpc, i = 0;
	// Read until we reach a '\n' only.
	while( !feof(pCurrFile) && i < size)
	{
		tmpc = fgetc(pCurrFile);
		if(ferror(pCurrFile))
			return 0;

		// Stop reading if its a new line character.
		if (tmpc == '\n')
		{
			// null terminate the string
			toread[i] = 0; 

			// success
			return 1;
		}

		// set the current character
		toread[i++] = tmpc;
	}

	// if we reached the end of file

	// error buffer too small
	if(i >= size)
		return -1;
	// null-terminate the string
	else
		toread[i] = 0;
	return 1;
}