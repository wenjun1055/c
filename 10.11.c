#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_quit(int);

int main(void)
{
    sigset_t    newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        printf("... can't catch SIGQUIT...\n");
        exit(-1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("... SIG_BLOCK error...\n");
        exit(-1);
    }

    sleep(5);

    if (sigpending(&pendmask) < 0) {
        printf("...sigpending error...\n");
        exit(-1);
    }

    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\n...SIGQUIT pending...\n");
        exit(-1);
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("...SIG_SETMASK error...\n");
        exit(-1);
    }

    printf("...SIGQUIT unblocked...\n");

    sleep(5);
    
    return 0;
}

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        printf("...can't reset SIGQUIT...");
        exit(-1);
    }
}
