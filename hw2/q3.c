#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int rd = fork();

  if (rd < 0) {
    printf("fork() call failed.\n");
    exit(1);
  } else if (rd == 0) {
    printf("hello\n");
  } else {
    wait(NULL);
    printf("goodbye\n");
  }

  return 0;
}
