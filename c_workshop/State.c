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
#define ALPHABET_SIZE 28

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/
typedef enum MyEnum
{
	INIT, INPUT, PROCESS, DISPLAY, FINAL
}State_en;
static UInt8 usedLetters[ALPHABET_SIZE] ;
static UInt8 lives;
static UInt8 currentWord[WORD_MAX_LEN];
static UInt8 character;
static UInt8 str[WORD_MAX_LEN];
static State_en state;
static UInt8 file_name[20];
static UInt8 word[WORD_MAX_LEN];
//static UInt8 continueGame;
static Boolean ok;
static Boolean correctWord;
static UInt8 buff;
static UInt8 body[100];
static UInt8 startMessage[10];
static Boolean isNotAlpha;
static Boolean isInUsedLetters;
static Boolean isString;
static Boolean gotInvalidChars;
/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : init
*//**
*	This function is used to place our state machine to be in the "INIT" state.
*	Param[in]:
*     file_name [char*]
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void init(UInt8 *fileName)
{
	state = INIT;
	strcpy(file_name, fileName);
}

/******************************************************************************
* Function : initVariables
*//**
*	This function is used to initialize our variables( It is used each time we start a new game ).
*	Param[in]:
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void initVariables()
{
	memset(usedLetters, '\0', sizeof(usedLetters));
	lives = 6;
	memset(currentWord, '_', sizeof(currentWord));
	character = '\0';
	ok = 0;
	memset(body, '\0', sizeof(body));
	correctWord = 0;
	memset(str, '\0', sizeof(str));
	memset(startMessage, '\0', sizeof(startMessage));
	isString=0;
	gotInvalidChars = 0;
}

/******************************************************************************
* Function : inUsedLetters
*//**
*	This function is used to verify if a character is in our array with used letters.
*	Param[in]:
*	  c[char]
*  Param[out]:
*     none
*	Return:
*	  bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean inUsedLetters(UInt8 c)
{
	SInt16 i = 0;
	while (usedLetters[i] != '\0')
	{
		if (usedLetters[i] == c)
			return 1;
		i++;
	}
	//usedLetters[i] = c;
	return 0;
}

/******************************************************************************
* Function : addToUsedLetters
*//**
*	This function is used to add our character to the used letters
*	Param[in]:
*	  c[char]
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/

void addToUsedLetters(UInt8 c)
{
	SInt16 i = 0;
	SInt16 j;
	SInt16 lenUsedLetters = lenOfString(usedLetters);
	while (usedLetters[i] != '\0' && c>usedLetters[i])
	{
		i++;
	}
	for (j = lenUsedLetters; j > i; j--)
	{
		usedLetters[j] = usedLetters[j - 1];
	}
	usedLetters[i] = c;
}

/******************************************************************************
* Function : isInWord
*//**
*	This function is used to verify if a character is in our word
*	Param[in]:
*	  c[char]
*  Param[out]:
*     none
*	Return:
*	  bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean isInWord(UInt8 c) 
{
	Boolean ok = 0;
	SInt16 i = 0;
	while (word[i] != '\0' && ok==0)
	{
		if (word[i] == c)
			return 1;
		i++;
	}
	return 0;
}

/******************************************************************************
* Function : completeCurrentWord
*//**
*	This function is used to add the character to the current try
*	Param[in]:
*	  c[char]
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void completeCurrentWord(UInt8 c)
{
	SInt16 i = 0;
	while (word[i] != '\n')
	{
		if (word[i] == c)
			currentWord[i] = c;
		i++;
	}
}

/******************************************************************************
* Function : finishCurrentWord
*//**
*	This function is used to add every character from the word in the currentWord
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void finishCurrentWord()
{
	SInt16 i = 0;
	while (word[i] != '\n')
	{
			currentWord[i] = word[i];
		i++;
	}
}

/******************************************************************************
* Function : printCurrentWord
*//**
*	This function is used to display the word with the letters we guessed so far
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
//void printCurrentWord2()
//{
//
//	int i = 0;
//	int j = 0;
//	while (word[i] != '\n')
//	{
//		i++;
//	}
//	printf("%s", "\t\t\tCurrent word: ");
//	for (j = 0; j < i; j++)
//		printf("%c%c", currentWord[j],' ');
//	printf("\n");
//}

UInt8* printCurrentWord()
{
	UInt8 testStr[100]="";
	SInt16 i = 0;
	while (word[i] != '\n')
	{
		testStr[2 * i] = currentWord[i];
		testStr[2 * i + 1] = ' ';
		i++;
	}
	//for (int j = 0; j < i; j++)
	//{
	//	testStr[2 * j] = currentWord[j];
	//	testStr[2 * j + 1] = ' ';
	//}
	/*printf("\n");*/
	return testStr;
}

