#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char** argv) {
  struct sockaddr_un addr = {
      .sun_family = AF_UNIX,
      .sun_path = "./some-socket-file",
  };

  int fd = socket(PF_UNIX, SOCK_STREAM, 0);

  if (fd < 0) {
    perror("socket");
    return -1;
  }

  if (connect(fd, (struct sockaddr*)&addr, sizeof addr) < 0) {
    perror("connect");
    return -1;
  }

  char* msg = "hello";
  if (argc > 1) {
    msg = argv[1];
  }

  write(fd, msg, strlen(msg));
  printf("client sent: %s\n", msg);

  char buf[256] = {};
  read(fd, buf, sizeof buf - 1);
  printf("client received: %s\n", buf);

  close(fd);
  return 0;
}
