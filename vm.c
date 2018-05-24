/******************************************************************************
** Student name: 	JOSHUA OROZCO
** Student number: 	s3485376
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"
#define COIN_LINE_SIZE 64

void config_vm_filenames(VmSystem *vending_machine_system, int argc, char **argv);


int main(int argc, char ** argv)
{
    VmSystem *vending_machine_system;
    MenuItem *menus;
    MenuFunction menu_function;
    Boolean hasInitialized = FALSE;

    vending_machine_system = (VmSystem *) malloc(sizeof(*vending_machine_system));
    config_vm_filenames(vending_machine_system, argc, argv);

    hasInitialized = systemInit(vending_machine_system);
    if (hasInitialized == FALSE) {
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
