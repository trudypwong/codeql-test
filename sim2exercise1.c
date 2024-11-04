#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

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

    // fix
    char cmd[BUFSIZE];
    snprintf(cmd, BUFSIZE, "wc -c < %.20s", argv[1]);

    system(cmd);
}
