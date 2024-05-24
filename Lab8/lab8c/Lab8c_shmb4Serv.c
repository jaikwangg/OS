#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

char *str;
int isLoop = 1;
void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    printf("from handler ");
    isLoop = 0;
    signal(sig,SIGHandler); //handler
}
int main(int argc, char * argv[]) {
    signal(SIGUSR1, SIGHandler);

    key_t key = ftok("hash_this",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    //int shmid = shmget(key,1024,0666);

    // shmat to attach to shared memory
    str = (char*) shmat(shmid,(void*)0,0);

    int cpid;
    sprintf(str,"%d",getpid()); //ppid for clnt

    // wait SIGUSR1 after child got my pid
    while(isLoop);
    isLoop = 1; //preparing for next loop

    cpid = atoi(str);
    kill(cpid,SIGUSR1); // to client 

    while(isLoop);
    //reading from  shmMem
    printf("From child: %s\n",str);

    //detach and remove 
    shmdt(str); shmctl(shmid,IPC_RMID,NULL);
 return 0;//main
}