/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20

#define COIN_DELIM ","

#endif


/**
 * Creates a new coins based on the new line of text provided
 **/
Coin *create_coin(char *line);


/**
 * Check if a number is valid denomination. Requires a value in cents
 **/
Boolean is_valid_denomination(int cents);


/**
 * Gets the cent value of a particular denomination
 **/
int get_cent_value(Denomination denomination);
