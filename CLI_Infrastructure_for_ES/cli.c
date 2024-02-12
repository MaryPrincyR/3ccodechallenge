#include "cli.h"

/*Initialize commands*/
const CLI_Cmd help_command = {
	"help",
	"\nHelp:\nDisplays all the available commands\nCommand List:\n",
	help_command_interpreter,
	-1
};

const CLI_Cmd set_command = {
	"set",
	"\nSet:\nAssigns the given value in the system\n",
	set_command_interpreter,
	2
};

const CLI_Cmd get_command = {
	"get",
	"\nGet:\nGet the set value\n",
	get_command_interpreter,
	2
};

int main()
{
	Reg_Cmd(&help_command);
	Reg_Cmd(&set_command);
	Reg_Cmd(&get_command);

	return 0;
}