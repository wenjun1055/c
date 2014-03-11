#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

static void sig_cld(int);

int main(void)
{
    pid_t   pid;

    if (signal(SIGCLD, sig_cld) == SIG_ERR) {
        printf("signal error\n");
        exit(-1);
    }

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (0 == pid) {
        sleep(2);
        _exit(0);
    }

    pause();

    exit(0);
}

static void sig_cld(int signo)
{
    pid_t   pid;
    int     status;

    printf("SIGCLD received\n");
    if (signal(SIGCLD, sig_cld) == SIG_ERR) {
        printf("signal error\n");
        exit(-1);
    }

    if ((pid = wait(&status)) < 0) {
        printf("wait error\n");
        exit(-1);
    }

    printf("pid = %d\n", pid);
}
