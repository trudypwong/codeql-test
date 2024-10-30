#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Required for execvp

int main(int argc, char **argv)
{
  char *userName = argv[1];

  char command1[1000] = {0};

  // Original
  // sprintf(command1, "ls %s", userName);

  // Fix 1 - safer because explicitly specifying the full path
  execl("/bin/ls", "ls", userName, NULL);

  // Fix 2 - more flexible as it searches the PATH
  // char *args[] = {"ls", "-l", userName};
  // execvp("ls", args);

  system(command1);
}