/******************************************************************************
* Function : printUsedLetters
*//**
*	This function is used to display our used letters
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
UInt8* printUsedLetters()
{
	UInt8 testStr[100] = "";
	SInt16 i = 0;
	while (usedLetters[i] != '\0')
	{
		testStr[i] = usedLetters[i];
		i++;
	}
	return testStr;
}

//void printUsedLetters2()
//{
//	int i = 0;
//	printf("%s", "\t\t\tUsed letters: ");
//	while (usedLetters[i] != '\0')
//	{
//		printf("%c ", usedLetters[i]);
//		i++;
//	}
//	printf("\n\n\n");
//}


/******************************************************************************
* Function : guessedAllLetters
*//**
*	This function is used to verify if we guessed all letters
*	Param[in]:
*	  none
*  Param[out]:
*     none
*	Return:
*	  bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean guessedAllLetters()
{

	SInt16 i = 0;
	SInt16 c = 0;
	SInt16 j = 0;
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

/******************************************************************************
* Function : printBody
*//**
*	This function is used to display the hangman in the current stage
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
//void printBody() {
//	UInt16 mistakes = 6 - lives;
//	switch (mistakes) {
//
//	case 6: body[6] = '\\'; break;
//	case 5: body[5] = '/'; break;
//	case 4: body[4] = '\\'; break;
//	case 3: body[3] = '/'; break;
//	case 2: body[2] = '|'; break;
//	case 1: body[1] = ')', body[0] = '('; break;
//	default: break;
//
//	}
//
//	printf("\t\t\t _________\n"
//		"\t\t\t|         |\n"
//		"\t\t\t|        %c %c\n"
//		"\t\t\t|        %c%c%c\n"
//		"\t\t\t|        %c %c\n"
//		"\t\t\t|             \n"
//		"\t\t\t|             \n\n\n", body[0], body[1], body[3],
//		body[2], body[4], body[5], body[6]);
//}

void printBody() {
	UInt16 mistakes = 6 - lives;
	switch (mistakes) {

	case 6: body[6] = '\\'; break;
	case 5: body[5] = '/'; break;
	case 4: body[4] = '\\'; break;
	case 3: body[3] = '/'; break;
	case 2: body[2] = '|'; break;
	case 1: body[1] = ')', body[0] = '('; break;
	default: break;

	}
	UInt8 s[100]="";
	strcpy(s,printCurrentWord());
	UInt8 s2[100]="";
	strcpy(s2, printUsedLetters());
	printf("\t\t\t _________\n"
		"\t\t\t|         |\n"
		"\t\t\t|        %c %c\n"
		"\t\t\t|        %c%c%c\n"
		"\t\t\t|        %c %c\t\t\t\t\t\t\tLives: %d\n"
		"\t\t\t|             \t\t\t\t\t\t\tCurrent word: %s\n"
		"\t\t\t|             \t\t\t\t\t\t\tUsed letters: %s\n\n\n\n\n", body[0], body[1], body[3],
		body[2], body[4], body[5], body[6],lives,s,s2);
}


/******************************************************************************
* Function : printHangman
*//**
*	This function is used to display the hangman title in big ascii
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void printHangman()
{
	printf("\t\t\t88\n"
		"\t\t\t88\n"
		"\t\t\t88\n"
		"\t\t\t88,dPPYba,  ,adPPYYba, 8b,dPPYba,   ,adPPYb,d8 88,dPYba,,adPYba,  ,adPPYYba, 8b,dPPYba,\n"
		"\t\t\t88P'    \"8a \"\"     `Y8 88P'   `\"8a a8\"    `Y88 88P\'   \"88\"    \"8a \"\"     \`Y8 88P'   `\"8a\n"
		"\t\t\t88       88 ,adPPPPP88 88       88 8b       88 88      88      88 ,adPPPPP88 88       88\n"
		"\t\t\t88       88 88,   , 88 88       88 \"8a,   ,d88 88      88      88 88,    ,88 88       88\n"
		"\t\t\t88       88 `\"8bbdP\"Y8 88       88  `\"YbbdP\"Y8 88      88      88 `\"8bbdP\"Y8 88       88\n"
		"\t\t\t                                    aa,   , 88\n"
		"\t\t\t                                     \"Y8bbdP\"\n\n\n\n\n\n\n");
}
void printEntireBody() {
	body[6] = '\\';
	body[5] = '/';
	body[4] = '\\';
	body[3] = '/';
	body[2] = '|';
	body[1] = ')';
	body[0] = '(';

	printf("\t _________\n"
		"\t|         |\n"
		"\t|        %c %c\n"
		"\t|        %c%c%c\n"
		"\t|        %c %c\n"
		"\t|             \n"
		"\t|             \n\n\n", body[0], body[1], body[3],
		body[2], body[4], body[5], body[6]);
}




/******************************************************************************
* Function : readFromFileAndPrint
*//**
*	This function is used to read the word from file and print it
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void readFromFileAndPrint()
{
	read_input(word, file_name);
	
}

/******************************************************************************
* Function : printNumberOfLives
*//**
*	This function is used to print our number of lives
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void printNumberOfLives()
{
	printf("\t\t\t%s%d\n", "Lives: ", lives);
}
/******************************************************************************
* Function : areStringsEqual
*//**
*	This function is used to verify is two strings are equal
*	Param[in]:
*	  none
*  Param[out]:
*     none
*	Return:
*     bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean areStringsEqual()
{
	SInt16 i = 0;
	SInt16 lenStr = lenOfString(str);
	SInt16 lenWord = lenOfString(word);
	if (lenStr > lenWord)
	{
		while (i < lenStr)
		{
			if (str[i] != word[i])
				return 0;
			i++;
		}
	}
	else
	{
		while (i < lenWord)
		{
			if (str[i] != word[i])
				return 0;
			i++;
		}
	}
	return 1;
}
/******************************************************************************
* Function : hasInvalidChars
*//**
*	This function is used to see if the string has characters different of alpha characters
*	Param[in]:
*	  s [char*]
*  Param[out]:
*     none
*	Return:
*     bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean hasInvalidChars(UInt8* s)
{
	SInt16 i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (isalpha(s[i]) == 0)
			return 1;
		i++;
	}
	return 0;
}

/******************************************************************************
* Function : toLower
*//**
*	This function is used to transform a capital letter into a small one
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void toLower()
{
	if(character>='A' && character<='Z')
	character = character + 32;
}
/******************************************************************************
* Function : readFromUser
*//**
*	This function is used to read a character or a string(if you read a string and it's not the random word you lose)
*	Param[in]:
*	  none
*  Param[out]:
*     none
*	Return:
*    bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void readFromUser()
{
	printf("%s", "\t\t\tGuess a letter: ");
	scanf("%s", str);
	//if (lenOfString(str) == 1)
	//{
	//	character = str[0];
	//	toLower(character);
	//	return 1;
	//}
	//else
	//{
	//	//if (hasInvalidChars(str) == 1)
	//	//{
	//	//	/////TO DO
	//	//	printf("a");
	//	//}
	//	//else if (areStringsEqual() == 1)
	//	//	finishCurrentWord();
	//	//else
	//	//{
	//	//	lives = 0;
	//	//	entireWord = 0;
	//	//}
	//	return 0;
	//}

	/*printf("%d", lenOfString(s));*/
	/*scanf("%c", &character);
	scanf("%c", &buff);*/
}


