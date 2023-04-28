#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int cpid = fork();

  // error check
  if (cpid < 0) {
    printf("failed to fork!\n");
    return cpid;
  }

  if (cpid) {
    // parent execution

    printf("parent %d waiting on child %d\n", getpid(), cpid);

    pid_t child = waitpid(cpid, NULL, 0);

    printf("parent %d done\n", getpid());

  } else {
    // child execution

    printf("child %d running for 3 seconds\n", getpid());

    sleep(3);

    printf("child %d done\n", getpid());
  }
}
