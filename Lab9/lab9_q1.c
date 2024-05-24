#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include "peterson.h" //**
#include <wait.h>
void  childProcess(int *);
void parentProcess(int *);

int main(int  argc, char *argv[]) {
  int   shmID;   int status;
  int  *count;
  pid_t  pid;
  int NITER = 100;
     
  shmID = shmget(IPC_PRIVATE, 
            sizeof(struct Memory), IPC_CREAT | 0666);

  count = (int *) shmat(shmID, (void *)0, 0);

  *count = 5; 

       //initialize Peterson's algorithm shared memory    
  initializePeterson();        

  pid = fork();
  if (pid == 0) {
       for (int i = 0; i < NITER; i++)
            childProcess(count);
       exit(0);
  }
  for (int i = 0; i < NITER; i++) 
       parentProcess(count);               
  wait(&status);
  printf("The final value of count is %d\n", *count);

  //remove shared memory for Peterson's algorithm
  removePeterson();           
  shmdt((void *) count);
  shmctl(shmID, IPC_RMID, NULL);          
  exit(0);
}
void  parentProcess(int *count) {
     enterCriticalSection(0);
     int temp = *count;  temp++;
     /*sleep(rand() % 3); */ *count = temp;
     /* A */
}
void  childProcess(int *count) {
     /* B */
     int temp = *count;  temp--;
     /*sleep(rand() % 3); */ *count = temp;
     exitCriticalSection(1);    
}
