/*******************************************************************************
* Title                 :   State
* Filename              :   state.c
* Author                :   OW
* Origin Date           :   05/08/2021
* Version               :   1.0.0
* Compiler              :	-
* Target                :	-
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  05/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
/** \file input.c
* \brief This module contains the
*/
/******************************************************************************
* Includes
*******************************************************************************/
#include "types.h"
#include "State.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
// the max number of words

  /******************************************************************************
  * Macros
  *******************************************************************************/
#define ALPHABET_SIZE 28
/******************************************************************************
* Variables
*******************************************************************************/
typedef enum MyEnum
{
	INIT, INPUT, PROCESS, DISPLAY, FINAL
}State_en;
static SInt8 usedLetters[ALPHABET_SIZE] ;
static UInt8 lives;
static SInt8 currentWord[WORD_MAX_LEN];
static SInt8 character;
static State_en state;
static SInt8 file_name[100];
/******************************************************************************
* Function Definitions
*******************************************************************************/
void init(SInt8 *fileName)
{
	state = INIT;
	strcpy(file_name, fileName);
}
void initVariables()
{
	usedLetters[ALPHABET_SIZE] = "";
	lives = 6;
	currentWord[WORD_MAX_LEN] = "";
	character = "";
}
Boolean isChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c<='Z'));
	return 1;
	return 0;
}

void switchState()
{
	while (1)
	{
		switch (state)
		{
		case INIT:
			/*initVariables();*/
			state = INPUT;
			break;
		case INPUT:
			state = PROCESS;
			/*character = getch();*/
			break;
		case PROCESS:
			/*if (isChar(character) == 0)
			{
				state = INPUT;
				break;
			}*/
			state = DISPLAY;
			break;
		case DISPLAY:
			state = FINAL;
			break;
		case FINAL:
			state = INIT;
			break;
		default:
			printf("Something went wrong");
			break;
		}
	}
}

/******************************************************************************
*******************************************************************************/

/*************** END OF FUNCTIONS ***************************************************************************/