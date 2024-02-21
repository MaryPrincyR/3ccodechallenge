#ifndef CLI_H
#define CLI_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum number of commands and buffer lengths
#define MAX_NUM_COMMANDS 10
#define MAX_BUFFER_LENGTH 50
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// Define login status constants
#define LOGGED_IN 1
#define NOT_LOGGED_IN 0

// Function prototype for command functions
typedef int (*CmdFunction)(char* []);

// Structure for command registration
typedef struct {
    const char* cmdName;     // Name of the command
    CmdFunction cmdFunction; // Function pointer for the command
    const char* helpText;   // Help text for the command
    int expectedNumParams;  // Expected number of parameters for the command
} CommandLineInterface;

// Global array to store commands
extern CommandLineInterface CLI_Array[MAX_NUM_COMMANDS];

// User credentials
extern const char* correctUsername;
extern const char* correctPassword;

// Global flag to indicate if user is logged in or not
extern int loginStatus;

// Global variable to hold the value of set function 
extern int storedValue;

// Function prototypes
void RegisterCommand(const char* cmdName, CmdFunction cmdFunction, const char* helpText, int numOfparam);
void showHelp();
void ProcessCommand(const char* inputCommand, char* arguments[]);
int setValue(char* arguments[]);
int getValue(char* arguments[]);
int getHelp(char* argument[]);
void userLogin();

#endif // CLI_H
