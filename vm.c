/******************************************************************************
** Student name: 	JOSHUA OROZCO
** Student number: 	s3485376
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"

int main(int argc, char ** argv)
{
    /**
     * 1st argument is the executable and will always be given
     * 2nd argument is the stock file. This should be optional.
     * 3rd argument is the coin file. This should be optional.
     */
    char *stockFile;
    char *coinFile;

    printf("ARGC %d\n", argc);
    switch (argc) {
        /* both stock and coin file args are missing */
        case 1:
            stockFile = DEFAULT_STOCK_FILE;
            coinFile = DEFAULT_COIN_FILE;
            break;
        /* stock file is given, coin file arg is missing */
        case 2:
            stockFile = argv[1];
            coinFile = DEFAULT_COIN_FILE;
            break;
        /* both stock and coin files are supplied */
        case 3:
        default:
            stockFile = argv[1];
            coinFile = argv[2];
            break;
    }

    
    while (argv) {
        printf("ARGV: %s", *argv);
        argv++;
    }

    MenuFunction menuChoice;
    MenuItem menuItem;
    VmSystem vmSystem;

    initMenu(&menuItem);
    
    do {
        menuChoice = getMenuChoice(&menuItem);
    }
    while (menuChoice == NULL);

    

    

    




    return EXIT_SUCCESS;
}
