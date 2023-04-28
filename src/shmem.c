#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int parent() {
  int fd = shm_open("/clowncopterize", O_CREAT | O_RDWR, 0644);

  ftruncate(fd, 256);
  char* m = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  char* msg = "hello world";
  memcpy(m, msg, strlen(msg));

  printf("parent wrote to shared memory: %s\n", m);

  sleep(3);

  printf("parent read from shared memory: %s\n", m);

  return 0;
}

int child() {
  sleep(1);

  int fd = shm_open("/clowncopterize", O_RDWR, 0644);
  char* m = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  printf("child read from shared memory: %s\n", m);

  sleep(1);
  m[0] = '_';
  printf("child modified first character: %s\n", m);

  return 0;
}

int main() {
  int cpid = fork();

  if (cpid) {
    return parent();
  } else {
    return child();
  }
}
