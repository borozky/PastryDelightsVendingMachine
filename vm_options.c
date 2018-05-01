/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_options.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"
#define STOCK_LINE_SIZE 1024
#define COIN_LINE_SIZE 64

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{
    if (system == NULL) {
        system = (VmSystem *) malloc(sizeof(*system));
        (*system).coinFileName = DEFAULT_COIN_FILE;
        (*system).stockFileName = DEFAULT_STOCK_FILE;
    }

    if (loadData(system, (*system).stockFileName, (*system).coinFileName) == FALSE) {
        return FALSE;
    }

    return TRUE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{ 
    return;
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    if (loadStock(system, stockFileName) && loadCoins(system, coinsFileName)) {
        return TRUE;
    }

    /* TODO: clean up here if above condition is false */

    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE *stock_file;
    char *line;
    Stock *stock;
    
    /* open stock file in read-mode, return FALSE if not found */
    stock_file = fopen(fileName, "r");
    if (stock_file == NULL) {
        fprintf(stderr, "Stock file '%s' doesn't exists or unreadable", fileName);
        return FALSE;
    }

    /* creates a linked list (see vm_stock.c) */
    (*system).itemList = create_list();

    /* gets each lines */
    line = (char *) malloc(sizeof(*line) * STOCK_LINE_SIZE);
    while (TRUE) {
        fgets(line, STOCK_LINE_SIZE, stock_file);
        if (feof(stock_file)) {
            break;
        }

        /* create and insert the stock into VmSystem's itemList */
        stock = create_stock(line);
        add_stock_item((*system).itemList, stock);
    }

    return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    FILE *coin_file;
    char *line;
    Coin *coin;
    int line_number;

    /* open the coin file, or return false is not found */
    coin_file = fopen(fileName, "r");
    if (coin_file == NULL) {
        fprintf(stderr, "Coin file '%s' doesn't exists or unreadable", fileName);
        return FALSE;
    }

    /* read each line */
    line_number = 0;
    line = (char *) malloc(sizeof(*line) * COIN_LINE_SIZE);
    while (TRUE) {
        fgets(line, COIN_LINE_SIZE, coin_file);
        if (feof(coin_file)) {
            break;
        }

        /* add new coin */
        coin = create_coin(line);
        (*system).cashRegister[line_number] = *coin;
        line_number += 1;
    }


    return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
    return FALSE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{ 
    Node *node;
    Stock *stock;

    node = (*system).itemList->head;
    printf("Items Menu\n");

    if (node == NULL) {
        printf("Sorry, there are no items in the list\n");
        return;
    }

    printf("%5s | %30s | %10s | %7s \n", "ID", "Name", "Available", "Price");
    printf("---------------------------------------------------\n");

    while (node != NULL) {
        stock = (*node).data;
        printf("%5s | %30s | %10d | $%-2d.%5d \n",
            (*stock).id,
            (*stock).name,
            (*stock).onHand,
            (*stock).price.dollars,
            (*stock).price.cents
        );
        node = (*node).next;
    }
    printf("DISPLAY ITEMS\n");
    return;
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{ 
    printf("PURCHASE ITEMS\n");
    return;
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ 
    printf("SAVE AND EXIT\n");
    return;
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{ 
    printf("ADD ITEM\n");
    return;
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ 
    printf("REMOVE ITEM\n");
    return;
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{ 
    printf("DISPLAY COINS\n");
    return;
}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{ 
    printf("RESET STOCK\n");
    return;
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{ 
    printf("RESET COINS\n");
    return;
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{ 
    printf("ABORT PROGRAM\n");
    return;
}
