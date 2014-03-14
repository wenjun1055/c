#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

static void     sig_int(int), pr_mask(const char *str);

int main(void)
{
    sigset_t    newmask, oldmask, waitmask;

    pr_mask("program start : ");

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal(SIGINT) error\n");
        exit(-1);
    }

    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error\n");
        exit(-1);
    }

    pr_mask("in critical region: ");

    if (sigsuspend(&waitmask) != -1) {
        printf("sigsuspend error\n");
        exit(-1);
    }

    pr_mask("after return from sigsuspend: ");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error\n");
        exit(-1);
    }

    pr_mask("program exit: ");

    return 0;
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}

static void pr_mask(const char *str)
{
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        printf("sigprocmask error\n");
        exit(-1);
    }

    printf("%s", str);

    if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
    if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
    if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
    if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");

    printf("\n");
    errno = errno_save;
}

