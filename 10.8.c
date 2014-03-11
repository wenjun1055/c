#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

static void     sig_alrm(int);
static jmp_buf  env_alrm;

int main(void)
{
    int     n;
    char    line[100];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        printf("signal(SIGALRM) error\n");
        exit(-1);
    }

    if (setjmp(env_alrm) != 0) {
        printf("read timeout\n");
        exit(-1);
    }

    alarm(10);
    if ((n = read(STDIN_FILENO, line, 100)) < 0) {
        printf("read error\n");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);

    return 0;
}

static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}
