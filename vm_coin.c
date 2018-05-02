/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

Coin *create_coin(char *line) {
    Coin *coin;
    char *token; /* save string tokens here */
    char *end_pointer; /* storage for non-int values processed by strtol() */
    int num_cents;
    int count;

    /* coin = new Coin(); */
    coin = (Coin *) malloc(sizeof(*coin));

    /* split the line provided */
    token = strtok(line, COIN_DELIM);
    num_cents = strtol(token, &end_pointer, 10);
    
    switch (num_cents) {
        case 1000:
            (*coin).denom = TEN_DOLLARS;
            break;
        case 500:
            (*coin).denom = FIVE_DOLLARS;
            break;
        case 200:
            (*coin).denom = TWO_DOLLARS;
            break;
        case 100:
            (*coin).denom = ONE_DOLLAR;
            break;
        case 50:
            (*coin).denom = FIFTY_CENTS;
            break;
        case 20:
            (*coin).denom = TWENTY_CENTS;
            break;
        case 10:
            (*coin).denom = TEN_CENTS;
            break;
        case 5:
            (*coin).denom = FIVE_CENTS;
            break;
        default:
            free(coin);
            fprintf(stderr, "%d is not a valid coin denomination.", num_cents);
            return NULL;
    }

    token = strtok(NULL, COIN_DELIM);
    count = strtol(token, &end_pointer, 10);
    (*coin).count = count;

    return coin;
}