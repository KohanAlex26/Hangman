/*******************************************************************************
* Title                 :   Read Input
* Filename              :   readInput.c
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
#include <stdlib.h>
#include <string.h>
#include <time.h>	
#include "types.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
// the max number of words
#define SIZE 100

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : read_input
*//**
*	This function is used to get the input from a file.
*	Param[in]: 
*     word [char*]
*     file_name [char*]
*  Param[out]:
*     none 
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Software Version    Initials   Description
*  05/08/2021    1.0.0            OW      Module Created
*
*******************************************************************************/
void read_input(UInt8* word, UInt8* file_name)
{
	// Buffer to store data
	UInt8 buffer[SIZE][WORD_MAX_LEN]; 
	FILE* file;

	file = fopen(file_name, "r");
	SInt8 i = 0;

	while (fgets(buffer[i], sizeof(buffer), file)) {

		// printf("%d %s", i , buffer[i]);
		i++;
	}

	srand(time(NULL));
	SInt8 r = rand() % i;

	strcpy(word, buffer[r]);
}

/*************** END OF FUNCTIONS ***************************************************************************/