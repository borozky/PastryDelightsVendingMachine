/******************************************************************************
** Student name: 	JOSHUA OROZCO
** Student number: 	s3485376
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"
#define COIN_LINE_SIZE 64

int initialize(VmSystem *vending_machine_system, int argc, char **argv);
void config_vm_filenames(VmSystem *vending_machine_system, int argc, char **argv);
void populate_cash_register(Coin cash_register[NUM_DENOMS], FILE *coin_file);
void populate_stock_list(List *item_list, FILE *stock_file);


int main(int argc, char ** argv)
{
    VmSystem *vending_machine_system;
    MenuItem *menus;
    MenuFunction menu_function;

    vending_machine_system = (VmSystem *) malloc(sizeof(*vending_machine_system));
    config_vm_filenames(vending_machine_system, argc, argv);

    if (systemInit(vending_machine_system) == FALSE) {
        return EXIT_FAILURE;
    }

    /* initialize menus here */
    menus = (MenuItem *) malloc(sizeof(*menus) * NUM_OPTIONS);
    initMenu(menus);

    do {
        menu_function = getMenuChoice(menus);
        if (menu_function != NULL) {
            menu_function(vending_machine_system);
        }

        if (menu_function == abortProgram || menu_function == saveAndExit) {
            break;
        }
    }
    while (TRUE);
    
    free(menus);
    return EXIT_SUCCESS;
}



int initialize(VmSystem *vending_machine_system, int argc, char **argv) {
    FILE *stock_file;
    FILE *coin_file;

    /* helper function to populate file names of VmSystem */
    config_vm_filenames(vending_machine_system, argc, argv);

    /* setup stock and coin files */
    stock_file = fopen(vending_machine_system->stockFileName, "r");
    coin_file = fopen(vending_machine_system->coinFileName, "r");

    /* both stock and coin files must exist */
    if (stock_file == NULL) {
        fprintf(stderr, "Stock file '%s' doesn't exists or unreadable\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (stock_file == NULL) {
        fprintf(stderr, "Stock file '%s' doesn't exists or unreadable\n", argv[1]);
        return EXIT_FAILURE;
    }

    vending_machine_system->itemList = create_list();

    /* helper method to fill up item_list and cash_register */
    populate_stock_list(vending_machine_system->itemList, stock_file);
    populate_cash_register(vending_machine_system->cashRegister, coin_file);

    /* everything is in memory */
    fclose(stock_file);
    fclose(coin_file);

    return EXIT_SUCCESS;
}


void config_vm_filenames(VmSystem *vending_machine_system, int argc, char **argv) {
    switch (argc) {
        /* both stock and coin file args are missing */
        case 1:
            vending_machine_system->stockFileName = DEFAULT_STOCK_FILE;
            vending_machine_system->coinFileName = DEFAULT_COIN_FILE;
            break;
        /* stock file is given, coin file arg is missing */
        case 2:
            vending_machine_system->stockFileName = argv[1];
            vending_machine_system->coinFileName = DEFAULT_COIN_FILE;
            break;
        /* both stock and coin files are supplied */
        case 3:
        default:
            vending_machine_system->stockFileName = argv[1];
            vending_machine_system->coinFileName = argv[2];
            break;
    }
}



void populate_cash_register(Coin cash_register[NUM_DENOMS], FILE *coin_file) {
    char *line;
    int line_num;

    line_num = 0;
    line = (char *) malloc(sizeof(*line) * 64);

    while (TRUE) {
        fgets(line, COIN_LINE_SIZE, coin_file);
        if (feof(coin_file)) {
            break;
        }
        cash_register[line_num] = *create_coin(line);
        line_num += 1;
    }
}



void populate_stock_list(List *item_list, FILE *stock_file) {
    char *line;

    line = (char *) malloc(sizeof(*line) * 1024);

    while (TRUE) {
        fgets(line, sizeof(Stock), stock_file);
        if (feof(stock_file)) {
            break;
        }

        add_stock_item(item_list, create_stock(line));
    }
}
