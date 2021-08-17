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
#include <stdio.h>
#include "types.h"
#include "State.h"
#include "input.h"
#include <stdlib.h>
#include <ctype.h>

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
static SInt8 word[WORD_MAX_LEN];
static SInt8 continueGame;
static Boolean ok;
static SInt8 buff;
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
	memset(usedLetters, '\0', sizeof(usedLetters));
	/*usedLetters[ALPHABET_SIZE] = "";*/
	lives = 6;
	//memset sau for
	/*currentWord[WORD_MAX_LEN] = "";*/
	memset(currentWord, '\0', sizeof(currentWord));
	character = '\0';
	ok = 0;
}
//Boolean isChar(SInt8 *c)
//{
//	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c<='Z'));
//	return 1;
//	return 0;
//}

Boolean inUsedLetters(SInt8 c)
{
	int i = 0;
	while (usedLetters[i] != '\0')
	{
		if (usedLetters[i] == c)
			return 1;
		i++;
	}
	usedLetters[i] = c;
	return 0;
}

void addUsedLetters(SInt8 c)
{
	int i = 0;
	while (usedLetters[i] != '\0')
	{
		i++;
	}
	usedLetters[i] = c;
}

Boolean isInWord(SInt8 c) 
{
	Boolean ok = 0;
	int i = 0;
	while (word[i] != '\0' && ok==0)
	{
		if (word[i] == c)
			return 1;
		i++;
	}
	return 0;
}

void switchState()
{
	while (1)
	{
		switch (state)
		{
		case INIT:
			initVariables();
			state = INPUT;
		case INPUT:
			printf("%s","Write a character that you think appears in the word: ");
			scanf("%c", &character);
			scanf("%c", &buff);
			state = PROCESS;
		case PROCESS:
			if (isalpha(character) == 0)
			{
				printf("%s%c%s%s","'",character , "'", " is Not a character!\n");
				state = INPUT;
				break;
			}
			if(inUsedLetters(character)==1)
			{
				printf("%c%s",character," is already used!\n");
				state = INPUT;
				break;
			}
			else
			{
				addUsedLetters(character);
				if (isInWord(character) == 0)
					lives = lives - 1;
			/*	if (isInWord(character) == 1)
				{
					pass();
				}
				else
				{
					lives = lives - 1;
				}*/
			}
		/*	read_input(word, file_name);
			printf("%s", word);*/
			state = DISPLAY;
		case DISPLAY:
			printf("%s", lives);
			state = FINAL;
		case FINAL:
			if (lives == 0)
			{
				printf("%s", "Do you want to start a new game? (Y/N): ");
				while (ok == 0)
				{
					scanf("%c", &continueGame);
					scanf("%c", &buff);
					if (continueGame == 'Y')
					{
						ok = 1;
						state = INIT;
						system("cls");
					}
					else if (continueGame == 'N')
					{
						ok = 1;
						return;
						printf("%s", "a");
					}
					else
					{
						printf("Write Y/N: ");
					}
				}
			}
			else
			{
				state = INPUT;
			}
			break;
		default:
			printf("Something went wrong! ");
			break;
		}
	}
}

/******************************************************************************
*******************************************************************************/

/*************** END OF FUNCTIONS ***************************************************************************/