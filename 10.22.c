#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#define BUFFSIZE 1024

static void sig_tstp(int);

int main(void)
{
    int     n;
    char    buf[BUFFSIZE];

    if (signal(SIGTSTP, SIG_IGN) == SIG_DFL) {
        signal(SIGTSTP, sig_tstp);
    }

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("write error\n");
            exit(-1);
        }
    }

    if (n < 0) {
        printf("read error\n");
        exit(-1);
    }

    return 0;
}

static void sig_tstp(int signo)
{
    sigset_t    mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    signal(SIGTSTP, SIG_DFL);

    kill(getpid(), SIGTSTP);

    signal(SIGTSTP, sig_tstp);
}
