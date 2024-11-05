#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 256

// Function to encode the user provided string by wrapping it with quotes
void encodeShellString(char *output, size_t bufferSize, const char *input)
{
    size_t inputLength = strlen(input);
    size_t outputIndex = 0;

    // Start by adding the opening quote to the destination buffer
    if (outputIndex < bufferSize - 1)
    {
        output[outputIndex++] = '"';
    }

    // Iterate over each character in the input string
    for (size_t i = 0; i < inputLength && outputIndex < bufferSize - 2; i++)
    {
        char c = input[i];

        // Escape special shell characters by adding a backslash before them
        // Note the '$' does not work properly - it looks like it interprets as a variable - ie. til the next '-'
        if (c == '"' || c == '\\' || c == '$' || c == '`' || c == '>' || c == '<')
        {
            if (outputIndex < bufferSize - 2)
            {
                // Make sure there's room for the backslash and character
                output[outputIndex++] = '\\';
            }
        }

        // Add the current character to the destination buffer
        if (outputIndex < bufferSize - 1)
        {
            output[outputIndex++] = c;
        }
    }

    // Add the closing quote, ensuring we don't overflow the buffer
    if (outputIndex < bufferSize - 1)
    {
        output[outputIndex++] = '"';
    }

    // Null-terminate the destination string
    output[outputIndex] = '\0';
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

    // limit length of the argument
    if (strlen(argv[1]) > 30)
    {
        fprintf(stderr, "Second argument must be under 30 characters.\n");
        return 1;
    }

    // quotes the user-provided value
    char encodedCmd[BUFSIZE] = {0};
    // note: with the special characters included - the filename had to be also wrapped in quotes
    encodeShellString(encodedCmd, BUFSIZE, argv[1]);
    // use snprintf instead of strcat
    char safeCmd[BUFSIZE] = {0};
    snprintf(safeCmd, BUFSIZE, "wc -c < %30s", encodedCmd);
    system(safeCmd);
}
