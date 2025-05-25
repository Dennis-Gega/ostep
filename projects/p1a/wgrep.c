// my own version of grep 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void searchForWord(char *searchword, FILE *fd)
{
  char *buffer = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&buffer, &linecap, fd)) > 0)
  {
    if (strstr(buffer, searchword) != NULL)
      printf("%s", buffer);
  }
}

int main(int argc, char* argv[])
{
  // print out correct usage of wgrep
  if (argc == 1)
  {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  char *searchword = argv[1];

  // if no file argument is specified, read from stdin
  if (!argv[2]) {
    searchForWord(searchword, stdin);
    exit(0);
  }

  // otherwise, look for string in every file specified in command line
  for (int i = 2; i < argc; i++)
  {
    FILE *current_file = fopen(argv[i], "r");
    
    if (current_file == NULL)
    {
      printf("wgrep: cannot open file\n");
      exit(1);
    }

    searchForWord(searchword, current_file);
  }

  return 0;
}
