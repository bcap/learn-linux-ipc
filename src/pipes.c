#include <stdio.h>
#include <unistd.h>

int main() {
  int pipefd[2];
  pipe(pipefd);

  int cpid = fork();

  // error check
  if (cpid < 0) {
    printf("failed to fork!\n");
    return cpid;
  }

  if (cpid == 0) {
    // child execution

    // replace stdout by closing it and then duplicating the pipe writing
    // endpoint
    close(1);
    dup(pipefd[1]);

    // the close + dup above can be simplified to:
    // dup2(pipefd[1], 1);

    // close the read endpoint as it is not necessary
    close(pipefd[0]);

    // replace this process with `seq 10`
    return execlp("seq", "seq", "10", NULL);

  } else {
    // parent execution

    // replace stding by closing it and then duplicating the pipe reading
    // endpoint
    close(0);
    dup(pipefd[0]);

    // the close + dup above can be simplified to:
    // dup2(pipefd[0], 0);

    // close the write endpoint as it is not necessary
    close(pipefd[1]);

    // replace this process with `tail -n 5`
    return execlp("tail", "tail", "-n", "5", NULL);
  }
}
