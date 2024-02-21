/*This is version_3 of the project CLI Infrastructure For Embedded Systems. In this version I
had added some more functionalities to the version_2 code wherein version 2 did not return have
a mechanism to store previous and current variables and values of set command. In this version 
I have defined a structure to store the previous and current variables and values of set command.
It can store upto 10  variables and values.
*/

#include "cli.h"
int main()
{
    // Registering specified commands
    RegisterCommand("set", setValue, "Set a value", 2);
    RegisterCommand("get", getValue, "Get a value", 1);
    RegisterCommand("help", getHelp, "Display help information for commands", -1);

    // Command-line input processing
    char userInputBuffer[100];

    while (1)
    {

        if (loginStatus != NOT_LOGGED_IN)
        {
            printf("\nEnter command: ");
            if (fgets(userInputBuffer, sizeof(userInputBuffer), stdin) == NULL)
            {
                break; // Exit on EOF
            }

            // Remove newline character
            size_t len = strlen(userInputBuffer);
            if (len > 0 && userInputBuffer[len - 1] == '\n')
            {
                userInputBuffer[len - 1] = '\0';
            }

            // Split command and argument
            char* command = strtok(userInputBuffer, " ");
            char* arguments[10];
            int argIndex = 0;

            // add the parameters in the arguments array
            while ((arguments[argIndex] = strtok(NULL, " ")) != NULL)
            {
                argIndex++;
            }

            // if command is not NULL then process the command
            if (command != NULL)
            {
                ProcessCommand(command, arguments);
            }
            else
            {
                printf("Error: Empty command\n");
            }
        }
        else
        {
            userLogin();
        }

    }

    return 0;
}
