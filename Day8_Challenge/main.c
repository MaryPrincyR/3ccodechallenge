/*Program to reverse a string and then convert the reversed string to uppercase*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Function to reverse the string*/
void reverse_string(char* str) 
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) 
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

/*Function to convert to upper case*/
void to_uppercase(char* str) 
{
    for (int i = 0; str[i]; i++) 
    {
        str[i] = toupper(str[i]);
    }
}

int main()
{
    char str[] = "Hello World";
    printf("Original string: %s\n", str);

    reverse_string(str);
    printf("Reversed string: %s\n", str);

    to_uppercase(str);
    printf("Uppercase reversed string: %s\n", str);

    return 0;
}