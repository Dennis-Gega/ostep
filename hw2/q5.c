#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rd = fork();
  printf("rd is %d\n", rd);
  if (rd < 0) {
    printf("fork() call failed.\n");
    exit(1);
  } else if (rd == 0) {
    printf("i am first (rd is: %d)\n", rd);
  } else {
    int rv = wait(NULL);
    printf("i am last (wait returned: %d)\n", rv);
  }

  return 0;
}
