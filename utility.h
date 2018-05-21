/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();


/* FUNCTIONS THAT ARE ADDED AS EXTRA HELPER METHODS */

/**
 * Ask the user to enter a line of text.
 * Note: This function will not do checking.
 * If user enters null or an empty string, it will be returned
 */
char *nextline(char *message, int size);

/**
 * Ask the user to enter a number.
 * Note: This function will not do checking. 
 * If user enters an invalid number, 0 will be returned
 **/
int nextint(char *message);

/**
 * Ask the user to enter a line of text. If line is null, this will ask again.
 * Note: If user returns string of blank character, it will still considered 
 * valid result.
 **/
char *nextline_required(char *message, int size, char *invalid_message);

/**
 * Ask the user to enter a number. If the input entered is not a number, it
 * will ask again.
 **/
int nextint_required(char *message, char *invalid_message);


#endif