//void readFromUser()
//{
//	printf("%s", "Guess a letter: ");
//	scanf("%s", &str);
//	//if (lenOfString(str) == 1)
//	//{
//	//	character = str[0];
//	//	toLower(character);
//	//	return 1;
//	//}
//	//else
//	//{
//	//	//if (hasInvalidChars(str) == 1)
//	//	//{
//	//	//	/////TO DO
//	//	//	printf("a");
//	//	//}
//	//	//else if (areStringsEqual() == 1)
//	//	//	finishCurrentWord();
//	//	//else
//	//	//{
//	//	//	lives = 0;
//	//	//	entireWord = 0;
//	//	//}
//	//	return 0;
//	//}
//
//	/*printf("%d", lenOfString(s));*/
//	/*scanf("%c", &character);
//	scanf("%c", &buff);*/
//}

/******************************************************************************
* Function : lenOfString
*//**
*	This function is used to return the length of a string
*	Param[in]:
*	  s [char*]
*  Param[out]:
*     none
*	Return:
*     int
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
int lenOfString(UInt8 *s)
{
	SInt16 i = 0;
	while (s[i] != '\0' && s[i]!='\n')
		i++;
	return i;
}
/******************************************************************************
* Function : printNotAChar
*//**
*	This function is used to print if we don't read a character
*	Param[in]:
*	  character[char]
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void printNotAChar(UInt8 c)
{
		printf("\t\t\t%s%c%s%s", "'", c, "'", " is Not a character!\n");
}

/******************************************************************************
* Function : printInUsedLetters
*//**
*	This function is used to print if we read a character that we already used
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void printInUsedLetters(UInt8 c)
{
	printf("\t\t\t%c%s", c, " is already used!\n");
}

/******************************************************************************
* Function : startOrEnd
*//**
*	This function is used to ask you if you want to start a new game or end the session
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void startOrEnd()
{
	printf("%s", "\t\t\tDo you want to start a new game? (Y/N): ");
	ok = 0;
	while (ok == 0)
	{
		scanf("%s", &startMessage);
		/*scanf("%c", &continueGame);
		scanf("%c", &buff);*/
		if (lenOfString(startMessage) != 1)
		{
			printf("Write Y/N: ");
		}
		else if (lenOfString(startMessage) == 1 && startMessage[0]!='Y' && startMessage[0] != 'N')
		{
			printf("Write Y/N: ");
		}
		else
		if (startMessage[0] == 'Y')
		{
			ok = 1;
			state = INIT;
			system("cls");
		}
		else if (startMessage[0] == 'N')
		{
			ok = 1;
			exit(0);
			printf("%s", "a");
		}
		
	}
}

