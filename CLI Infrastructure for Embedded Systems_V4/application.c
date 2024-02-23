#include "cli.h"

int setValue(char* arguments[]) 
{
    if (loginStatus)
    {
        // Find the variable in the array or use an empty slot
        for (int i = 0; i < MAX_VARIABLES; ++i) 
        {
            if (strcmp(variables[i].name, arguments[0]) == 0 || variables[i].name[0] == '\0') 
            {
                // Set the name and value of the variable
                strncpy(variables[i].name, arguments[0], MAX_BUFFER_LENGTH);
                variables[i].value = atoi(arguments[1]);
                printf("Setting value of %s to: %d\n", variables[i].name, variables[i].value);
                return 0; // Indicate that the function has completed its job
            }
        }
        printf("Error: No available slots for new variables\n");
    }
    else 
    {
        printf("Please log in first.\n");
    }
    return 1; // Indicate that the function has not completed its job

}

int getValue(char* arguments[])
{
    if (loginStatus) 
    {
        // Find the variable in the array
        for (int i = 0; i < MAX_VARIABLES; ++i)
        {
            if (strcmp(variables[i].name, arguments[0]) == 0) 
            {
                printf("Getting value for %s .......%s is %d\n", variables[i].name, variables[i].name, variables[i].value);
                return 0; // Indicate that the function has completed its job
            }
        }
        printf("Error: Variable not found\n");
    }
    else 
    {
        printf("Please log in first.\n");
    }
    return 1; // Indicate that the function has not completed its job
}


// Command function for "help" command
int getHelp(char* argument[])
{
    //check if user is loggedin first
    if (loginStatus)
    {
        if (argument[0] != NULL)
        {
            // Display help for a specific command
            for (int i = 0; i < MAX_NUM_COMMANDS; ++i)
            {
                if (CLI_Array[i].cmdName != NULL && strcmp(argument[0], CLI_Array[i].cmdName) == 0)
                {
                    printf("Help for command '%s': %s\n", argument[0], CLI_Array[i].helpText);
                    return 0; // Indicate that the function has completed its job
                }
            }
            printf("Error: Unknown command: %s\n", argument[0]);
            return 1; // Indicate that the function has not completed its job
        }
        else
        {
            // Display general help for all commands
            showHelp();
            return 0; // Indicate that the function has completed its job
        }
    }
    else
    {
        printf("Please log in first.\n");
        return 1; // Indicate that the function has not completed its job
    }
}

int main()
{
    // Registering specified commands
    CommandLineInterface setCommand = { "set", setValue, "Set a value", 2 };
    RegisterCommand(&setCommand);

    CommandLineInterface getCommand = { "get", getValue, "Get a value", 1 };
    RegisterCommand(&getCommand);

    CommandLineInterface helpCommand = { "help", getHelp, "Display help information for commands", -1 };
    RegisterCommand(&helpCommand);

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



