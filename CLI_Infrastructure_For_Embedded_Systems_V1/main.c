#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of commands
#define MAX_COMMANDS 10

// Maximum size for the character buffer
#define MAX_BUFFER_SIZE 50
#define MAX_USERNAME_SIZE 20
#define MAX_PASSWORD_SIZE 20

#define TRUE       1
#define FALSE      0

// Define function prototype for command functions which will be provided by application
typedef void (*CommandFunction)(char* []);

// Define a structure for command registration
typedef struct {
    const char* command;     // name of the command
    CommandFunction function; // function pointer for the particular command
    const char* helpText;  // Help text for the command
    int expectedParams;  // Expected number of parameters for the command
} CommandLineInterface;

// Global array to store commands
CommandLineInterface CommandInterfaceArray[MAX_COMMANDS];

// User credentials
const char* validUsername = "Priyanka";
const char* validPassword = "password";
// global flag to indicate if user is loggedin or not
int isLoggedIn = 0;
// global variable to hold the value of set function 
int value = 0;

// Function to register a new command and its corresponding function
void registerCommand(const char* command, CommandFunction function, const char* helpText, int numOfparam) {
    static int commandCount = 0;

    // Only register specified commands
    if (commandCount < MAX_COMMANDS) {
        CommandInterfaceArray[commandCount].command = command;
        CommandInterfaceArray[commandCount].function = function;
        CommandInterfaceArray[commandCount].expectedParams = numOfparam;
        CommandInterfaceArray[commandCount].helpText = helpText;
        commandCount++;
    }
    else {
        fprintf(stderr, "Maximum number of commands reached\n");
    }
}

// Function to display help information for all registered commands
void displayHelp() {
    printf("Available commands:\n");
    for (int i = 0; i < MAX_COMMANDS; ++i) {
        if (CommandInterfaceArray[i].command != NULL) {
            printf("  %s: %s\n", CommandInterfaceArray[i].command, CommandInterfaceArray[i].helpText);
        }
    }
}

// Function to process and execute the command
void processCommand(const char* inputCommand, char* arguments[]) {
    if (!isLoggedIn) {
        printf("Please log in first.\n");
        return;
    }

    for (int i = 0; i < MAX_COMMANDS; ++i) {
        if (CommandInterfaceArray[i].command != NULL && strcmp(inputCommand, CommandInterfaceArray[i].command) == 0) {
            // Check if the correct number of parameters is provided
            int expectedParams = CommandInterfaceArray[i].expectedParams;
            int providedParams = 0;

            // calculate the provided num of parameters by user 
            while (arguments[providedParams] != NULL) {
                providedParams++;
            }

            // function pointer should be called only if the number of parameters matches the expected one or it is s help cmd
            if ((expectedParams == -1) || (expectedParams == providedParams)) {
                // Call the corresponding function using function pointer
                CommandInterfaceArray[i].function(arguments);
                return;
            }
            else {
                printf("Error: Incorrect number of parameters for '%s' command\n", inputCommand);
                return;
            }
        }
    }

    printf("Error: Unknown command: %s\n", inputCommand);
    displayHelp();
}

// Command function for "set" command
void setCommand(char* arguments[]) {
    /*check if user is logedin then only allow usage of set functionality*/
    if (isLoggedIn) {
        value = atoi(arguments[1]);
        printf("Setting value to: %d\n", value);
    }
    else {
        printf("Please log in first.\n");
    }
}

// Command function for "get" command
void getCommand(char* arguments[]) {
    /* check if user is loggedin then only allow usage of get functionality*/
    if (isLoggedIn) {
        printf("Getting value for: %s is %d\n", arguments[0], value);
    }
    else {
        printf("Please log in first.\n");
    }
}

// Command function for "help" command
void helpCommand(char* argument[]) {
    /*check if user is loggedin first*/
    if (isLoggedIn)
    {
        if (argument[0] != NULL) {
            // Display help for a specific command
            for (int i = 0; i < MAX_COMMANDS; ++i) {
                if (CommandInterfaceArray[i].command != NULL && strcmp(argument[0], CommandInterfaceArray[i].command) == 0) {
                    printf("Help for command '%s': %s\n", argument[0], CommandInterfaceArray[i].helpText);
                    return;
                }
            }
            printf("Error: Unknown command: %s\n", argument[0]);
        }
        else {
            // Display general help for all commands
            displayHelp();
        }
    }
    else {
        printf("Please log in first.\n");
    }
}

// Function to handle user login
void login() {
    char username[MAX_USERNAME_SIZE];
    char password[MAX_PASSWORD_SIZE];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);

    // Remove newline character
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);

    // Remove newline character
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    // Perform basic login validation
    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        printf("Login successful. Welcome, %s!\n", validUsername);
        isLoggedIn = TRUE;
    }
    else {
        printf("Invalid login credentials. Please try again.\n");
        isLoggedIn = FALSE;
    }
}

int main() {
    // Registering specified commands
    registerCommand("set", setCommand, "Set a value", 2);
    registerCommand("get", getCommand, "Get a value", 1);
    registerCommand("help", helpCommand, "Display help information for commands", -1);

    // Command-line input processing
    char UserinputBuffer[100];

    while (1) {

        if (isLoggedIn != FALSE)
        {
            printf("\nEnter command: ");
            if (fgets(UserinputBuffer, sizeof(UserinputBuffer), stdin) == NULL) {
                break; // Exit on EOF
            }

            // Remove newline character
            size_t len = strlen(UserinputBuffer);
            if (len > 0 && UserinputBuffer[len - 1] == '\n') {
                UserinputBuffer[len - 1] = '\0';
            }

            // Split command and argument
            char* command = strtok(UserinputBuffer, " ");
            char* arguments[10];
            int argIndex = 0;

            // add the parameters in the arguments array
            while ((arguments[argIndex] = strtok(NULL, " ")) != NULL) {
                argIndex++;
            }

            // if command is not NULL then process the command
            if (command != NULL) {
                processCommand(command, arguments);
            }
            else {
                printf("Error: Empty command\n");
            }
        }
        else
        {
            login();
        }

    }

    return 0;
}