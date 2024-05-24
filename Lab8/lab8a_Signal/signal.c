#include <stdio.h>
#include <unistd.h> // for pause
#include <signal.h>
#include <stdlib.h> // for exit

void INThandler(int); // prototype

void main(void) {
    /* install Ctrl-C handler */
    signal(SIGINT, INThandler);

    while (1) /* loop forever while pause */
    /* cpu can be allocated to others */
    pause();
} //main

void INThandler(int sig) {
    /* when an SIGINT is generated,
    Start here as installed (declared) */
    signal(sig, SIG_IGN); /* disable Ctrl-C */
    /* response from INThandler */
    printf("Did you hit Ctrl-C?\n
    want to quit? [y/n] \n");
    char c;
    //c = getchar(); /* requires to trim \n */
    scanf("%c",&c);
    if (c == 'y' || c == 'Y') /* if y or Y */
    exit(0);
    else
    signal(SIGINT, INThandler);
    /* reinstall the handler */
}