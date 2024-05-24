//Lab8c_shmb2Clnt.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
char *str;
int isLoop1 = 1;
void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    //printf("from handler ");
    printf("ppid = %s, Btw SIGUSR1 = %d\n",str,sig);
    isLoop1 = 0;
    signal(sig,SIGHandler);
}
int main() {
    signal(SIGUSR1, SIGHandler);
    // ftok to generate unique key
    key_t key = ftok("hash_this",65);
    int shmid;
    //shmid = shmget(key,1024,0666|IPC_CREAT);
    shmid = shmget(key,1024,0666);
    // shmat to attach to shared memory
    str = (char*) shmat(shmid,(void*)0,0);

    // after attach to shared mem, get ppid
    int ppid = atoi(str);
    sprintf(str,"%d",getpid());
    printf("succesfully obtain ppid\n");

    kill(ppid,SIGUSR1); // to server
    //raise(SIGUSR1);
    while(isLoop1); //set to 0 to disable loop
    //str now refers to content in shmMem
    printf("Data in memory: %s\n",str);
    //kill(SIGUSR1,ppid);
    
    sprintf(str,"%s","os kmitl\n");
    printf("Writing to memory: %s\n",str);
    
    //detach from shared memory
    shmdt(str);
    
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
 return 0;
}