/******************************************************************************
* Function : loseALife
*//**
*	This function is used to lose a life if you don't guess a good character
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void loseALife()
{
	lives = lives - 1;
}
/******************************************************************************
* Function : dead
*//**
*	This function is used to check if we have lives
*	Param[in]:
*	  none
*  Param[out]:
*     none
*	Return:
*	  bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean dead()
{
	if (lives == 0)
		return 1;
	return 0;

}
/******************************************************************************
* Function : validLetter
*//**
*	This function is to manage what happens if the character is not in the used letters array and is an alpha character
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void validLetter()
{
	addToUsedLetters(character);
	if (isInWord(character) == 0)
		loseALife();
	else
	{
		completeCurrentWord(character);
	}
}

/******************************************************************************
* Function : printEverything
*//**
*	This function is to print every detail on the screen
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void printEverything()
{
	printf("%s%s\n\n", "Guess this word: ", word);
	printHangman();
	printBody();
}

//void printEverything2()
//{
//	printf("%s%s\n\n", "Guess this word: ", word);
//	printHangman();
//	printBody();
//	printNumberOfLives();
//	printCurrentWord();
//	printUsedLetters();
//}

/******************************************************************************
* Function : isCharacter
*//**
*	This function is to return if we read a character or a string
*	Param[in]:
*	  none
*  Param[out]:
*     none
*	Return:
*	  bool
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
Boolean isCharacter()
{
	if (lenOfString(str) == 1)
	{
		character = str[0];
		toLower(character);
		return 1;
	}
	else
	{ 
		SInt16 lenStr = lenOfString(str);
		for (SInt16 i = 0; i < lenStr; i++)
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] = str[i] + 32;
		return 0;
	}
	
}

/******************************************************************************
* Function : manageString
*//**
*	This function is to manage the steps for a string
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void manageString()
{
	if (hasInvalidChars(str) == 1)
	{
		gotInvalidChars = 1;
	}
	else if (areStringsEqual() == 1)
	{
		correctWord = 1;
		finishCurrentWord();
	}
	else
	{
		lives = 0;
	}
}

/******************************************************************************
* Function : manageChar
*//**
*	This function is to manage the steps for a character
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void manageChar()
{
	if (isalpha(character) == 0)
	{
		isNotAlpha = 1;
	}
	else if (inUsedLetters(character) == 1)
	{
		isInUsedLetters = 1;
	}
	else
	{
		validLetter();
	}
}
/******************************************************************************
* Function : switchState
*//**
*	This function is used to switch the state to our state machine and controll the application
*	Param[in]:
*	  none
*  Param[out]:
*     none
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  18/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void switchState()
{
	while (1)
	{
		switch (state)
		{
		case INIT:
			readFromFileAndPrint();
			initVariables();
			printEverything();
			state = INPUT;
		case INPUT:
			readFromUser();
			state = PROCESS;
		case PROCESS:
			if (isCharacter() == 0)
			{
				manageString();
				isString = 1;
			}
			else
			{
				manageChar();
			}
			state = DISPLAY;
		case DISPLAY:
			if (isString == 1)
			{
				if (gotInvalidChars == 1)
				{
					system("cls");
					printEverything();
					printf("\t\t\tYou got an invalid character in your text\n");
					gotInvalidChars = 0;
				}
				else
				{
					system("cls");
					if (correctWord == 1)
					{
						printEverything();
					}
					else
						printEntireBody();
				}
			}
			else
			if (isNotAlpha == 1)
			{
				system("cls");
				printEverything();
				printNotAChar(character);
				isNotAlpha = 0;
			}
			else if (isInUsedLetters == 1)
			{
				system("cls");
				printEverything();
				printInUsedLetters(character);
				isInUsedLetters = 0;
			}
			else
			{
				system("cls");
				printEverything();
			}
			isString = 0;
			state = FINAL;
		case FINAL:
			if (guessedAllLetters()==1)
			{
				printf("\t\t\tYou won!\n");
				startOrEnd();
			}
			else if (dead() == 1)
			{
				printf("You lost!\n");
				startOrEnd();
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


/*************** END OF FUNCTIONS ***************************************************************************/