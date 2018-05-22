/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{
    int i = 0;
    int j = 0;

    /* array of strings of menu items */
    char* menuItemTexts[NUM_OPTIONS] = {
        "Display items",
        "Purchase items",
        "Save and Exit",
        "Add item",
        "Remove item",
        "Display coins",
        "Reset stock",
        "Reset coins",
        "Abort Program"
    };

    /* array of function pointers */
    MenuFunction menuFunctions[NUM_OPTIONS] = {
        displayItems,
        purchaseItem,
        saveAndExit,
        addItem,
        removeItem,
        displayCoins,
        resetStock,
        resetCoins,
        abortProgram
    };


    /* assign text and callbacks */
    for (i = 0; i < NUM_OPTIONS; i++) {
        strcpy(menu[i].text, menuItemTexts[i]);
        menu[i].function = menuFunctions[i];
    }

    while (j < NUM_OPTIONS) {
        if (j == 0) {
            printf("Main Menu:\n");
        }
        else if (j == 3) {
            printf("Administrator-Only Menu:\n");
        }
        printf("%d. %s\n", j + 1, menu[j].text);
        j += 1;
    }

}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    MenuFunction function;
    int inputNumber = 0;

    inputNumber = get_menu_number();

    if (inputNumber > 0 && inputNumber <= NUM_OPTIONS) {
        function = menu[inputNumber - 1].function;
        return function;
    }

    return NULL;
}

/**
 * Ask the user a number from 1 - 9. This is a recursive function.
 **/
int get_menu_number() {
    int inputNumber = 0;

    inputNumber = nextint_required("Select your options (1-9): ", "Invalid input\n");

    printf("Detected number: %d\n", inputNumber);

    if (inputNumber > 0 && inputNumber <= NUM_OPTIONS) {
        return inputNumber;
    }
    
    printf("Please choose 1 - 9\n");
    return get_menu_number();
}

