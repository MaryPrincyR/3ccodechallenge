#include "cli.h"

// Initialize global variables
CommandLineInterface CLI_Array[MAX_NUM_COMMANDS];
const char* correctUsername = "Priyanka";
const char* correctPassword = "password";
int loginStatus = 0;
int storedValue = 0;

// Function to register a new command and its corresponding function
void RegisterCommand(const char* cmdName, CmdFunction cmdFunction, const char* helpText, int numOfparam) 
{
    static int numCommands = 0;

    // Only register specified commands
    if (numCommands < MAX_NUM_COMMANDS) 
    {
        CLI_Array[numCommands].cmdName = cmdName;
        CLI_Array[numCommands].cmdFunction = cmdFunction;
        CLI_Array[numCommands].expectedNumParams = numOfparam;
        CLI_Array[numCommands].helpText = helpText;
        numCommands++;
    }
    else 
    {
        fprintf(stderr, "Maximum number of commands reached\n");
    }
}

// Function to display help information for all registered commands
void showHelp()
{
    printf("Available commands:\n");
    for (int i = 0; i < MAX_NUM_COMMANDS; ++i) 
    {
        if (CLI_Array[i].cmdName != NULL) 
        {
            printf("  %s: %s\n", CLI_Array[i].cmdName, CLI_Array[i].helpText);
        }
    }
}

// Function to process and execute the command
void ProcessCommand(const char* inputCommand, char* arguments[]) 
{
    if (!loginStatus)
    {
        printf("Please log in first.\n");
        return;
    }

    for (int i = 0; i < MAX_NUM_COMMANDS; ++i)
    {
        if (CLI_Array[i].cmdName != NULL && strcmp(inputCommand, CLI_Array[i].cmdName) == 0)
        {
            // Check if the correct number of parameters is provided
            int expectedNumParams = CLI_Array[i].expectedNumParams;
            int providedNumParams = 0;

            // calculate the provided num of parameters by user 
            while (arguments[providedNumParams] != NULL) 
            {
                providedNumParams++;
            }

            // function pointer should be called only if the number of parameters matches the expected one or it is s help cmd
            if ((expectedNumParams == -1) || (expectedNumParams == providedNumParams)) 
            {
                // Call the corresponding function using function pointer
                int result = CLI_Array[i].cmdFunction(arguments);
                if (result == 0)
                {
                    printf("Command executed successfully.\n");
                }
                else
                {
                    printf("Command did not complete successfully.\n");
                }
                return;
            }
            else 
            {
                printf("Error: Incorrect number of parameters for '%s' command\n", inputCommand);
                return;
            }
        }
    }

    printf("Error: Unknown command: %s\n", inputCommand);
    showHelp();
}

// Command function for "set" command
int setValue(char* arguments[]) 
{
    //check if user is logedin then only allow usage of set functionality
    if (loginStatus) 
    {
        storedValue = atoi(arguments[1]);
        printf("Setting value to: %d\n", storedValue);
        return 0; // Indicate that the function has completed its job
    }
    else 
    {
        printf("Please log in first.\n");
        return 1; // Indicate that the function has not completed its job
    }
}

// Command function for "get" command
int getValue(char* arguments[])
{
    // check if user is logged in then only allow usage of get functionality
    if (loginStatus)
    {
        printf("Getting value for: %s is %d\n", arguments[0], storedValue);
        return 0; // Indicate that the function has completed its job
    }
    else 
    {
        printf("Please log in first.\n");
        return 1; // Indicate that the function has not completed its job
    }
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


// Function to handle user login
void userLogin()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);

    // Remove newline character
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
    {
        username[len - 1] = '\0';
    }

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);

    // Remove newline character
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') 
    {
        password[len - 1] = '\0';
    }

    // Perform basic login validation
    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
    {
        printf("Login successful. Welcome, %s!\n", correctUsername);
        loginStatus = LOGGED_IN;
    }
    else 
    {
        printf("Invalid login credentials. Please try again.\n");
        loginStatus = NOT_LOGGED_IN;
    }
}

       
