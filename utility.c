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
    printf("%s", message);
    fgets(line, size, stdin);
    fflush(stdin);
    return strtok(line, "\n");
}

char *nextline_required(char *message, int size, char* invalid_message) {
    char *line;

    line = nextline(message, size);
    if (line != NULL && strlen(line) > 0) {
        return line;
    }

    printf("%s", invalid_message);
    return nextline_required(message, size, invalid_message);
}


int nextint(char *message) {
    char *line;
    int integer;
    char *endPointer;

    line = nextline(message, 11);
    integer = strtol(line, &endPointer, 10);
    return integer;
}

int nextint_required(char *message, char *invalid_message) {
    char *line;
    int integer;
    char *endPointer;

    line = nextline_required(message, 11, invalid_message);
    integer = strtol(line, &endPointer, 10);
    return integer;
}
