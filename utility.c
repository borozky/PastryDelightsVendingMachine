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

char *nextline(char *message, int size) {
    char *line = (char *) malloc(size);

    do {
        printf("%s", message);
        line = fgets(line, size, stdin);
        if (strlen(line) > 0) {
            break;
        }
    } while (TRUE);

    return strtok(line, "\n");
}

int nextint(char *message) {
    /**
     * max integer is 2,147,483,647 w/c is 10 digits,
     * the remaining 1 slot is for null space
     */
    char line[11];
    int integer;
    char *endPointer;

    do {
        printf("%s", message);
        fgets(line, sizeof(line), stdin);
        integer = strtol(line, &endPointer, 10);
        if (strlen(endPointer) == 0) {
            break;
        }
    } 
    while (TRUE);

    return integer;
}
