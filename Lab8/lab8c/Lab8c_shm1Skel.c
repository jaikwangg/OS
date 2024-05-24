#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//Lab8c_shm1Skel.c
int main() {
 // ftok to generate unique key
 key_t key = ftok("shmfile",65);
 
 // shmget returns an identifier in shmid
 int shmid = shmget(key,1024,0666|IPC_CREAT);
 // shmat to attach to shared memory
 char *str = (char*) shmat(shmid,(void*)0,0);
 //original data in shmMem
 printf("Read from mem: %s\n",str);
 //sprintf(str,"%s","os kmitl\n");
 printf("Data written to mem: %s\n",str);
 
 //detach from shared memory
shmdt(str);
 
// destroy the shared memory
shmctl(shmid,IPC_RMID,NULL);
 
 return 0;
} //main
