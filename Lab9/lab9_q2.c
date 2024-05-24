#include <stdio.h>      //for printf
#include <pthread.h>
#include <stdlib.h>     //for exit
#include <semaphore.h>//posix semaphore

#define NITER 100000 //100 x 1,000

pthread_attr_t attr[2];
pthread_t tid[2];
sem_t mySemaphore;
int cnt;
void * Count(void* a) {
  int i;
  for (i = 0; i < NITER; i++) {
    /* C */
    cnt++;
    sem_post(&mySemaphore);
  }
  void* lastSeen = malloc(sizeof(int));
  // lastSeen now refers to an actual
  // piece of memory
  if (pthread_self() == tid[0]) {
    *(int *)lastSeen = cnt; 
    printf("thr %lu exits. lastSeen = %d\n",
              pthread_self(), *(int *)lastSeen ); 
    pthread_exit( (void*)lastSeen );   } //if tid[0]
}
int main() {
  /* D */
  pthread_attr_init(&attr[0]); 
  pthread_attr_init(&attr[1]);
  pthread_create(&tid[0],&attr[0],
                   Count,NULL);
  pthread_create(&tid[1],&attr[1],
                   Count,NULL);
  void* returnVal;
  pthread_join(tid[0], &returnVal);
  int x = *(int*)returnVal;
  printf("Last cnt from tid[0] is %d\n", x);
  
  pthread_join(tid[1],NULL); //NULL if not expecting return
  
  printf("final cnt = %d\n",cnt);
  sem_destroy(&mySemaphore);
  return 0;
}