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


/**
 * Creates a new coins based on the new line of text provided
 **/
Coin *create_coin(char *line) {
    Coin *coin;
    char *token; /* save string tokens here */
    char *end_pointer; /* storage for non-int values processed by strtol() */
    int num_cents;
    int count;

    /* new Coin */
    coin = (Coin *) malloc(sizeof(*coin));

    /* split the line */
    token = strtok(line, COIN_DELIM);
    num_cents = strtol(token, &end_pointer, 10);
    
    switch (num_cents) {
        case 1000:
            coin->denom = TEN_DOLLARS;
            break;
        case 500:
            coin->denom = FIVE_DOLLARS;
            break;
        case 200:
            coin->denom = TWO_DOLLARS;
            break;
        case 100:
            coin->denom = ONE_DOLLAR;
            break;
        case 50:
            coin->denom = FIFTY_CENTS;
            break;
        case 20:
            coin->denom = TWENTY_CENTS;
            break;
        case 10:
            coin->denom = TEN_CENTS;
            break;
        case 5:
            coin->denom = FIVE_CENTS;
            break;
        default:
            free(coin);
            fprintf(stderr, "%d is not a valid coin denomination.", num_cents);
            return NULL;
    }

    token = strtok(NULL, COIN_DELIM);
    count = strtol(token, &end_pointer, 10);
    coin->count = count;

    return coin;
}

/**
 * Check if a number is valid denomination. Requires a value in cents
 **/
Boolean is_valid_denomination(int cents) {
    switch (cents) {
        case 1000:
        case 500:
        case 200:
        case 100:
        case 50:
        case 20:
        case 10:
        case 5:
            return TRUE;
        default:
            return FALSE;
    }
}

/**
 * Gets the cent value of a particular denomination
 **/
int get_cent_value(Denomination denomination) {
    switch (denomination) {
        case TEN_DOLLARS:
            return 1000;
        case FIVE_DOLLARS:
            return 500;
        case TWO_DOLLARS:
            return 200;
        case ONE_DOLLAR:
            return 100;
        case FIFTY_CENTS:
            return 50;
        case TWENTY_CENTS:
            return 20;
        case TEN_CENTS:
            return 10;
        case FIVE_CENTS:
            return 5;
        default:
            fprintf(stderr, "Not a valid denomination");
            return 0;
    }
}

