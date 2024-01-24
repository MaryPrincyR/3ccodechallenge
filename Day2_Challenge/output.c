#include <stdio.h>
#include "output.h"

void display_output(char* line)
{
    for (int i = 0; line[i] != '\0'; i++) 
    {
        putchar(line[i]);
    }
    putchar('\n');
}
