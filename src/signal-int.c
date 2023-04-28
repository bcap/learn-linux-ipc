#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void sigint_handler(int sig) {
  const char* msg = " received SIGINT!\n";
  write(1, msg, strlen(msg));
}

int main(int argc, char** argv) {
  struct sigaction sa = {
      .sa_handler = sigint_handler,
  };

  if (argc > 1 && strcmp(argv[1], "--sa-restart") == 0) {
    sa.sa_flags = SA_RESTART;
  }

  sigaction(SIGINT, &sa, NULL);

  char buf[128];
  printf("reading input from stdin\n");
  if (fgets(buf, sizeof buf, stdin) == NULL) {
    perror("fgets");
    return -1;
  }

  printf("buf is %s\n", buf);
  return 0;
}
