#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;
int data = 0;

void* incr(void* arg) {
  char* task_name = (char*)arg;

  // enter critical section
  sem_wait(&mutex);

  int i = data;
  // simulate 1s work
  sleep(1);
  data = i + 1;

  // leave critical section
  sem_post(&mutex);

  printf("%s done\n", task_name);

  return NULL;
}

int main() {
  int num_tasks = 5;

  pthread_t task1, task2, task3;

  sem_init(&mutex, 0, 1);

  pthread_create(&task1, NULL, incr, "task 1");
  pthread_create(&task2, NULL, incr, "task 2");
  pthread_create(&task3, NULL, incr, "task 3");

  pthread_join(task1, NULL);
  pthread_join(task2, NULL);
  pthread_join(task3, NULL);

  printf("data = %d\n", data);

  return 0;
}
