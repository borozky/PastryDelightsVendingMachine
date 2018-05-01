/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"
#define NUM_OF_OPTIONS 9

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

    /* menu will be NULL when passed. So initialize some memory */
    menu = (MenuItem *) malloc(sizeof(MenuItem) * NUM_OF_OPTIONS);
    if (menu == NULL) {
        printf("CANNOT INITIALIZE MENU ITEMS");
        exit(0);
    }

    /* array of strings of menu items */
    char* menuItemTexts[NUM_OF_OPTIONS] = {
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
    MenuFunction menuFunctions[NUM_OF_OPTIONS] = {
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
    for (i = 0; i < NUM_OF_OPTIONS; i++) {
        /**
         * Using this code below produce error 'array type 'char [51]' is not assignable'
         * menu[i].text = menuItemText[i]
         * So copy the strings instead of referencing them
         */
        strcpy(menu[i].text, menuItemTexts[i]);
        menu[i].function = menuFunctions[i];
    }


    for (j = 0; j < NUM_OF_OPTIONS; j++) {
        if (j == 0) {
            printf("Main Menu:\n");
        }
        else if (j == 3) {
            printf("Administrator-Only Menu:\n");
        }
        printf("%d. %s\n", j + 1, menuItemTexts[j]);
    }


}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    int buffer;
    char* enteredInput;
    int inputNumber;
    char *endPointer; /* all non int inputs will be collected here */
    MenuFunction function;

    inputNumber = 0;
    buffer = sizeof(int);
    enteredInput = (char *) malloc(buffer);

    printf("Select your options (1-9): ");
    enteredInput = fgets(enteredInput, buffer, stdin);
    fflush(stdin);
    printf("Entered: %s\n", enteredInput);

    /**
     * endPointer must not be NULL so don't initialize 
     * endPointer as '**endPointer' becasue it will be 
     * NULL to begin with */
    inputNumber = strtol(enteredInput, &endPointer, 10);
    printf("Detected number: %d\n", inputNumber);

    if (inputNumber > 0 && inputNumber <= NUM_OF_OPTIONS) {
        return *(menu + (inputNumber - 1))->function; 
    }

    return NULL;

}
