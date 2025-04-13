#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int parent[2], child[2];
  char buf[5];

  if (pipe(parent) < 0 || pipe(child) < 0) {
    fprintf(2, "pipe failed\n");
    exit(1);
  }

  int pid = fork();
  if (pid < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    read(parent[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(child[1], "pong", 4);
  } else {
    write(parent[1], "ping", 4);
    read(child[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
  }

  exit(0);
}