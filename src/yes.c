#include <stdio.h>

// a simple, line buffered version of the yes command
int main(int argc, char** argv) {
  if (argc < 2) {
    return -1;
  }
  setlinebuf(stdout);
  while (1) {
    printf("%s\n", argv[1]);
  }
  return 0;
}
