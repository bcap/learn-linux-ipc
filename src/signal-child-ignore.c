#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // struct sigaction sa = {.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT};

  // sigaction(SIGCHLD, &sa, NULL);

  int cpid = fork();

  // error check
  if (cpid < 0) {
    printf("failed to fork!\n");
    return cpid;
  }

  if (cpid) {
    // parent execution

    printf("parent %d running for 5 seconds\n", getpid());

    // try to sleep 5s
    sleep(5);

    printf("parent %d done\n", getpid());

  } else {
    // child execution

    printf("child %d running for 3 seconds\n", getpid());

    sleep(3); // sleep 3s

    printf("child %d done\n", getpid());
  }
}
