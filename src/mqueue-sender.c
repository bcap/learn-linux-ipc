#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>

int main() {
  const int MSG_SIZE = 256;

  struct mq_attr attr = {
      .mq_flags = 0,
      .mq_maxmsg = 10,
      .mq_msgsize = MSG_SIZE,
      .mq_curmsgs = 0,
  };
  mqd_t mq = mq_open("/testqueue", O_CREAT | O_RDWR, 0644, &attr);

  if (mq == -1) {
    printf("Failed to open the queue\n");
    return -1;
  }
  printf("Queue created\n");

  printf("Write message and press enter to send it\n");
  char buf[MSG_SIZE - 1];
  fgets(buf, sizeof buf, stdin);
  mq_send(mq, buf, sizeof buf, 0);
  printf("Sent the following message: %s\n", buf);

  mq_close(mq);
  mq_unlink("/testqueue");

  return 0;
}
