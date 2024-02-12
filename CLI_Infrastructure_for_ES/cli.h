#include <string.h>
#include <stdint.h>
#include <stdio.h>

char buffer[];

/* Structure to define the commands*/
typedef struct command_definition {
	const char* cmd;
	const char* help_txt;
	int(*cmd_interpreter_func)(char* buffer, long int buffer_length,  char* cmd_str);
	int expected_num_of_parameters;
} CLI_Cmd;


/*Function Prototypes*/
int Reg_Cmd(CLI_Cmd*  command_to_register);
int get_num_of_parameters( char* cmd_str);
char* cli_get_parameter( char* cmd_str, int parameter1, int* parameter2);


int help_command_interpreter(char* buffer, long int buffer_length,  char* cmd_str);
int set_command_interpreter(char* buffer, long int buffer_length,  char* cmd_str);
int get_command_interpreter(char* buffer, long int buffer_length,  char* cmd_str);

