/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}


/* FUNCTIONS THAT ARE ADDED AS EXTRA HELPER FUNCTIONS */


/**
 * Ask the user to enter a line of text.
 * 
 * Note: This function will not do checking.
 * If user enters null or an empty string, it will be returned
 */
char *nextline(char *message, int size) {
    char *token;
    char *line = (char *) malloc(size);
    printf("%s", message);
    fgets(line, size + NEW_LINE_SPACE + NULL_SPACE, stdin);

    token = strtok(line, "\n");
    return token;
}


/**
 * Ask the user to enter a line of text. If line is null, this will ask again.
 * This is a recursive function.
 * 
 * Note: If user returns string of blank character, it will still considered 
 * valid result.
 **/
char *nextline_required(char *message, int size, char* invalid_message) {
    char *line;

    line = nextline(message, size);
    
    if (line != NULL && strlen(line) > 0) {
        return line;
    }

    printf("%s", invalid_message);
    readRestOfLine();
    return nextline_required(message, size, invalid_message);
}

/**
 * Ask the user to enter a number.
 * Note: This function will not do checking. 
 * If user enters an invalid number, 0 will be returned
 **/
int nextint(char *message) {
    char *line;
    int integer;
    char *endPointer;

    /**
     * 11 is the strlen of string value of max possible integer - 2,147,483,647
     * The last space is for the null termination
     **/
    line = nextline(message, 11);

    /* use base 10 */
    integer = strtol(line, &endPointer, 10);

    return integer;
}

/**
 * Ask the user to enter a number. If the input entered is not a number, it
 * will ask again. This is a recursive function.
 **/
int nextint_required(char *message, char *invalid_message) {
    char *line;
    int integer;
    char *endPointer;

    /**
     * 11 is the strlen of string value of max possible integer - 2,147,483,647
     * The last space is for the null termination
     **/
    line = nextline_required(message, 11, invalid_message);

    /* use base 10 */
    integer = strtol(line, &endPointer, 10);

    if (endPointer == NULL || strlen(endPointer) == 0) {
        return integer;
    }

    printf("%s", invalid_message);
    readRestOfLine();
    return nextint_required(message, invalid_message);
}
