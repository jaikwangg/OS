#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int notDone = 1; int cnt = 0;
void mySIGhandler(int sig) {
    notDone = 0;
}

void printCnt(int sig) {
    printf("it takes %d\n", cnt);
}

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("child created\n");
        signal(SIGUSR1, printCnt);
        while(notDone){
            cnt++;
        }
        printf("this line should not be shown\n");
        exit(0);
    } else {
        signal(SIGALRM,mySIGhandler); 
        printf("parent wait for SIGALRM\n");
        sleep(5);
        kill(pid, SIGUSR1);
        usleep(100000);
        kill(pid, SIGKILL);
    }
    return 0;
}

/* lab8a_Signal */

//Q1 (2.4)
//Output line 13 :
// 20! = 2432902008176640000

// Q2 (3.3)
// Lab8a_q3.c

/* lab8b_Pipe */

// Q1.1 -> pfd
// Q1.2 -> buf
// Q1.3 -> pfd[1], inbuf, strlen(inbuf) + 1
// Q1.4 -> pfd[1]
// Q1.5 -> wait(NULL)
// Output Q1 :
// write pipe id = 4
// read file id = 3
// child recieved 1234567890. After + 5 = 1234567895
// child recieved 12. After + 5 = 17

// Q2.1 -> dup2(fd, STDOUT_FILENO);
// Output Q2 :
// current file descriptor id is 3
// please read this line in aaa.txt
