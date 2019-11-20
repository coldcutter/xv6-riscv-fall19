#include "kernel/types.h"
#include "user/user.h"

void primeproc(int rfd) {
  int fd[2], p, n, r;
  r = read(rfd, &p, sizeof(int));
  if (r != 4) {
    return;
  }
  printf("prime %d\n", p);
  pipe(fd);
  if (fork() == 0) {
    primeproc(fd[0]);
  } else {
    while (read(rfd, &n, sizeof(int)) > 0) {
      if (n % p != 0) {
        write(fd[1], &n, sizeof(int));
      }
    }
    close(fd[1]);
    close(rfd);
  }
}

int
main(int argc, char *argv[]) {
  int fd[2], i;

  pipe(fd);
  if (fork() == 0) {
    primeproc(fd[0]);
  } else {
    for (i = 2; i <= 35; ++i) {
      write(fd[1], &i, sizeof(int));
    }
    close(fd[1]);
  }

  exit();
}
