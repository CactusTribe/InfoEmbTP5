#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <semaphore.h>

#define _GNU_SOURCE

#define PRIORITY_T1 30
#define PRIORITY_T2 20
#define PRIORITY_T3 10

pthread_mutex_t verrou;
sem_t sem1,sem2,sem3;

int medium_executed = 0;
int inversion = 0;

void Thread1()
{
  sem_wait(&sem1);
  pthread_mutex_lock(&verrou);
  printf("Thread_1 : HIGH Pritority\n");
  sem_post(&sem3);
  pthread_mutex_unlock(&verrou);
  if(medium_executed) inversion = 1;
}

void Thread2()
{
  sem_wait(&sem2);
  pthread_mutex_lock(&verrou);
  printf("Thread_2 : MEDIUM Pritority\n");
  pthread_mutex_unlock(&verrou);
  medium_executed = 1;
}

void Thread3()
{
  sem_wait(&sem3);
  pthread_mutex_lock(&verrou);
  printf("Thread_3 : LOW Pritority\n");
  sem_post(&sem2);
  sem_post(&sem1);
  pthread_mutex_unlock(&verrou);
}

int main(int argc, char* argv[])
{
  pthread_t ppid1,ppid2,ppid3;
  struct sched_param param;
  pthread_attr_t attr1,attr2,attr3;

  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 1);

  pthread_mutex_init(&verrou, NULL);

  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);
  pthread_attr_init(&attr3);

  int policy;
  if(argc > 1){
      policy = PTHREAD_INHERIT_SCHED;
  }else{
      policy = PTHREAD_EXPLICIT_SCHED;
  }

  param.sched_priority = PRIORITY_T1;
  pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
  pthread_attr_setschedparam(&attr1,&param);
  pthread_attr_setinheritsched(&attr1, policy);

  param.sched_priority = PRIORITY_T2;
  pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
  pthread_attr_setschedparam(&attr2,&param);
  pthread_attr_setinheritsched(&attr2, policy);

  param.sched_priority = PRIORITY_T3;
  pthread_attr_setschedpolicy(&attr3,SCHED_FIFO);
  pthread_attr_setschedparam(&attr3,&param);
  pthread_attr_setinheritsched(&attr3, policy);

  pthread_create(&ppid1,&attr1,(void *)Thread1, NULL);
  pthread_create(&ppid2,&attr2,(void *)Thread2, NULL);
  pthread_create(&ppid3,&attr3,(void *)Thread3, NULL);

  pthread_join(ppid1,NULL);
  pthread_join(ppid2,NULL);
  pthread_join(ppid3,NULL);

  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
  pthread_attr_destroy(&attr3);

  if(inversion){
    printf("%s\n", "Inversion détectée");
  }else{
    printf("%s\n", "Inversion non détectée");
  }

  return 0;
}
