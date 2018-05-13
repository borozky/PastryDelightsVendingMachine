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

Coin *create_coin(char *line);
Boolean is_valid_denomination(int cents);
int get_cent_value(Denomination denomination);
