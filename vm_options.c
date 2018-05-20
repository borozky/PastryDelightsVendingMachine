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
char *get_payment();
Boolean add_payment(int *payments, int payment);
void display_payments(int *payments);
int *get_all_payments(int item_price_in_cents);
int get_total_amount(int *payments);
int *get_coins_change(int change, Coin cash_register[NUM_DENOMS]);
void display_change(int *change);
void add_to_cash_register(VmSystem *vmSystem, int *payment);
void refund(VmSystem *vmSystem, int *payments);

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
    char *id;
    char *payment;
    int payment_in_cents;
    int item_price;
    int *payments;
    int amount_paid;
    int change;
    int *coins_change;

    Stock *stock;

    id = nextline_required("Please enter the id of the item your wish to purchase: ", ID_LEN + NULL_SPACE, "Not a valid ID\n");
    stock = get_stock_item_by_id(system->itemList, id);

    if (stock == NULL) {
        printf("Item with ID %s cannot be found", id);
        return;
    }

    if (stock->onHand <= 0) {
        printf("Item \"%s\" has ran out of stock.\n", stock->name);
        return;
    }

    printf("You have selected \"%s  %s\". This will cost you $%d.%02d\n", 
        stock->name, stock->desc, stock->price.dollars, stock->price.cents
    );

    printf("Please hand over your payment - type in the value of each note/coin in cents\n");
    printf("Press enter twice to cancel this purchase.\n");

    item_price = (stock->price.dollars * 100) + stock->price.cents;

    payments = get_all_payments(item_price);
    if (payments == NULL) {
        printf("Purchase cancelled.\n");
        return;
    }

    add_to_cash_register(system, payments);
    stock->onHand -= 1;

    /* process transaction */
    amount_paid = get_total_amount(payments);
    change = amount_paid - item_price;

    /* pay the change first*/
    coins_change = get_coins_change(change, system->cashRegister);

    /* if for some reason, seller cannot pay the change, refund and cancel transaction */
    if (get_total_amount(coins_change) != change) {
        refund(system, payments);
        stock->onHand += 1;
        printf("Sorry, we cannot send back the change. {TODO: reason}");
    } 
    else {
        printf("Thank you. Here is your %s, and your change of $%d.%02d: ", stock->name, (change / 100), (change % 100));
        display_change(coins_change);
        printf("\n");
    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ 
    saveStock(system);
    printf("Stock has been saved to %s\n", system->stockFileName);

    saveCoins(system);
    printf("Coins has been saved to %s\n", system->coinFileName);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{ 
    char price_str[10];
    double price;
    int dollars, cents;
    
    Stock *stock = (Stock *) malloc(sizeof(Stock));

    strcpy(stock->id, next_stock_id(system->itemList));
    strcpy(stock->name, nextline("Enter the item name: ", sizeof(stock->name)));
    strcpy(stock->desc, nextline("Enter the item description: ", sizeof(stock->desc)));

    do {
        strcpy(price_str, nextline("Enter the price for this item: ", 10));
        price = atof(price_str);
        if (price == 0.0) {
            continue;
        }
        dollars = (int) price;
        cents = (int) ((double) price - (double)dollars);
        break;
    }
    while (TRUE);

    stock->price.dollars = dollars;
    stock->price.cents = cents;
    stock->onHand = 0;

    add_stock_item(system->itemList, stock);
    printf("This item \"%s - %s\" has now been added to the menu.\n", stock->name, stock->desc);
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ 
    char *id;
    char *name;
    char *description;
    Stock *stock;

    Boolean isRemoved = FALSE;

    id = nextline("Enter the id of the item to remove from the menu: ", ID_LEN + NULL_SPACE);
    stock = get_stock_item_by_id(system->itemList, id);

    if (stock == NULL) {
        printf("Cannot remove item for ID %s because it doesn't exists\n", id);
        return;
    }

    strcpy(name, stock->name);
    strcpy(description, stock->desc);

    isRemoved = remove_stock_item_by_id(system->itemList, id);

    if (isRemoved == FALSE) {
        printf("Cannot remove item for ID %s\n", id);
        return;
    }

    printf("\"%s - %s  %s\" has been removed from the system.\n", id, name, description);
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
    loadStock(system, DEFAULT_STOCK_FILE);
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
    loadCoins(system, DEFAULT_COIN_FILE);
    return;
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{ 
    systemFree(system);
    return;
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

char *get_payment() {
    char *line = (char *) malloc(4 * sizeof(char));
    fgets(line, sizeof(line), stdin);

    if (strtok(line, "\n") == NULL) {
        readRestOfLine();
        return NULL;
    }
    return line;
}

Boolean add_payment(int *payments, int payment) {
    if (payments == NULL) {
        return FALSE;
    }

    while (payments) {
        if (*payments <= 0) {
            *payments = payment;
            return TRUE;
        }
        payments++;
    }

    return FALSE;
}

void display_payments(int *payments) {
    if (payments == NULL) {
        fprintf(stderr, "There are no payments");
    }

    printf("Payments:\n");
    while (payments) {
        if (*payments > 0) {
            printf("%d\n", *payments);
            payments++;
            continue;
        }
        break;
    }
}

int *get_all_payments(int item_price_in_cents) {
    char *payment;
    int *actual_payments;
    int i = 0;

    int payment_in_cents = 0;
    int num_payments = 0;
    int cents_remaining = item_price_in_cents;
    int *payments = (int *) malloc(item_price_in_cents * sizeof(int));

    do {
        printf("You still need to give us $%d.%02d: ", (cents_remaining / 100), (cents_remaining % 100));

        payment = get_payment();
        if (payment == NULL) {
            return NULL;
        }

        payment_in_cents = atoi(payment);
        
        if (is_valid_denomination(payment_in_cents) == FALSE) {
            printf("%d is not a valid denomination of money.\n", payment_in_cents);
            continue;
        }

        add_payment(payments, payment_in_cents);
        num_payments += 1;
        cents_remaining -= payment_in_cents;

        if (cents_remaining > 0) {
            continue;
        } else {
            break;
        }

    } while (TRUE);

    actual_payments = (int *) malloc(num_payments * sizeof(int));
    for (i = 0; i < num_payments; i++) {
        actual_payments[i] = payments[i];
    }
    free(payments);

    return actual_payments;
}

int get_total_amount(int *payments) {
    int amount_paid = 0;
    while (payments) {
        if (is_valid_denomination(*payments) == FALSE) {
            return amount_paid;
        }

        amount_paid += *payments;
        payments++;
    }
    return amount_paid;
}

int *get_coins_change(int change, Coin cash_register[NUM_DENOMS]) {
    int i = 0, j = 0;
    int change_remaining = change;
    int *coins = (int *) malloc(change * sizeof(int));
    int num_coins = 0;
    int num_avail_coins = 0;
    int coins_added = 0;
    int cent_value = 0;

    while (change_remaining > 0) {
        for (i = 0; i < NUM_DENOMS; i++) {
            num_coins = 0;

            /* skip this denomination is not enough coins available */
            num_avail_coins = cash_register[i].count;
            if (num_avail_coins <= 0) {
                continue;
            }

            cent_value = get_cent_value(cash_register[i].denom);

            /* if coin is enough to pay the change */
            num_coins = change_remaining / cent_value;
            for (j = coins_added; j < num_coins + coins_added; j++) {
                coins[j] = cent_value;
            }

            coins_added += num_coins;
            change_remaining %= cent_value;
        }
    }

    return coins;
}

void display_change(int * change) {
    while (change) {
        if (is_valid_denomination(*change) == FALSE) {
            return;
        }

        if (*change < 100) {
            printf("%d c ", *change);
        }
        else {
            printf("$%d ", (*change / 100));
        }
        change++;
    }
}

void add_to_cash_register(VmSystem *vmSystem, int *payment) {
    int i = 0;
    while (payment) {
        if (is_valid_denomination(*payment) == FALSE) {
            return;
        }

        for (i = 0; i < NUM_DENOMS; i++) {
            if ( *payment == get_cent_value(vmSystem->cashRegister[i].denom) ) {
                vmSystem->cashRegister[i].count += 1;
            }
        }
        payment++;
    }
}

void refund(VmSystem *vmSystem, int *payment){
    int i = 0;
    while (payment) {
        for (i = 0; i < NUM_DENOMS; i++) {
            if ( *payment == get_cent_value(vmSystem->cashRegister[i].denom) ) {
                vmSystem->cashRegister[i].count -= 1;
            }
        }
        payment++;
    }
}

