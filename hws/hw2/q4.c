#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  int rd = fork();
  if (rd < 0) {
    printf("fork() call failed.\n");
    exit(1);
  } else if (rd == 0) {
    printf("child process --------------------------------------\n");
    char *args[] = {"/bin/ls", NULL };
    execvp(args[0], args);
  } else {
    printf("parent process -------------------------------------\n");
    char *args[] = {"/bin/ls", NULL };
    execvp(args[0], args);
  }
  return 0;
}
