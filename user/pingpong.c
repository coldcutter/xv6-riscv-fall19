#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int parent_fd[2], child_fd[2];
  char buf[4];

  pipe(parent_fd);
  pipe(child_fd);
  if (fork() == 0) {
    read(parent_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    close(parent_fd[0]);
    write(child_fd[1], "pong", 4);
    close(child_fd[1]);
  } else {
    write(parent_fd[1], "ping", 4);
    close(parent_fd[1]);
    read(child_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    close(child_fd[0]);
  }

  exit();
}
