/******************************************************************************
** Student name: 	JOSHUA OROZCO
** Student number: 	s3485376
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"
#define COIN_LINE_SIZE 64

int retrieveCashRegister(FILE * coinFile, Coin cashRegister[NUM_DENOMS]);
int retrieveStocks(FILE * stockFile, List * itemList);

int main(int argc, char ** argv)
{
    FILE * coinFile;
    Coin cashRegister[NUM_DENOMS];

    coinFile = fopen(argv[2], "r");
    if (coinFile == NULL) {
        fprintf(stderr, "Coin file '%s' doesn't exists or unreadable", argv[2]);
        return EXIT_FAILURE;
    }
    
    retrieveCashRegister(coinFile, cashRegister);
    printf("Cash register: %d\n", cashRegister[1].count);
    fclose(coinFile);

    return EXIT_SUCCESS;
}


void setup (int argc, char ** argv) {
    VmSystem vmSystem;
    MenuFunction menuChoice;
    MenuItem menuItem;

    /**
     * 1st argument is the executable and will always be given
     * 2nd argument is the stock file. This should be optional.
     * 3rd argument is the coin file. This should be optional.
     */

    printf("ARGC %d\n", argc);
    switch (argc) {
        /* both stock and coin file args are missing */
        case 1:
            vmSystem.stockFileName = DEFAULT_STOCK_FILE;
            vmSystem.coinFileName = DEFAULT_COIN_FILE;
            break;
        /* stock file is given, coin file arg is missing */
        case 2:
            vmSystem.stockFileName = argv[1];
            vmSystem.coinFileName = DEFAULT_COIN_FILE;
            break;
        /* both stock and coin files are supplied */
        case 3:
        default:
            vmSystem.stockFileName = argv[1];
            vmSystem.coinFileName = argv[2];
            break;
    }
    
    initMenu(&menuItem);
    
    do {
        menuChoice = getMenuChoice(&menuItem);
    }
    while (menuChoice == NULL);
}



int retrieveCashRegister(FILE * coinFile, Coin cashRegister[NUM_DENOMS]) {
    Boolean validFormat;
    int lineNumber;
    char line[COIN_LINE_SIZE];

    char *denom;
    int denominationInt;
    char * denomEndPtr;

    char *coinQuantityStr;
    int coinQuantity;
    char * coinQuantityEndPtr;

    validFormat = TRUE;

    lineNumber = 0;
    while (TRUE) {
        fgets(line, COIN_LINE_SIZE, coinFile);
        if (feof(coinFile)) {
            break;
        }
        /*printf("LINE: %s", line);*/

        denom = strtok(line, COIN_DELIM);
        /*printf("DENOMINATION: %s\n", denom);*/
        denominationInt = strtol(denom, &denomEndPtr, 10);
        /*printf("DENOMINATION INTEGER: %d\n", denominationInt);*/

        coinQuantityStr = strtok(NULL, COIN_DELIM); /* to get 2nd, 3rd, 4th, ... nth token, use NULL as first param */
        /*printf("COIN QUANTITY STRING: %s\n", coinQuantityStr);*/
        coinQuantity = strtol(coinQuantityStr, &coinQuantityEndPtr, 10);
        /*printf("COIN QUANTITY: %d\n", coinQuantity);*/

        switch (denominationInt) {
            case 1000:
                cashRegister[lineNumber].denom = TEN_DOLLARS;
                break;
            case 500:
                cashRegister[lineNumber].denom = FIVE_DOLLARS;
                break;
            case 200:
                cashRegister[lineNumber].denom = TWO_DOLLARS;
                break;
            case 100:
                cashRegister[lineNumber].denom = ONE_DOLLAR;
                break;
            case 50:
                cashRegister[lineNumber].denom = FIFTY_CENTS;
                break;
            case 20:
                cashRegister[lineNumber].denom = TWENTY_CENTS;
                break;
            case 10:
                cashRegister[lineNumber].denom = TEN_CENTS;
                break;
            case 5:
                cashRegister[lineNumber].denom = FIVE_CENTS;
                break;
            default:
                validFormat = FALSE;
                break;
        }
        cashRegister[lineNumber].count = coinQuantity;

        lineNumber += 1;
    }

    if (validFormat) {
        return 1;
    }

    return 0;
}
