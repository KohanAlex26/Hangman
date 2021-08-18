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
static SInt8 body[100];

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
	lives = 6;
	memset(currentWord, '_', sizeof(currentWord));
	character = '\0';
	ok = 0;
	memset(body, '\0', sizeof(body));
}

Boolean inUsedLetters(SInt8 c)
{
	int i = 0;
	while (usedLetters[i] != '\0')
	{
		if (usedLetters[i] == c)
			return 1;
		i++;
	}
	//usedLetters[i] = c;
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
void completeCurrentWord(SInt8 c)
{
	int i = 0;
	while (word[i] != '\n')
	{
		if (word[i] == c)
			currentWord[i] = c;
		i++;
	}
}

void displayCurrentWord()
{
	int i = 0;
	int c = 0;
	int j = 0;
	while (word[i] != '\n')
	{
		i++;
		c++;
	}
	printf("%s", "Current word: ");
	for (j = 0; j < c; j++)
		printf("%c%c", currentWord[j],' ');
	printf("\n\n");
}
Boolean guessedAllLetters()
{

	int i = 0;
	int c = 0;
	int j = 0;
	Boolean ok = 1;
	while (word[i] != '\n')
	{
		i++;
		c++;
	}
	for (j = 0; j < c; j++)
		if (currentWord[j] == '_')
		{
			return 0;
			printf("%c", currentWord[j]);
		}
	return 1;
}

void printBody(int mistakes) {
	switch (mistakes) {

	case 6: body[6] = '\\'; break;
	case 5: body[5] = '/'; break;
	case 4: body[4] = '\\'; break;
	case 3: body[3] = '/'; break;
	case 2: body[2] = '|'; break;
	case 1: body[1] = ')', body[0] = '('; break;
	default: break;

	}

	printf("\t _________\n"
		"\t|         |\n"
		"\t|        %c %c\n"
		"\t|        %c%c%c\n"
		"\t|        %c %c\n"
		"\t|             \n"
		"\t|             \n\n\n", body[0], body[1], body[3],
		body[2], body[4], body[5], body[6]);
}

void displayUsedLetters()
{
	int i = 0;
	printf("%s", "Used letters: ");
	while (usedLetters[i] != '\0')
	{
		printf("%c", usedLetters[i]);
		i++;
	}
	printf("\n");
}

void switchState()
{
	while (1)
	{
		switch (state)
		{
		case INIT:
			read_input(word, file_name);
			printf("%s%s", "Guess this word: ",word);
			initVariables();
			printBody(6 - lives);
			state = INPUT;
		case INPUT:
			printf("%s%d\n","Lives: ", lives);
			displayCurrentWord();
			displayUsedLetters();
			printf("%s","Guess a letter: ");
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
				else
				{
					completeCurrentWord(character);
				}
			}
			state = DISPLAY;
		case DISPLAY:
			system("cls");
			printBody(6-lives);
			state = FINAL;
		case FINAL:
			if (guessedAllLetters()==1)
			{
				printf("You won!\n");
				ok = 0;
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
			else if (lives == 0)
			{
				ok = 0;
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