#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
  printf("measuring syscall time:\n");
  struct timeval time_before, time_after;
  gettimeofday(&time_before, NULL);

  int fd = open("./readfile", O_RDONLY);
  char buffer[1];

  for (int i = 0; i < 1000; i++)
    read(fd, buffer, 0);

  gettimeofday(&time_after, NULL);

  printf("elapsed time: %lf microseconds\n", (time_after.tv_usec - time_before.tv_usec) / 1000.0);
  return 0;
}
