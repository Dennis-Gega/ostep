#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // all the addresses printed out here are virtual
  printf("location of code: %p\n", (void *) main);
  printf("location of heap: %p\n", (void *) malloc(1));
  int x = 3;
  printf("location of stack: %p\n", (void *) &x);
  return 0;
}
