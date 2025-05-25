#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

char* message = "x";

int main() {
  printf("measuring syscall time:\n");
  struct timeval time_before, time_after;
  int fd = open("./readfile", O_RDONLY);
  if (fd < 0) {
    perror("open() failed");
    exit(1);
  }
  char buffer[1];
  int num_iterations = 1000;
  gettimeofday(&time_before, NULL);
  for (int i = 0; i < num_iterations; i++)
    read(fd, buffer, 1);
  gettimeofday(&time_after, NULL);
  close(fd);
  double syscall_time = (time_after.tv_sec - time_before.tv_sec) * 1e6 +
                        (time_after.tv_usec - time_before.tv_usec);
  printf("average syscall time: %lf microseconds\n\n", syscall_time / num_iterations);
  
  printf("measuring context switch time:\n");
  int p1[2], p2[2];
  if (pipe(p1) < 0 || pipe(p2) < 0) {
    perror("pipe failed");
    exit(1);
  }
  
  char buf[1];
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }
  
  int context_switch_iterations = 10;
  if (pid > 0) {
    close(p1[0]);
    close(p2[1]);
    
    gettimeofday(&time_before, NULL);
    for (int i = 0; i < context_switch_iterations; i++) {
      write(p1[1], message, 1);
      read(p2[0], buf, 1);
    }
    gettimeofday(&time_after, NULL);
    
    close(p1[1]);
    close(p2[0]);
    wait(NULL);
    
    double context_time = (time_after.tv_sec - time_before.tv_sec) * 1e6 +
                          (time_after.tv_usec - time_before.tv_usec);
    printf("average context switch time: %lf microseconds\n", context_time / (2 * context_switch_iterations));
  } else {
    close(p1[1]);
    close(p2[0]);
    
    for (int i = 0; i < context_switch_iterations; i++) {
      read(p1[0], buf, 1);
      write(p2[1], buf, 1);
    }
    
    close(p1[0]);
    close(p2[1]);
    exit(0);
  }
  return 0;
}
