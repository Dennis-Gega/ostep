#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
  int fd = open("./q2.output", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
  char *msg = "Hello, world!\n";
  write(fd, msg, 15 * sizeof(char));

  int rc = fork();
  if (rc < 0) {
    printf("fork failed.\n");
    exit(1);
  } else if (rc == 0) {
    char child[15];
    write(fd, ",olleH !dlrow\n", 15 * sizeof(char));

  } else {
    char parent[15];
    write(fd, ",olleH !dlrow\n", 15 * sizeof(char));
  }
  
  return 0;
}
