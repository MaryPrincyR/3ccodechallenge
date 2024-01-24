#include "input.h"
#include "output.h"

#define LENGTH 1000

int main()
{
    char line[LENGTH];
    get_input(line);
    display_output(line);

    return 0;
}
