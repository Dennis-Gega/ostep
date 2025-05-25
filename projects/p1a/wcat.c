// implement my own version of cat
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1000

int main(int argc, char* argv[]) {

  // exit right away if no arguments are passed on command line
  if (argc == 1) {
    exit(0);
  }

  // print each file passed on command line
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "r");

    if (file == NULL) {
      perror("wcat: cannot open file\n");
      exit(1);
    }

    char buffer[BUFFER_SIZE];
    
    // print every line until we reach end-of-file
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
      printf("%s", buffer);
    }
  }
  return 0;
}
