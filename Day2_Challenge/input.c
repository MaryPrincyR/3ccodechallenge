#include <stdio.h>
#include "input.h"

void get_input(char* line) 
{
    int c, i = 0;

    while ((c = getchar()) != '\n' && c != EOF) /*getchar() can only read one character
                                                 at a time and it returns EOF(end - of - file) 
                                                 if there’s no more input.*/
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
}
