#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  struct sockaddr_un addr = {
      .sun_family = AF_UNIX,
      .sun_path = "./some-socket-file",
  };

  // cleanup before start
  unlink("./some-socket-file");

  int srvfd = socket(PF_UNIX, SOCK_STREAM, 0);
  if (srvfd < 0) {
    perror("socket");
    return -1;
  }

  if (bind(srvfd, (struct sockaddr*)&addr, sizeof addr) < 0) {
    perror("bind");
    return -1;
  }

  if (listen(srvfd, 5) < 0) {
    perror("listen");
    return -1;
  }

  printf("server listening\n");

  while (1) {
    int clifd = accept(srvfd, NULL, 0);
    if (clifd < 0) {
      perror("accept");
      return -1;
    }

    char msg[256] = {};

    int n = read(clifd, msg, sizeof msg);

    if (n < 0) {
      perror("read");
      return -1;
    }

    printf("server echoing back: %s\n", msg);

    if (write(clifd, msg, n) < 0) {
      perror("write");
      return -1;
    }

    close(clifd);
  }

  return 0;
}
