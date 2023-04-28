#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("program started with pid %ld\n", (long)getpid());

  int v = 0;

  printf("integer value before forking: %d\n", v);

  pid_t cpid = fork();

  // could we fork?
  if (cpid < 0) {
    perror("fork");
    return -1;
  }

  if (cpid == 0) {
    // child execution
    printf("forked, child running at new pid %ld\n", (long)getpid());

    // testing copy on write
    printf("child decrementing value by 1\n");
    v--;
    printf("child has value %d\n", v);
    assert(v == -1);

  } else {
    // parent execution
    printf("forked, parent continues running at pid %ld\n", (long)getpid());

    // testing copy on write
    printf("parent incrementing value by 1\n");
    v++;
    printf("parent has value %d\n", v);
    assert(v == 1);
  }

  return 0;
}
