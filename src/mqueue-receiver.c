#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>

int main() {
  mqd_t mq = mq_open("/testqueue", O_RDONLY);

  if (mq == -1) {
    printf("Failed to open the queue\n");
    return -1;
  }

  char msg[256] = {};
  printf("Waiting for message to arrive at the queue...\n");
  mq_receive(mq, msg, sizeof msg, 0);
  printf("Message received: %s\n", msg);

  return 0;
}
