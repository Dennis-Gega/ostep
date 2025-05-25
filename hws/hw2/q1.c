#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  int x = 100;

  int rd = fork();
  if (rd < 0) {
    printf("fork() call failed.\n");
    exit(1);
  } else if (rd == 0) {
    printf("this is the child process, x = %d\n", x);
  } else {
    x = 50;
    printf("this is the parent process, x = %d\n", x);
  }
}

// the variable in the child process is the same as the initialization
// when we change the variable in a process it only affects the process it is in
