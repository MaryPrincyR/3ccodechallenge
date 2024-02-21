/*This is version_2 of the project CLI Infrastructure For Embedded Systems. In this version I 
had added some more functionalities to the version_1 code wherein version 1 did not return any values indicating that
setValue and getvalue functions has executed their job or not. In this version the setValue and
getvalue functions returns 0 or 1 indicating that the function was executed successfully or not.
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
