This is my project "CLI Infrastructure for Embedded Devices". 
In the realm of embedded systems, a Command-Line Interface (CLI) plays a crucial role. Let’s delve into its significance:
---Development and Debugging:
During development, a CLI provides a straightforward way to run commands repeatedly. This is essential for verifying functionality, performing system-level tests, and ensuring that features work as expected.
Debugging embedded systems often involves stepping through code in a debugger. However, relying solely on debuggers can be cumbersome and time-consuming. A CLI offers an alternative for efficient testing without the need for extensive software know-how.
---Manufacturing and Testing:
When manufacturing embedded devices, it’s essential to validate their functionality. A CLI simplifies this process by allowing manufacturers to execute specific commands.
Unlike debuggers, which may not be available or practical for non-developers, a CLI provides a user-friendly interface accessible during production.
---Communication Flexibility:
Embedded systems communicate through various interfaces: USB, UART, Bluetooth, Ethernet, and more. A well-designed CLI abstracts away the underlying communication protocol.
Developers and manufacturers can use the CLI over the most convenient interface for their situation, ensuring flexibility and ease of use.
---Resource Efficiency:
CLI commands are text-based and require minimal memory and processing power. Unlike graphical interfaces, they don’t burden the system with heavy graphical elements.
Executing the same command via a CLI typically involves fewer steps compared to a graphical user interface (GUI), making it an efficient choice for specific tasks

The proposed CLI infrastructure  consists of : 
--Command registration system.
--Command processing mechanism.
--Predefined ‘help’ command.
--User-defined commands.

How to run the code on your system?
--The IDE I used is Microsoft visual studio. 
--When you run the code, the CLI asks to enter the user name and password. The user name is "Princy" and password is 'password'.
--Now enter 'help' command. This will list all the command names and its functionalities.
--Now you can use 'set' command to set any variables. For instance, "set temp1 20"- this command sets variable temp1 to value 20.Other examples, "set pressure 100", "set temperature 30", "set temp2 10"
--To get the above set values use "get" command. For example, "get temp1", "get pressure", "get temperature".
--"help" command can be used with "set" and "get" commands also. For example,entering  "help set" command display the functionality of "set" command.Entering "help get" will display the functionality     of "get" command.
--To exit the CLI interface, press CTRL^Z and enter if you are using windows based system and if you are using linux based system, press CTRL^D and enter. 



<
MaryPrincyR/MaryPrincyR is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
