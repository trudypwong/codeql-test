#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 256

// Function to validate input
int is_valid_input(const char *input)
{
    size_t length = strlen(input); // Get the length of the string
    // Iterate over each character in the string using the length
    for (size_t i = 0; i < length; i++)
    {
        if (input[i] == '/' || input[i] == ';' || input[i] == '&' || input[i] == '<' || input[i] == '>')
        {
            printf("Character %zu: %c\n", i, input[i]);
            return 0; // Invalid character found
        }
    }
    return 1; // Input is valid
}

// This program prints the size of a specified file in bytes
int main(int argc, char **argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }
    // original
    // char cmd[BUFSIZE] = "wc -c < ";
    // strcat(cmd, argv[1]);

    // Validate user input
    if (!is_valid_input(argv[1]))
    {
        fprintf(stderr, "Invalid input: '/', ';', '&', '<', '>' are not allowed, only alphanumeric letters allowed.\n");
        return 1;
    }

    // Use snprintf instead of strcat
    char cmd[BUFSIZE];
    snprintf(cmd, BUFSIZE, "wc -c < %.20s", argv[1]);

    system(cmd);
}
