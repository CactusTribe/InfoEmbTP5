#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <semaphore.h>

pthread_mutex_t verrou;
//sem_t sem1,sem2,sem3;
sem_t mutex;

void Thread1()
{
  sem_wait(&mutex);
  pthread_mutex_lock(&verrou);
  printf("Thread_1 : HIGH Pritority\n");
  pthread_mutex_unlock(&verrou);
  //sem_post(&sem1);
}

void Thread2()
{
  sem_wait(&mutex);
  pthread_mutex_lock(&verrou);
  printf("Thread_2 : MEDIUM Pritority\n");
  pthread_mutex_unlock(&verrou);
  //sem_post(&sem2);
}

void Thread3()
{
  sem_wait(&mutex);
  pthread_mutex_lock(&verrou);
  printf("Thread_3 : LOW Pritority\n");
  pthread_mutex_unlock(&verrou);
  //sem_post(&sem1);
}

int main(int argc, char* argv[])
{
  
  pthread_t ppid1,ppid2,ppid3;
  struct sched_param param;
  pthread_attr_t attr1,attr2,attr3;
  
  //sem_init(&sem1, 0, 0);
  //sem_init(&sem2, 0, 0);
  //sem_init(&sem3, 0, 0);
  sem_init(&mutex, 0, 0);

  pthread_mutex_init(&verrou, NULL);
  
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);
  pthread_attr_init(&attr3);

  int i;
  if(argc > 1){
      i = PTHREAD_INHERIT_SCHED;
  }else{
      i = PTHREAD_EXPLICIT_SCHED;
  }

  param.sched_priority = 51;
  pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
  pthread_attr_setschedparam(&attr1,&param);
  pthread_attr_setinheritsched(&attr1,i);

  param.sched_priority = 21;
  pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
  pthread_attr_setschedparam(&attr2,&param);
  pthread_attr_setinheritsched(&attr2,i);
 
  param.sched_priority = 1;
  pthread_attr_setschedpolicy(&attr3,SCHED_FIFO);
  pthread_attr_setschedparam(&attr3,&param);
  pthread_attr_setinheritsched(&attr3,i);


  sem_wait(&mutex);

  pthread_create(&ppid1,&attr1,(void *)Thread1,NULL);
  pthread_create(&ppid2,&attr2,(void *)Thread2,NULL);
  pthread_create(&ppid3,&attr3,(void *)Thread3,NULL);

  pthread_join(ppid1,NULL);
  pthread_join(ppid2,NULL);
  pthread_join(ppid3,NULL);

  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
  pthread_attr_destroy(&attr3);
  return 0;
}