/*******************************************************************************
* Title                 :	Hangman game.
* Filename              :   main.c
* Author                :	Rakhel Linguraru
* Origin Date           :	12.08.2021
* Version               :   1.0.0
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date         Software Version       Initials   Description
*    12.08.2021         v1.0             lir1clj    Module Created.
*
*******************************************************************************/
/** \file main.c
 * \brief This module contains the
 */
 /******************************************************************************
 * Includes
 *******************************************************************************/
#include <stdio.h>	
#include "types.h"
#include "input.h"
#include "State.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/**
*Doxygen tag for documenting variables and constants
*/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
extern void init(SInt8* fileName);
extern void switchState();

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : main()
*//**
*	This function is used to control the flow of the whole program.
*	Param[in]: 
*     argc [Int32]
*     argv [Int8]
*  Param[out]:
*     none 
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*		Date         Software Version    Initials   Description
*		12.08.2021           v1.0        lir1clj    Function Created.
*
*******************************************************************************/

int main(int argc, char** argv)
{
	SInt8 file_name[FILE_MAX_LEN];
	SInt8 word[WORD_MAX_LEN];
	if (argc == 2)
	{
		/*strcpy(file_name, argv[1]);
		read_input(word, file_name);
	    printf("%s", word);*/
		init(argv[1]);
		switchState();
	}
	else
	{
		printf("Wrong parameters from command line.");
		exit(1);
	}
}