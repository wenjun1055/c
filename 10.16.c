#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t   quitflag;

static void sig_int(int signo)
{
    if (SIGINT == signo) {
        printf("\ninterrupt\n");
    } else if (SIGQUIT == signo) {
        quitflag = 1;
    }
}

int main(void)
{
    sigset_t    newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal(SIGINT) error\n");
        exit(-1);
    }
    
    if (signal(SIGQUIT, sig_int) == SIG_ERR) {
        printf("signal(SIGQUIT) error\n");
        exit(-1);
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error\n");
        exit(-1);
    }

    while(0 == quitflag) {
        sigsuspend(&zeromask);
    }

    quitflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error\n");
        exit(-1);
    }

    return 0;
}
