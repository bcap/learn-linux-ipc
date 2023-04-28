#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int pipefd[2];
  char buf[256] = {};

  socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);

  int cpid = fork();

  if (cpid) {
    // parent writes to socket and reads back response

    char* msg = "hello";
    if (argc > 1) {
      msg = argv[1];
    }

    write(pipefd[0], msg, strlen(msg));
    printf("parent sent: %s\n", msg);

    read(pipefd[0], buf, sizeof buf - 1);
    printf("parent received: %s\n", buf);

  } else {
    // child echoes back whatever comes from the socket
    int n = read(pipefd[1], buf, sizeof buf - 1);
    printf("child echoing back: %s\n", buf);
    write(pipefd[1], buf, n);
  }

  return 0;
}
