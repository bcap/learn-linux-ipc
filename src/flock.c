#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // lock whole file by setting:
  // - seek to zero position
  // - use zero length, which means until EOF
  struct flock fl = {
      .l_type = F_WRLCK,
      .l_whence = SEEK_SET,
      .l_start = 0,
      .l_len = 0,
      .l_pid = getpid()};
  int fd;

  // set as read lock in case --read is passed on first command line arg
  if (argc > 1 && strcmp(argv[1], "--read") == 0) {
    fl.l_type = F_RDLCK;
  }

  if ((fd = open("/tmp/foo", O_RDWR | O_CREAT, 0644)) == -1) {
    perror("open");
    exit(1);
  }

  puts("Trying to get lock...");

  if (fcntl(fd, F_SETLKW, &fl) == -1) {
    perror("fcntl");
    exit(1);
  }

  puts("Got lock");
  puts("Press <RETURN> to release lock");
  getchar();

  fl.l_type = F_UNLCK; /* set to unlock same region */

  if (fcntl(fd, F_SETLK, &fl) == -1) {
    perror("fcntl");
    exit(1);
  }

  puts("Unlocked");

  close(fd);

  return 0;
}
