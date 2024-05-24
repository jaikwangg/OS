//Lab8c_shmb2Clnt.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
char *str;
int isLoop = 0;
void SIGHandler(int sig) {
 signal(sig, SIG_IGN);
 printf("from handler ");
 printf("%s\n",str);
 signal(sig,SIGHandler);
}
int main() {
 signal(SIGUSR1, SIGHandler);
 // ftok to generate unique key
 key_t key = ftok("hash_this",65);
 
 // shmget returns an identifier in shmid
 int shmid = shmget(key,1024,0666|IPC_CREAT);
 // shmat to attach to shared memory
 str = (char*) shmat(shmid,(void*)0,0);
 while(isLoop) ; //set to 0 to disable loop
 //str now refers to content in shmMem
 printf("Data in memory: %s\n",str);
 int ppid = atoi(str);
 //kill(SIGUSR1,ppid);
 raise(SIGUSR1);
 
 sprintf(str,"%s","os kmitl\n");
 printf("Writing to memory: %s\n",str);
 
 //detach from shared memory
 shmdt(str);
 
 // destroy the shared memory
 shmctl(shmid,IPC_RMID,NULL);
 return 0;
}