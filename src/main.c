/* Joaquim Lefranc, Liang Guan */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread1(){
	printf(" - THREAD 1\n");
	return NULL;
}

void* thread2(){
	printf(" - THREAD 2\n");
	return NULL;
}

void* thread3(){
	printf(" - THREAD 3\n");
	return NULL;
}

int main(int argc, char** argv){

	pthread_t t1, t2, t3;
	int prio_t1 = 50;
	int prio_t2 = 60;
	int prio_t3 = 70;

  struct sched_param sched_param_1;
  sched_param_1.sched_priority = prio_t1;

  pthread_attr_t pthread_attr_1;
  pthread_attr_init(&pthread_attr_1);
  pthread_attr_setschedpolicy(&pthread_attr_1, SCHED_FIFO);
  pthread_attr_setschedparam(&pthread_attr_1, &sched_param_1);

  struct sched_param sched_param_2;
  sched_param_2.sched_priority = prio_t2;
  pthread_attr_t pthread_attr_2;
  pthread_attr_init(&pthread_attr_2);
  pthread_attr_setschedpolicy(&pthread_attr_2, SCHED_FIFO);
  pthread_attr_setschedparam(&pthread_attr_2, &sched_param_2);

  struct sched_param sched_param_3;
  sched_param_3.sched_priority = prio_t3;

  pthread_attr_t pthread_attr_3;
  pthread_attr_init(&pthread_attr_3);
  pthread_attr_setschedpolicy(&pthread_attr_3, SCHED_FIFO);
  pthread_attr_setschedparam(&pthread_attr_3, &sched_param_3);

	pthread_create(&t1, &pthread_attr_1, thread1, NULL);
  pthread_create(&t2, &pthread_attr_2, thread2, NULL);
  pthread_create(&t3, &pthread_attr_3, thread3, NULL);

  //pthread_join(p1, NULL);
  //pthread_join(p2, NULL);

	exit(0);
}