#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void child_death(int signal) {
  pid_t pid = wait(NULL);

  char msg[256];
  sprintf(
      msg,
      "handler at pid %d: child pid %d died (received signal %d)\n",
      getpid(),
      pid,
      signal);
  write(1, msg, strlen(msg));
}

int main() {
  struct sigaction sa = {
      .sa_handler = child_death,
  };

  sigaction(SIGCHLD, &sa, NULL);

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
    // it will actually sleep 3 as the child death will interrupt the parent
    sleep(5);

    // Use the following for sleeping 5s while being interrupt-proof
    // struct timespec st = {
    //   .tv_sec = 5,
    //   .tv_nsec = 0,
    // };
    // while(nanosleep(&st, &st) != 0) {}

    printf("parent %d done\n", getpid());

  } else {
    // child execution

    printf("child %d running for 3 seconds\n", getpid());

    sleep(3); // sleep 3s

    printf("child %d done\n", getpid());
  }
}
