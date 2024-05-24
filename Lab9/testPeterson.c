#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include "peterson.h"
void  childProcess(int *);
void parentProcess(int *);
int main(int  argc, char *argv[])
{
     int   shmID;
     int  *count;
     pid_t  pid;
     int    status;
     
     shmID = shmget(IPC_PRIVATE, sizeof(struct Memory), IPC_CREAT | 0666);
     if (shmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     
     count = (int *) shmat(shmID, NULL, 0);
     if ((int) *count == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     *count = 5;   
     initializePeterson(); //initialize shared memory for Peterson's algorithm       
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          childProcess(count);
          exit(0);
     }
     parentProcess(count);	    	 	     
     wait(&status);
     printf("The final value of count is %d\n", *count);	
     removePeterson(); //remove shared memory for Peterson's algorithm	
     //remove shared memory used by this program	
     shmdt((void *) count);
     shmctl(shmID, IPC_RMID, NULL);		
     exit(0);
}
void  parentProcess(int *count) {
	enterCriticalSection(0);
	int temp = *count;
	temp++;
     sleep(rand() % 4);
	*count = temp;
     exitCriticalSection(0);
}
void  childProcess(int *count)
{
 	enterCriticalSection(1);
	
	int temp = *count;
	temp--;
	sleep(rand() % 4);
	*count = temp;
        exitCriticalSection(1);    
}
