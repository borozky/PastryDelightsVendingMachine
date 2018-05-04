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

int compare_coins(const void *coin1, const void *coin2);
int size_of_longest_stock_name(List *stock_list);
void printStock(Stock *stock, int longest_name_size);

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
    FILE *stock_file;
    Stock *stock;
    Node *node;
    char *line;

    stock_file = fopen((*system).stockFileName, "a");
    if (stock_file == NULL) {
        fprintf(stderr, "File '%s' cannot be found or unwritable.", (*system).stockFileName);
        return FALSE;
    }

    node = (*system).itemList->head;
    while (node != NULL) {
        stock = (*node).data;

        line = (char *) malloc(sizeof(*line) * sizeof(*stock));

        sprintf(line, "%s%s%s%s%s%s%d.%02d%s%d",
            (*stock).id,
            STOCK_DELIM,
            (*stock).name,
            STOCK_DELIM,
            (*stock).desc,
            STOCK_DELIM,
            (*stock).price.dollars,
            (*stock).price.cents,
            STOCK_DELIM,
            (*stock).onHand
        );

        printf("LINE: %s\n", line);

        /* TODO: Save to stock.dat */

        node = (*node).next;

    }

    fclose(stock_file);

    return FALSE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    FILE *coin_file;
    char *line;
    int line_number;
    int cents;

    coin_file = fopen((*system).coinFileName, "a");
    if (coin_file == NULL) {
        fprintf(stderr, "Coin file '%s' doesn't exists or unreadable\n", (*system).coinFileName);
        return FALSE;
    }

    line_number = 0;
    while (line_number < NUM_DENOMS) {
        line = (char *) malloc(COIN_LINE_SIZE);

        cents = get_cent_value((*system).cashRegister[line_number].denom);
        
        sprintf(line, "%d%s%d",
            cents,
            COIN_DELIM,
            (*system).cashRegister[line_number].count
        );

        printf("COIN: %s\n", line);

        line_number += 1;
    }



    fclose(coin_file);
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
    int longest_name_size = size_of_longest_stock_name((*system).itemList);

    printf("Items Menu\n");
    node = (*system).itemList->head;
    if (node == NULL) {
        printf("Sorry, there are no items in the list\n");
        return;
    }

    printf(" %-5s | %-*s | %-10s | %-7s \n", "ID", longest_name_size, "Name", "Available", "Price");
    printf("---------------------------------------------------------\n");

    while (node != NULL) {
        stock = (*node).data;
        printStock(stock, longest_name_size);
        node = (*node).next;
    }
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
    printf("SAVE AND EXIT started.\n");
    saveStock(system);
    saveCoins(system);
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
    int i;
    int cents;
    char denomination_name[13];

    printf("Coins Summary\n");
    printf("---------\n");
    printf("Denomination | Count\n\n");

    /* sort by denomination value - 5 cents is 0 -> 10 dollars is 7 */
    qsort((*system).cashRegister, NUM_DENOMS, sizeof((*(*system).cashRegister)), compare_coins);

    for (i = 0; i < NUM_DENOMS; i++) {
        cents = get_cent_value((*system).cashRegister[i].denom);

        if (cents < 100) {
            sprintf(denomination_name, "%d cents", cents);
        } else {
            sprintf(denomination_name, "%d dollars", (cents / 100));
        }

        printf("%12s | %d\n", denomination_name, (*system).cashRegister[i].count);
    }

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

int compare_coins(const void *coin1, const void *coin2) {
    Coin *c1;
    Coin *c2;

    c1 = (Coin *) coin1;
    c2 = (Coin *) coin2;

    if (c1->denom < c2->denom) {
        return -1;
    }
    else if (c1->denom > c2->denom) {
        return 1;
    }
    else {
        return 0;
    }
}

int size_of_longest_stock_name(List *stock_list) {
    Node *node;
    Stock *stock;
    int size;
    char *name;

    size = 0;
    if (stock_list == NULL) {
        return size;
    }

    node = (*stock_list).head;
    while (node != NULL) {
        stock = (*node).data;
        if (strlen(stock->name) > size) {
            size = strlen(stock->name);
        }
        node = (*node).next;
    }

    return size;
}

void printStock(Stock *stock, int longest_name_size) {
    if (stock == NULL || longest_name_size < 0) {
        return;
    }

    printf(" %-5s |", (*stock).id);
    printf(" %-*s |", longest_name_size, (*stock).name);
    printf(" %-10d |", (*stock).onHand);
    printf(" $%2d.%02d ", (*stock).price.dollars, (*stock).price.cents);
    printf("\n");
}
